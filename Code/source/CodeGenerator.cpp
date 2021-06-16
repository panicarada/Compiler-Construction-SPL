//
// Created by 邱泽鸿 on 2021/6/15.
//

#include "CodeGenerator.hpp"
#include "yacc.tab.hpp"


llvm::LLVMContext CodeGenerator::Context;
llvm::IRBuilder<> CodeGenerator::Builder(CodeGenerator::Context);

void CodeGenerator::genCode_init(Interpreter* ipt)
{
    mainFunction = llvm::Function::Create(
            llvm::FunctionType::get(Builder.getVoidTy(), false),    // no arg
            llvm::GlobalValue::InternalLinkage,
            "main",
            Module
    );
    llvm::BasicBlock* mainBlock = llvm::BasicBlock::Create(
            Context,
            "main_entry",
            mainFunction
    );

    setupIO();
    Builder.SetInsertPoint(mainBlock);

    auto SymbolTable = ipt->symbol_table;
    auto MainEntry = ipt->main_entry;
    // TODO: 把符号表中的数据加入CodeBlock
    isGlobal = true;
    CodeGeneration::CodeBlock* CodeBlock;

    // TODO: 检查main_entry
    genCode(MainEntry);
}
void CodeGenerator::setupIO()
{
    // write, read的输入都是是个pointer（用8位地址表示）
    std::vector<llvm::Type*> argumentTypes{Builder.getInt8PtrTy()};

    llvm::FunctionType* IOprototype = llvm::FunctionType::get(
        Builder.getInt32Ty(),
        argumentTypes,
        true    // is var
    );
    writeFunction = llvm::Function::Create(
            IOprototype,
            llvm::Function::ExternalLinkage,
            "write",
            Module
    );
    writeFunction->setCallingConv(llvm::CallingConv::C);

    readFunction = llvm::Function::Create(
            IOprototype,
            llvm::Function::ExternalLinkage,
            "read",
            Module
    );
    readFunction->setCallingConv(llvm::CallingConv::C);
}

llvm::Value* CodeGenerator::genCode(AST::Node* node)
{

    switch (node->m_Attribute)
    {
        case AST::Attribute::Constant:
        {
            if (node->m_Constant.Type == AST::ConstantType::Real)
            {
                return llvm::ConstantFP::get(Context, llvm::APFloat(node->m_Constant.dValue));
            }
            else if (node->m_Constant.Type == AST::ConstantType::Integer)
            {
                // TODO：常数类型补全
            }
        }
        case AST::Attribute::Identifier:
        {
        }
        case AST::Attribute::Operation:
        {
            switch (node->m_Operation.Operator)
            {
                case ASSIGN:
                {   // 赋值语句
                    auto Left = node->m_Operation.List_Operands[0];
                    auto Right = node->m_Operation.List_Operands[1];
                    auto LeftType = Left->m_Type;
                    if (LeftType->m_Type == Typing::NodeType::t_SYS_TYPE)
                    {   // 左边是变量名，id := ???
                        return Builder.CreateStore( // sto
                        /* value = */ genCode(Right),
                        /* address = */ getVar(Left->m_Identifier.Name)->Addr
                        );
                    }
                    else if (LeftType->m_Type == Typing::NodeType::t_ARRAY)
                    {   // array[index] := ????
                        // 子结点为(数组名称，下标)
                        auto Array = getVar(Left->m_Operation.List_Operands[0]->m_Identifier.Name);
                        llvm::Value* valOfIndex = genCode(node->m_Operation.List_Operands[1]);

                        // index = 下标 - lower_bound
                        valOfIndex = Builder.CreateSub(valOfIndex, ((CodeGeneration::ArrayType*)(Array->refType))->LowerBound);
                        std::vector<llvm::Value*> Index{Builder.getInt32(0), valOfIndex};
                        return Builder.CreateStore(
                        /* value = */ genCode(Right),
                        /* address = */ Builder.CreateGEP(Array->Addr, Index)
                        );
                    }
                    else if (LeftType->m_Type == Typing::NodeType::t_RECORD)
                    {   // record.field := ???
                        auto Record = getVar(Left->m_Operation.List_Operands[0]->m_Identifier.Name);
                        auto Member = Left->m_Operation.List_Operands[1]->m_Identifier.Name;
                        int valOfIndex = ((CodeGeneration::StructType*)(Record->refType))->getIndex(Member);
                        std::vector<llvm::Value*> Index{Builder.getInt32(0), Builder.getInt32(valOfIndex)};
                        return Builder.CreateStore(
                        /* value = */ genCode(Right),
                        /* address = */ Builder.CreateGEP(Record->Addr, Index)
                        );
                    }
                }
                case SEMI:
                {
                    // 先生成左边（第一条）语句代码
                    genCode(node->m_Operation.List_Operands[0]);
                    // 返回右边语句的类型
                    return genCode(node->m_Operation.List_Operands[1]);
                }
                case LABEL_STMT:
                {
                    int Label = node->m_Operation.List_Operands[0]->m_Constant.iValue;
                    llvm::Function* currentFunction = Builder.GetInsertBlock()->getParent();
                    llvm::BasicBlock* LabelBlock = llvm::BasicBlock::Create(
                            Context,
                            "label_" + std::to_string(Label),
                            currentFunction
                    );
                    CodeBlockList.back()->Labels.insert(std::make_pair(Label, LabelBlock));
                    Builder.CreateBr(LabelBlock);
                    Builder.SetInsertPoint(LabelBlock);
                    return genCode(node->m_Operation.List_Operands[1]);
                }
                case PLUS: return Builder.CreateFAdd(genCode(node->m_Operation.List_Operands[0]), genCode(node->m_Operation.List_Operands[1]), "addtmp");
                case MINUS:
                {
                    if (node->m_Operation.NumOperands == 1)
                    {   // 负号
                        return Builder.CreateFNeg(genCode(node->m_Operation.List_Operands[0]), "negtmp");
                    }
                    else
                    {   // 减法
                        return Builder.CreateFSub(genCode(node->m_Operation.List_Operands[0]), genCode(node->m_Operation.List_Operands[1]), "subtmp");
                    }
                }
                case MUL: return Builder.CreateFMul(genCode(node->m_Operation.List_Operands[0]), genCode(node->m_Operation.List_Operands[1]), "multmp");
                case LT:
                {
                    auto compare = Builder.CreateFCmpULT(genCode(node->m_Operation.List_Operands[0]), genCode(node->m_Operation.List_Operands[1]), "cmptmp");
                    return Builder.CreateUIToFP(compare, llvm::Type::getDoubleTy(Context), "booltmp");
                }

            }
        }

    }
}