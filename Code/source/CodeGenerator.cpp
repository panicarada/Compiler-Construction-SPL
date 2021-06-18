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
                    Builder.CreateStore(
                    /* Value =  */ genCode(ASTNode->m_Operation.List_Operands[1], false),
                    /* Variable= */genCode(ASTNode->m_Operation.List_Operands[0], true)
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
