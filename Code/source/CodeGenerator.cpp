//
// Created by 邱泽鸿 on 2021/6/15.
//


#include "CodeGenerator.hpp"
#include "Typing.hpp"
#include "Interpreter.hpp"
#include "SystemFunctions.hpp"
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
            else if (sysNode->dType == Typing::DataType::d_CHAR)
            {
                return Builder.getInt8Ty();
            }
            else if (sysNode->dType == Typing::DataType::d_STRING)
            { // 字符串就是一个字符指针
                return Builder.getInt8PtrTy();
            }
        }
        case Typing::NodeType::t_RECORD:
        {
            auto* RecordNode = dynamic_cast<Typing::recordNode*>(tNode);
            std::vector<llvm::Type*> Members;
            for (auto Member_it = RecordNode->MemberIndex.begin(); Member_it != RecordNode->MemberIndex.end(); ++Member_it)
            { // 按顺序遍历每个成员，添加到Members中
                Members.emplace_back(toLLVM((*(RecordNode->m_Field))[*Member_it]));
            }
            auto* Record = llvm::StructType::get(Context, Members);

            return Record;
        }
        case Typing::NodeType::t_ARRAY:
        {
            auto* ArrayNode = dynamic_cast<Typing::arrayNode*>(tNode);
            // 数组中每个元素是一个pointer【->getPointerTo()】
            return llvm::ArrayType::get(toLLVM(ArrayNode->m_EleType), ArrayNode->getSize());
        }
    }
    return nullptr;
}

void CodeGenerator::execute(const Interpreter* ipt, std::ofstream &Out)
{
    /* 1. 初始化llvm */
    // 主函数
    auto* mainFunction = llvm::Function::Create(
            llvm::FunctionType::get(Builder.getVoidTy(), false),
            llvm::GlobalValue::ExternalLinkage,
            "main",
            Module
    );
    auto* mainBlock = llvm::BasicBlock::Create( // 主函数函数体
            Context,
            "main_entry",
            mainFunction
    );

    // 跳转到main block
    Builder.SetInsertPoint(mainBlock);

    RecordsStack.push(std::map<std::string, Typing::recordNode*>());


    /* 2. 根据符号表内容构造全局变量和常量，以及函数/过程的声明 */
    SymbolTable = ipt->symbol_table;
    setupGlobal();

    /* 3. 生成主函数代码 */
    genCode(ipt->main_entry, false);
    // 主函数返回void
    Builder.CreateRet(nullptr);

    /* 4. 函数/过程的定义 */
    // 生成函数的定义
    defineFunctions();
    // 生成过程的定义
    defineProcedures();

    /* 5. 生成所用到的系统函数的定义 */
    for (const auto& SystemFunction : CalledSystemFunctions)
    {
        SystemFunctions::define(SystemFunction, Context, Builder, Module);
    }

    /* 6. 生成中间码 */
    std::string IRCode;
    llvm::raw_string_ostream IR(IRCode);
    IR << *Module;
    IR.flush();
    std::cout << IRCode << std::endl;

    Out << IRCode;
    Out.close();
}

void CodeGenerator::setupGlobal()
{
    for (const auto& it : SymbolTable->Table)
    { // 遍历符号表中每个定义
        std::string Name = it.first;
        Typing::Node* tNode = it.second.top();

        if (tNode->nType == Typing::NodeType::t_PROCEDURE)
        { // 直接定义过程
            auto* ProcNode = dynamic_cast<Typing::procNode*>(tNode);
            auto ArgumentsType = std::vector<llvm::Type*>(); // 参数类型
            for (auto Param_it = ProcNode->m_Params.begin(); Param_it != ProcNode->m_Params.end(); Param_it++)
            {
                std::string ParamName = Param_it->first;
                bool isVar = Param_it->second;
                if (isVar)
                { // 否则，参数类型为相应的指针
                    ArgumentsType.push_back(toLLVM(ProcNode->m_var_table->get(ParamName, 0))->getPointerTo());
                }
                else
                { // 不是引用类型，则参数类型就是本身类型
                    ArgumentsType.push_back(toLLVM(ProcNode->m_val_table->get(ParamName, 0)));
                }
            }
            auto* FunctionProto = llvm::Function::Create(
                    llvm::FunctionType::get(Builder.getVoidTy(), ArgumentsType, true),
                    llvm::GlobalValue::InternalLinkage,
                    ProcNode->m_name,
                    Module
            );
            // 将函数声明保存起来，之后再插入代码【否则会打断main block】
            ProcedureSet.insert(std::make_pair(FunctionProto, ProcNode));
        }
        if (tNode->nType == Typing::NodeType::t_FUNCTION)
        { // 直接定义函数
            auto* FunctNode = dynamic_cast<Typing::functNode*>(tNode);
            auto ArgumentsType = std::vector<llvm::Type*>(); // 参数类型
            for (auto Param_it = FunctNode->m_Params.begin(); Param_it != FunctNode->m_Params.end(); Param_it++)
            {
                std::string ParamName = Param_it->first;
                bool isVar = Param_it->second;
                if (isVar)
                { // 否则，参数类型为相应的指针
                    ArgumentsType.push_back(toLLVM(FunctNode->m_var_table->get(ParamName, 0))->getPointerTo());
                }
                else
                { // 不是引用类型，则参数类型就是本身类型
                    ArgumentsType.push_back(toLLVM(FunctNode->m_val_table->get(ParamName, 0)));
                }
            }
            auto* FunctionProto = llvm::Function::Create(
                    llvm::FunctionType::get(toLLVM(FunctNode->m_resType), ArgumentsType, true),
                    llvm::GlobalValue::InternalLinkage,
                    FunctNode->m_name,
                    Module
            );


            // 将函数声明保存起来，之后再插入代码【否则会打断main block】
            FunctionSet.insert(std::make_pair(FunctionProto, FunctNode));
        }
        else if (tNode->nType == Typing::NodeType::t_CONSTANT)
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
                                                               (constNode->m_Constant.bValue) ? 1 : 0, true);
                    break;

                case Typing::DataType::d_REAL:
                    GlobalConst[Name] = llvm::ConstantFP::get(Builder.getDoubleTy(),
                                                              constNode->m_Constant.dValue);
                    break;
                case Typing::DataType::d_CHAR:
                    GlobalConst[Name] = llvm::ConstantInt::get(Builder.getInt8Ty(),
                                                               constNode->m_Constant.cValue);
                    break;
                case Typing::DataType::d_STRING:
                    GlobalConst[Name] = Builder.CreateGlobalStringPtr(constNode->m_Constant.sValue, "string_tmp_");
                    break;
            }
        }
        else
        { // 添加全局变量
            llvm::Type* Type = toLLVM(tNode);
            if (tNode->nType == Typing::NodeType::t_RECORD)
            {
                RecordsStack.top()[Name] = dynamic_cast<Typing::recordNode*>(tNode);
            }
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
        { /* 注意，这里绝对不可能是函数 */
            llvm::Value* ret;
            std::string Name = ASTNode->m_Identifier.Name;
            // 先找常数
            ret = GlobalConst[Name];
            if (ret != nullptr) return ret;
            // 再找本地函数参数
            if (!ArgumentsStack.empty())
            {
                auto& Arguments = ArgumentsStack.top();
                ret = Arguments[Name];
            }
            if (ret == nullptr)
            { // 如果不是常数，并且不属于函数参数
                ret = GlobalVariables[Name];
            }
            if (ret != nullptr)
            { // 判断是要返回变量地址还是要返回变量指向的值
                if (getVarByAddr) return ret;
                else
                {
                    return Builder.CreateLoad(ret, Name);
                }
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
                case AST::ConstantType::String:
                    return Builder.CreateGlobalStringPtr(ASTNode->m_Constant.sValue, "string_tmp_");
            }
        }
        case AST::Attribute::Operation:
        {
            switch (ASTNode->m_Operation.Operator)
            {
                case BRACKET:
                {
                    // 子节点为[数组名，索引]
                    auto* Array = genCode(ASTNode->m_Operation.List_Operands[0], true);

                    auto* Index = genCode(ASTNode->m_Operation.List_Operands[1], false); // 一定是llvm::Int32
                    auto* ret = Builder.CreateGEP(Array, {llvm::ConstantInt::get(Builder.getInt32Ty(), 0, false),
                                                          Index});

                    if (!getVarByAddr)
                    {
                        ret = Builder.CreateLoad(ret, "load_tmp_");
                    }
                    return ret;
                }
                case CASE_STMT:
                {
                    auto* TestedValue = genCode(ASTNode->m_Operation.List_Operands[0], false);
                    auto CaseList = ASTNode->m_Operation.List_Operands[1]->m_Operation;
                    int NumCases = CaseList.NumOperands;
                    std::vector<llvm::BasicBlock*> CaseConditionBlocks(NumCases);
                    std::vector<llvm::BasicBlock*> CaseBodyBlocks(NumCases);

                    auto* AfterBlock = llvm::BasicBlock::Create(Context, "after", Builder.GetInsertBlock()->getParent());
                    for (int i = 0;i < NumCases; ++i)
                    { // 先初始化
                        CaseConditionBlocks[i] = llvm::BasicBlock::Create(Context, "case_condition_" + std::to_string(i), Builder.GetInsertBlock()->getParent());
                        CaseBodyBlocks[i] = llvm::BasicBlock::Create(Context, "case_body_" + std::to_string(i), Builder.GetInsertBlock()->getParent());
                    }

                    Builder.CreateBr(CaseConditionBlocks[0]);

                    for (int i = 0;i < NumCases; ++i)
                    {
                        auto CaseUnit = CaseList.List_Operands[i]->m_Operation;
                        Builder.SetInsertPoint(CaseConditionBlocks[i]);
                        auto* TargetValue = genCode(CaseUnit.List_Operands[0], false);
                        llvm::Value* Condition;
                        // 如果之一为浮点数，则都变成浮点数
                        if (TestedValue->getType() == Builder.getDoubleTy() || TargetValue->getType() == Builder.getDoubleTy())
                        {
                            TestedValue = Builder.CreateSIToFP(TestedValue, Builder.getDoubleTy(), "si2double_tmp_");
                            TargetValue = Builder.CreateSIToFP(TargetValue, Builder.getDoubleTy(), "si2double_tmp_");
                            Condition = Builder.CreateFCmp(llvm::FCmpInst::Predicate::FCMP_OEQ, TestedValue, TargetValue, "feq_tmp_");
                        }
                        else
                        { // 都是整数
                            Condition = Builder.CreateICmp(llvm::ICmpInst::Predicate::ICMP_EQ, TestedValue, TargetValue, "ieq_tmp_");
                        }
                        // 如果条件满足，则跳到函数体，否则下一个条件
                        if (i < NumCases - 1)
                        {
                            Builder.CreateCondBr(Condition, CaseBodyBlocks[i], CaseConditionBlocks[i+1]);
                        }
                        else
                        {
                            Builder.CreateCondBr(Condition, CaseBodyBlocks[i], AfterBlock);
                        }


                        // 构造case函数体
                        Builder.SetInsertPoint(CaseBodyBlocks[i]);
                        genCode(CaseUnit.List_Operands[1], getVarByAddr);
                        // 跳转到after
                        Builder.CreateBr(AfterBlock);
                    }

                    // 结束case语句处理
                    Builder.SetInsertPoint(AfterBlock);
                    break;
                }
                case DOT:
                { // 访问数组
                    auto* Record = genCode(ASTNode->m_Operation.List_Operands[0], true);
                    std::string RecordName = ASTNode->m_Operation.List_Operands[0]->m_Identifier.Name;
                    // 获取成员名字
                    std::string Member = ASTNode->m_Operation.List_Operands[1]->m_Identifier.Name;

                    auto* RecordNode = RecordsStack.top()[RecordName]; // 本地找不到
                    if (!RecordNode) // 就到全局找
                    {
                        RecordNode = dynamic_cast<Typing::recordNode*>(SymbolTable->get(RecordName, 0));
                    }

                    int MemberIndex = RecordNode->getIndex(Member);
                    auto* ret = Builder.CreateStructGEP(Record, MemberIndex, "record_access_tmp_");
                    if (!getVarByAddr)
                    {
                        ret = Builder.CreateLoad(ret, "load_tmp_");
                    }
                    return ret;
                }
                case CALL_PROC:
                { // 调用过程
                    // 获取函数
                    std::string ProcedureName = ASTNode->m_Operation.List_Operands[0]->m_Identifier.Name;

                    auto* ProcedureNode = dynamic_cast<Typing::procNode*>(SymbolTable->get(ProcedureName, 0));
                    // 设置参数
                    CallerArguments.clear();
                    for (int i = 1;i < ASTNode->m_Operation.NumOperands; ++i)
                    {
                        if (ProcedureNode->m_Params[i-1].second)
                        { // 如果是引用类型，则输入地址
                            CallerArguments.push_back(genCode(ASTNode->m_Operation.List_Operands[i], true));
                        }
                        else
                        {
                            CallerArguments.push_back(genCode(ASTNode->m_Operation.List_Operands[i], false));
                        }
                    }
                    // 调用【这时候虽然过程没有定义，但是已经声明了】
                    Builder.CreateCall(Module->getFunction(ProcedureName), CallerArguments);
                    break;
                }
                case CALL_FUNCT:
                { // 调用函数
                    // 获取函数
                    std::string FunctionName = ASTNode->m_Operation.List_Operands[0]->m_Identifier.Name;

                    auto* FunctionNode = dynamic_cast<Typing::functNode*>(SymbolTable->get(FunctionName, 0));

                    // 设置参数
                    CallerArguments.clear();
                    for (int i = 1;i < ASTNode->m_Operation.NumOperands; ++i)
                    {
                        if (FunctionNode->m_Params[i-1].second)
                        { // 如果是引用类型，则输入地址
                            CallerArguments.push_back(genCode(ASTNode->m_Operation.List_Operands[i], true));
                        }
                        else
                        {
                            CallerArguments.push_back(genCode(ASTNode->m_Operation.List_Operands[i], false));
                        }
                    }
                    // 调用【这时候虽然函数没有定义，但是已经声明了】
                    return Builder.CreateCall(Module->getFunction(FunctionName), CallerArguments);
                }
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
//                    std::cout << "Left: "; LeftValue->getType()->print(llvm::dbgs()); std::cout << std::endl;
//                    std::cout << "Right: "; RightValue->getType()->print(llvm::dbgs()); std::cout << std::endl;

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
                        if (FunctionName == "write" || FunctionName == "writeln")
                        {
                            std::vector<llvm::Value*> Params;
                            for (int i = 1;i < ASTNode->m_Operation.NumOperands; ++i)
                            {
                                llvm::Value* Param = genCode(ASTNode->m_Operation.List_Operands[i], false);
                                if (Param->getType() == Builder.getInt1Ty())
                                { // 这是一个bool类型，但是输出时按照integer
                                    Param = Builder.CreateIntCast(Param, Builder.getInt32Ty(), true, "bool2int_tmp_");
                                }
                                Params.emplace_back(Param);
                            }
                            callWrite((FunctionName == "writeln"), Params);
                        }
                        else if (FunctionName == "read")
                        { // read格式为<read, 提示字符串, 待输入的参数>
                            std::vector<llvm::Value*> Params;
                            for (int i = 1;i < ASTNode->m_Operation.NumOperands; ++i)
                            {
                                llvm::Value* Param = genCode(ASTNode->m_Operation.List_Operands[i], true);
                                Params.emplace_back(Param);
                            }
                            callRead(Params);
                        }
                        else if (FunctionName == "odd" || FunctionName == "chr")
                        { // 输入整数
                            auto* Input = genCode(ASTNode->m_Operation.List_Operands[1], false);
                            SystemFunctions::declare(FunctionName, Builder, Module);
                            CalledSystemFunctions.insert(FunctionName);
                            auto* ret = Builder.CreateCall(Module->getFunction(FunctionName), {Input});
                            CallerArguments.clear();
                            return ret;
                        }
                        else if (FunctionName == "abs" || FunctionName == "sqr")
                        { // 输出和输入的类型一致
                            auto* Input = genCode(ASTNode->m_Operation.List_Operands[1], false);
                            std::string Name = FunctionName;
                            // 如果是浮点数，则fabs/fsqr，否则iabs/fsqr
                            if (Input->getType() == Builder.getInt32Ty())
                            {
                                Name = "i" + Name;
                            }
                            else if (Input->getType() == Builder.getDoubleTy())
                            {
                                Name = "f" + Name;
                            }
                            // 先声明
                            SystemFunctions::declare(Name, Builder, Module);
                            CalledSystemFunctions.insert(Name);
                            // 然后再调用
                            return Builder.CreateCall(Module->getFunction(Name), {Input});
                        }
                        else if (FunctionName == "sqrt")
                        {
                            auto* Input = genCode(ASTNode->m_Operation.List_Operands[1], false);
                            // 用到了fabs
                            SystemFunctions::declare("fabs", Builder, Module);
                            CalledSystemFunctions.insert("fabs");
                            SystemFunctions::declare("sqrt", Builder, Module);
                            CalledSystemFunctions.insert("sqrt");
                            // 然后再调用，需要注意的是，输入一定要为double
                            return Builder.CreateCall(Module->getFunction("sqrt"),
                                                      {Builder.CreateSIToFP(Input, Builder.getDoubleTy(), "si2double_tmp_")});
                        }
                        break;
                    }
                }
        }
    }
    return nullptr;
}

void CodeGenerator::defineFunctions()
{
    for (const auto& it : FunctionSet)
    {
        llvm::Function* Function = it.first;
        Typing::functNode* FunctNode = it.second;
        // 创建函数体代码区
        auto* FunctionBlock = llvm::BasicBlock::Create(Context, Function->getName(), Function);
        // 进入函数体代码区
        Builder.SetInsertPoint(FunctionBlock);
        std::map<std::string, llvm::Value*> ArgumentMap; // 当前函数的参数映射表

        RecordsStack.push(std::map<std::string, Typing::recordNode*>());
        // 加载参数
        int ArgumentIndex = 0;
        for (auto Argument_it = Function->arg_begin(); Argument_it != Function->arg_end(); Argument_it++)
        {
            auto Argument = dynamic_cast<llvm::Value*>(Argument_it);
            std::string Name = FunctNode->m_Params[ArgumentIndex].first;
            Typing::Node* Type;
            bool isVar = FunctNode->m_Params[ArgumentIndex].second;
            if (isVar)
            { // 这个参数是引用类型的话
                ArgumentMap[Name] = Argument; // 直接传递地址
                Type = FunctNode->m_var_table->get(Name, 0);
            }
            else
            { // 如果不是引用类型，
                Type = FunctNode->m_val_table->get(Name, 0);
                // 为本地参数分配空间
                ArgumentMap[Name] = Builder.CreateAlloca(Argument->getType(), nullptr, Name);
                // 再直接load值
                Builder.CreateStore(
                        Argument,
                        ArgumentMap[Name]
                );
            }
            if (Type->nType == Typing::NodeType::t_RECORD)
            {
                RecordsStack.top()[Name] = dynamic_cast<Typing::recordNode*>(Type);
            }
            ArgumentIndex ++;
        }
        // 最后，函数的名字也作为一个参数
        std::string FunctionName(Function->getName());
        ArgumentMap[FunctionName] = Builder.CreateAlloca(toLLVM(FunctNode->m_resType), nullptr, FunctionName);

        if (FunctNode->m_resType->nType == Typing::NodeType::t_RECORD)
        {
            RecordsStack.top()[FunctionName] = dynamic_cast<Typing::recordNode*>(FunctNode->m_resType);
        }

        ArgumentsStack.push(ArgumentMap);
        // 参数建立完成
        // 生成函数体代码
        genCode(FunctNode->m_body, true);

        // 弹出参数
        ArgumentsStack.pop();
        // 弹出结构体
        RecordsStack.pop();

        // 返回值
        auto* RetPtr = ArgumentMap[std::string(Function->getName())];
        Builder.CreateRet(Builder.CreateLoad(RetPtr, "load_tmp_"));
    }
}

void CodeGenerator::defineProcedures()
{
    for (const auto& it : ProcedureSet)
    {
        llvm::Function* Function = it.first;
        Typing::procNode* ProcedureNode = it.second;
        // 创建函数体代码区
        auto* FunctionBlock = llvm::BasicBlock::Create(Context, Function->getName(), Function);
        // 进入函数体代码区
        Builder.SetInsertPoint(FunctionBlock);
        std::map<std::string, llvm::Value*> ArgumentMap; // 当前函数的参数映射表

        RecordsStack.push(std::map<std::string, Typing::recordNode*>());
        // 加载参数
        int ArgumentIndex = 0;
        for (auto Argument_it = Function->arg_begin(); Argument_it != Function->arg_end(); Argument_it++)
        {
            auto Argument = dynamic_cast<llvm::Value*>(Argument_it);
            std::string Name = ProcedureNode->m_Params[ArgumentIndex].first;
            Typing::Node* Type;
            bool isVar = ProcedureNode->m_Params[ArgumentIndex].second;
            if (isVar)
            { // 这个参数是引用类型的话
                ArgumentMap[Name] = Argument; // 直接传递地址
                Type = ProcedureNode->m_var_table->get(Name, 0);
            }
            else
            { // 如果不是引用类型，
                Type = ProcedureNode->m_val_table->get(Name, 0);
                // 为本地参数分配空间
                ArgumentMap[Name] = Builder.CreateAlloca(Argument->getType(), nullptr, Name);
                // 再直接load值
                Builder.CreateStore(
                        Argument,
                        ArgumentMap[Name]
                );
            }
            if (Type->nType == Typing::NodeType::t_RECORD)
            {
                RecordsStack.top()[Name] = dynamic_cast<Typing::recordNode*>(Type);
            }
            ArgumentIndex ++;
        }

        ArgumentsStack.push(ArgumentMap);
        // 参数建立完成
        // 生成函数体代码
        genCode(ProcedureNode->m_body, true);

        // 弹出参数
        ArgumentsStack.pop();
        // 弹出结构体
        RecordsStack.pop();

        // 返回值为void
        Builder.CreateRet(nullptr);
    }
}
