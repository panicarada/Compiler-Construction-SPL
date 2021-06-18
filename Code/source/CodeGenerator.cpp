//
// Created by 邱泽鸿 on 2021/6/15.
//


#include "CodeGenerator.hpp"
#include "Typing.hpp"
#include "Interpreter.hpp"
#include "yacc.tab.hpp"


llvm::LLVMContext CodeGenerator::Context;
llvm::IRBuilder<> CodeGenerator::Builder(Context);


llvm::Type* CodeGenerator::toLLVM(Typing::Node* tNode)
{
    switch (tNode->nType)
    {
        case Typing::NodeType::t_CONSTANT:
        {
            raiseError("这部分应该被处理过");
        }
        case Typing::NodeType::t_SYS_TYPE:
        {
            auto* sysNode = dynamic_cast<Typing::sysNode*>(tNode);
            if (sysNode->dType == Typing::DataType::d_INTEGER)
            {
                return Builder.getInt32Ty();
            }
            else if (sysNode->dType == Typing::DataType::d_REAL)
            {
                return Builder.getDoubleTy();
            }
            else if (sysNode->dType == Typing::DataType::d_BOOLEAN)
            {
                return Builder.getInt1Ty();
            }
        }
    }
    return nullptr;
}

void CodeGenerator::execute(const Interpreter* ipt, std::ofstream &Out)
{
    // 主函数
    auto* mainFunction = llvm::Function::Create(
            llvm::FunctionType::get(Builder.getVoidTy(), false),
            llvm::GlobalValue::InternalLinkage,
            "main",
            Module
    );
    auto* mainBlock = llvm::BasicBlock::Create(
            Context,
            "main_entry",
            mainFunction
    );
    Builder.SetInsertPoint(mainBlock);

    // 根据符号表内容构造全局变量和常量
    setupGlobal(ipt->symbol_table);

    // 生成主函数代码
    genCode(ipt->main_entry, false);

    // 主函数返回void
    Builder.CreateRet(nullptr);

    std::string IRCode;
    llvm::raw_string_ostream IR(IRCode);
    IR << *Module;
    IR.flush();
    std::cout << IRCode << std::endl;

    Out << IRCode;
    Out.close();
}

void CodeGenerator::setupGlobal(ST* SymbolTable)
{
    for (const auto& it : SymbolTable->Table)
    { // 遍历符号表中每个定义
        std::string Name = it.first;
        Typing::Node* tNode = it.second;

        if (tNode->nType == Typing::NodeType::t_CONSTANT)
        { // 处理constant
            auto* constNode = dynamic_cast<Typing::constNode*>(tNode);
            switch (constNode->m_Sys->dType)
            {
                case Typing::DataType::d_INTEGER:
                    GlobalConst[Name] = llvm::ConstantInt::get(Builder.getInt32Ty(),
                                                                constNode->m_Constant.iValue, true);
                    break;
                case Typing::DataType::d_BOOLEAN:
                    GlobalConst[Name] = llvm::ConstantInt::get(Builder.getInt1Ty(),
                                                               constNode->m_Constant.bValue);
                    break;

                case Typing::DataType::d_REAL:
                    GlobalConst[Name] = llvm::ConstantFP::get(Builder.getDoubleTy(),
                                                              constNode->m_Constant.dValue);
                    break;
            }
        }
        else
        { // 添加全局变量
            llvm::Type* Type = toLLVM(tNode);
            if (Type)
            {
                GlobalVariables[Name] = Builder.CreateAlloca(Type, nullptr, Name);
            }
        }
    }
}

/*
 * getVarByAddr：返回变量时是否要返回地址，否则返回其值（加个load语句）
 */
llvm::Value *CodeGenerator::genCode(AST::Node *ASTNode, bool getVarByAddr)
{
    if (!ASTNode) return nullptr;
    switch (ASTNode->m_Attribute)
    {
        case AST::Attribute::Identifier:
        {
            llvm::Value* ret;
            std::string Name = ASTNode->m_Identifier.Name;
            // 先找常数
            ret = GlobalConst[Name];
            if (ret) return ret;
            // 再找变量
            ret = GlobalVariables[Name];
            if (ret)
            {
                if (getVarByAddr) return ret;
                else return Builder.CreateLoad(ret, Name);
            }
            break;
        }
        case AST::Attribute::Constant:
        {
            switch (ASTNode->m_Constant.Type)
            {
                case AST::ConstantType::Integer:
                    return llvm::ConstantInt::get(Builder.getInt32Ty(), ASTNode->m_Constant.iValue, true);
                case AST::ConstantType::Real:
                    return llvm::ConstantFP::get(Builder.getDoubleTy(), ASTNode->m_Constant.dValue);
                case AST::ConstantType::Boolean:
                    return llvm::ConstantInt::get(Builder.getInt1Ty(), ASTNode->m_Constant.bValue, false);
                case AST::ConstantType::Char: // 字符用ASCII表示，所以相当于8bit整数
                    return llvm::ConstantInt::get(Builder.getInt8Ty(), ASTNode->m_Constant.cValue, false);
            }
        }
        case AST::Attribute::Operation:
        {
            switch (ASTNode->m_Operation.Operator)
            {
                case WHILE:
                {
                    auto* LOOP_Condition_Block = llvm::BasicBlock::Create(Context, "loop_condition", Builder.GetInsertBlock()->getParent());
                    auto* LOOP_Body_Block = llvm::BasicBlock::Create(Context, "loop_body", Builder.GetInsertBlock()->getParent());
                    auto* After_Block = llvm::BasicBlock::Create(Context, "after", Builder.GetInsertBlock()->getParent());

                    // 进入条件判断
                    Builder.CreateBr(LOOP_Condition_Block);
                    Builder.SetInsertPoint(LOOP_Condition_Block);
                    // 判断条件
                    Builder.CreateCondBr(
                            genCode(ASTNode->m_Operation.List_Operands[0], false),
                            LOOP_Body_Block, After_Block
                    );
                    // 循环体
                    Builder.SetInsertPoint(LOOP_Body_Block);
                    genCode(ASTNode->m_Operation.List_Operands[1], getVarByAddr);
                    // 无条件跳转到条件判断
                    Builder.CreateBr(LOOP_Condition_Block);
                    // 结束while语句
                    Builder.SetInsertPoint(After_Block);
                    break;
                }
                case TO: case DOWNTO:
                { // for循环
                    int Operator = ASTNode->m_Operation.Operator;
                    // 初始化
                    llvm::Value* IndexVariable = genCode(ASTNode->m_Operation.List_Operands[0], true);
                    llvm::Value* BoundaryValue = genCode(ASTNode->m_Operation.List_Operands[2], false); // 边界值
                    llvm::Value* IndexValue = genCode(ASTNode->m_Operation.List_Operands[1], false); // 其实值
                    Builder.CreateStore(
                    /* Value = */ IndexValue,
                    /* Ptr   = */ IndexVariable
                    );
                    // loop区域
                    auto* LOOP_Condition_Block = llvm::BasicBlock::Create(Context, "loop_condition", Builder.GetInsertBlock()->getParent());
                    auto* LOOP_Body_Block = llvm::BasicBlock::Create(Context, "loop_body", Builder.GetInsertBlock()->getParent());
                    auto* After_Block = llvm::BasicBlock::Create(Context, "after", Builder.GetInsertBlock()->getParent());
                    // 进入loop区域
                    Builder.CreateBr(LOOP_Condition_Block);
                    Builder.SetInsertPoint(LOOP_Condition_Block);
                    llvm::Value* Condition; // loop条件
                    IndexValue = Builder.CreateLoad(IndexVariable, IndexVariable->getName());
                    if (Operator == TO)
                    {
                        Condition = Builder.CreateICmp(llvm::CmpInst::Predicate::ICMP_SLE, IndexValue, BoundaryValue, "ile_tmp_");
                    }
                    else if (Operator == DOWNTO)
                    {
                        Condition = Builder.CreateICmp(llvm::CmpInst::Predicate::ICMP_SGE, IndexValue, BoundaryValue, "ige_tmp_");
                    }
                    // 如果满足loop条件，则进入循环体，否则跳出
                    Builder.CreateCondBr(Condition, LOOP_Body_Block, After_Block);
                    // 循环体代码
                    Builder.SetInsertPoint(LOOP_Body_Block);

                    genCode(ASTNode->m_Operation.List_Operands[3], getVarByAddr);

                    // index variable自增或自减
                    if (Operator == TO)
                    {
                        IndexValue = Builder.CreateAdd(IndexValue, llvm::ConstantInt::get(Builder.getInt32Ty(), 1, true), "iadd_tmp_");
                        Builder.CreateStore(
                                IndexValue,
                                IndexVariable
                        );
                    }
                    else if (Operator == DOWNTO)
                    {
                        IndexValue = Builder.CreateSub(IndexValue, llvm::ConstantInt::get(Builder.getInt32Ty(), 1, true), "isub_tmp_");
                        Builder.CreateStore(
                                IndexValue,
                                IndexVariable
                        );
                    }
                    // 无条件跳到loop条件判断
                    Builder.CreateBr(LOOP_Condition_Block);
                    // 循环语句结束
                    Builder.SetInsertPoint(After_Block);
                    break;
                }
                case REPEAT:
                {
                    llvm::BasicBlock* LOOP_Block = llvm::BasicBlock::Create(Context, "loop", Builder.GetInsertBlock()->getParent());
                    llvm::BasicBlock* After_Block = llvm::BasicBlock::Create(Context, "after", Builder.GetInsertBlock()->getParent());
                    // 先进入loop区域
                    Builder.CreateBr(LOOP_Block);
                    Builder.SetInsertPoint(LOOP_Block);
                    // loop区域代码块
                    genCode(ASTNode->m_Operation.List_Operands[1], getVarByAddr);

                    // 判断until条件
                    auto* Condition = genCode(ASTNode->m_Operation.List_Operands[0], false);
                    Builder.CreateCondBr(Condition, After_Block, LOOP_Block); // 如果条件满足，就跳出循环，否则回到开头

                    // 结束unti语句的代码
                    // 后面的代码写到after block
                    Builder.SetInsertPoint(After_Block);
                    break;
                }
                // 数值比较
                case _GE_: case _GT_: case _LE_: case _LT_: case EQUAL: case UNEQUAL:
                {
                    int Operator = ASTNode->m_Operation.Operator;
                    llvm::Value* LeftValue = genCode(ASTNode->m_Operation.List_Operands[0], false);
                    llvm::Value* RightValue = genCode(ASTNode->m_Operation.List_Operands[1], false);
                    if (LeftValue->getType() == Builder.getDoubleTy() || RightValue->getType() == Builder.getDoubleTy())
                    { // 二者之一为浮点数，则结果就为浮点数
                        // SIToFP: Signed Integer to Float Point
                        // 如果本身为浮点数，那么相当于没有操作
                        LeftValue = Builder.CreateSIToFP(LeftValue, Builder.getDoubleTy(), "si2double_tmp_");
                        RightValue = Builder.CreateSIToFP(RightValue, Builder.getDoubleTy(), "si2double_tmp_");

                        if (Operator == _GE_) return Builder.CreateFCmp(
                                llvm::CmpInst::Predicate::FCMP_OGE,
                                LeftValue, RightValue,
                                "fge_tmp_");
                        if (Operator == _GT_) return Builder.CreateFCmp(llvm::CmpInst::Predicate::FCMP_OGT, LeftValue, RightValue,"fgt_tmp_");
                        if (Operator == _LE_) return Builder.CreateFCmp(llvm::CmpInst::Predicate::FCMP_OLE, LeftValue, RightValue,"fle_tmp_");
                        if (Operator == _LT_) return Builder.CreateFCmp(llvm::CmpInst::Predicate::FCMP_OLT, LeftValue, RightValue,"flt_tmp_");
                        if (Operator == EQUAL) return Builder.CreateFCmp(llvm::CmpInst::Predicate::FCMP_OEQ,LeftValue, RightValue,"feq_tmp_");
                        if (Operator == UNEQUAL) return Builder.CreateFCmp(llvm::CmpInst::Predicate::FCMP_ONE, LeftValue, RightValue,"fne_tmp_");
                    }
                    else
                    {
                        if (Operator == _GE_) return Builder.CreateICmp(llvm::CmpInst::Predicate::ICMP_SGE, LeftValue, RightValue,"ige_tmp_");
                        if (Operator == _GT_) return Builder.CreateICmp(llvm::CmpInst::Predicate::ICMP_SGT, LeftValue, RightValue,"igt_tmp_");
                        if (Operator == _LE_) return Builder.CreateICmp(llvm::CmpInst::Predicate::ICMP_SLE, LeftValue, RightValue,"ile_tmp_");
                        if (Operator == _LT_) return Builder.CreateICmp(llvm::CmpInst::Predicate::ICMP_SLT, LeftValue, RightValue,"ilt_tmp_");
                        if (Operator == EQUAL) return Builder.CreateICmp(llvm::CmpInst::Predicate::ICMP_EQ,LeftValue, RightValue,"ieq_tmp_");
                        if (Operator == UNEQUAL) return Builder.CreateICmp(llvm::CmpInst::Predicate::ICMP_NE, LeftValue, RightValue,"ine_tmp_");
                    }
                    break;
                }
                case IF:
                {
                    auto* Condition = genCode(ASTNode->m_Operation.List_Operands[0], false);
                    auto* IF_Block  = llvm::BasicBlock::Create(Context, "if", Builder.GetInsertBlock()->getParent());
                    auto* ELSE_Block = llvm::BasicBlock::Create(Context, "else", Builder.GetInsertBlock()->getParent());
                    auto* After_Block = llvm::BasicBlock::Create(Context, "after", Builder.GetInsertBlock()->getParent());

                    Builder.CreateCondBr(Condition, IF_Block, ELSE_Block); // 条件跳转语句

                    // 生成IF语句部分的代码
                    Builder.SetInsertPoint(IF_Block);
                    genCode(ASTNode->m_Operation.List_Operands[1], getVarByAddr);
                    // jump to After_Block
                    Builder.CreateBr(After_Block);

                    // 生成ELSE语句部分的代码
                    Builder.SetInsertPoint(ELSE_Block);
                    // 如果有Else部分
                    if (ASTNode->m_Operation.NumOperands == 3)
                    {
                        genCode(ASTNode->m_Operation.List_Operands[2], getVarByAddr);
                    }
                    // jump to After_Block
                    Builder.CreateBr(After_Block);

                    // 后面代码的内容全在After Block中
                    Builder.SetInsertPoint(After_Block);
                    break;
                }
                // 一元布尔运算
                case NOT:
                {
                    return Builder.CreateNot(genCode(ASTNode->m_Operation.List_Operands[0], false), "not_tmp_");
                }
                // 二元布尔运算
                case AND: case OR:
                {
                    int Operator = ASTNode->m_Operation.Operator;
                    auto* Left = ASTNode->m_Operation.List_Operands[0];
                    auto* Right = ASTNode->m_Operation.List_Operands[1];
                    if (Operator == AND) return Builder.CreateAnd(genCode(Left, false), genCode(Right, false), "and_tmp_");
                    if (Operator == OR) return Builder.CreateOr(genCode(Left, false), genCode(Right, false), "or_tmp_");
                }
                // 二元算数运算
                case PLUS: case MUL: case MINUS: case DIV: case MOD:
                {
                    int Operator = ASTNode->m_Operation.Operator;
                    if (Operator == MINUS && ASTNode->m_Operation.NumOperands == 1)
                    { // 取负
                        llvm::Value* Value = genCode(ASTNode->m_Operation.List_Operands[0], false);
                        if (Value->getType() == Builder.getInt32Ty()) return Builder.CreateNeg(Value, "ineg_tmp_");
                        if (Value->getType() == Builder.getDoubleTy()) return Builder.CreateFNeg(Value, "fneg_tmp_");
                        break;
                    }
                    llvm::Value* LeftValue = genCode(ASTNode->m_Operation.List_Operands[0], false);
                    llvm::Value* RightValue = genCode(ASTNode->m_Operation.List_Operands[1], false);
                    if (LeftValue->getType() == Builder.getDoubleTy() || RightValue->getType() == Builder.getDoubleTy())
                    {   // 二者之一为浮点数，则结果就为浮点数
                        // SIToFP: Signed Integer to Float Point
                        // 如果本身为浮点数，那么相当于没有操作
                        LeftValue = Builder.CreateSIToFP(LeftValue, Builder.getDoubleTy(), "si2double_tmp_");
                        RightValue = Builder.CreateSIToFP(RightValue, Builder.getDoubleTy(), "si2double_tmp_");
                        // 浮点数运算
                        if (Operator == PLUS) return Builder.CreateFAdd(LeftValue, RightValue, "fadd_tmp_");
                        if (Operator == MINUS) return Builder.CreateFSub(LeftValue, RightValue, "fsub_tmp_");
                        if (Operator == MUL)  return Builder.CreateFMul(LeftValue, RightValue, "fmul_tmp_");
                        if (Operator == DIV) return Builder.CreateFDiv(LeftValue, RightValue, "fdiv_tmp_");
                        if (Operator == MOD) return Builder.CreateFRem(LeftValue, RightValue, "fmod_tmp_");
                    }
                    else
                    { // 都是整数操作
                        if (Operator == PLUS) return Builder.CreateAdd(LeftValue, RightValue, "iadd_tmp_");
                        if (Operator == MINUS) return Builder.CreateSub(LeftValue, RightValue, "isub_tmp_");
                        if (Operator == MUL)  return Builder.CreateMul(LeftValue, RightValue, "imul_tmp_");
                        if (Operator == DIV) return Builder.CreateSDiv(LeftValue, RightValue, "idiv_tmp_");
                        if (Operator == MOD) return Builder.CreateSRem(LeftValue, RightValue, "fmod_tmp_");
                    }
                    break;
                }
                case ASSIGN:
                {
                    auto* Left = dynamic_cast<Typing::sysNode*>(ASTNode->m_Operation.List_Operands[0]->m_Type);
                    auto* LeftValue = genCode(ASTNode->m_Operation.List_Operands[0], true);
                    auto* RightValue = genCode(ASTNode->m_Operation.List_Operands[1], false);
                    if (Left->dType == Typing::DataType::d_REAL)
                    { // 左边为浮点数时，右边也要变成浮点数
                        RightValue = Builder.CreateSIToFP(RightValue, Builder.getDoubleTy(), "si2double_tmp_");
                    }

                    Builder.CreateStore(
                    /* Value =  */ RightValue,
                    /* Variable= */LeftValue
                    );
                    break;
                }
                case SEMI:
                {
                    genCode(ASTNode->m_Operation.List_Operands[0], getVarByAddr);
                    genCode(ASTNode->m_Operation.List_Operands[1], getVarByAddr);
                    break;
                }
                case ROUTINE_BODY:
                {
                    genCode(ASTNode->m_Operation.List_Operands[0], getVarByAddr);
                    break;
                }
                case SYS_PROC: case SYS_FUNCT:
                    { // 系统函数调用
                        // 函数名
                        std::string FunctionName = ASTNode->m_Operation.List_Operands[0]->m_Identifier.Name;
                        // 函数参数
                        if (FunctionName == "write" || FunctionName == "writeln")
                        {
                            std::vector<llvm::Value*> Params;
                            for (int i = 2;i < ASTNode->m_Operation.NumOperands; ++i)
                            {
                                llvm::Value* Param = genCode(ASTNode->m_Operation.List_Operands[i], false);
                                if (Param->getType() == Builder.getInt1Ty())
                                { // 这是一个bool类型，但是输出时按照integer
                                    Param = Builder.CreateIntCast(Param, Builder.getInt32Ty(), true, "bool2int_tmp_");
                                }
                                Params.emplace_back(Param);
                            }
                            callWrite((FunctionName == "writeln"), std::string(ASTNode->m_Operation.List_Operands[1]->m_Constant.sValue), Params);
                        }
                        else if (FunctionName == "read")
                        {
                            std::vector<llvm::Value*> Params;
                            for (int i = 2;i < ASTNode->m_Operation.NumOperands; ++i)
                            {
                                llvm::Value* Param = genCode(ASTNode->m_Operation.List_Operands[i], true);
                                Params.emplace_back(Param);
                            }
                            callRead(std::string(ASTNode->m_Operation.List_Operands[1]->m_Constant.sValue), Params);
                        }
                        break;
                    }
                }
        }
    }
    return nullptr;
}
