//
// Created by 邱泽鸿 on 2021/6/15.
//

#include "CodeGenerator.hpp"
#include "yacc.tab.hpp"

auto CodeGenerator::Builder = llvm::IRBuilder<>(CodeGenerator::Context);

void CodeGenerator::genCode(AST::Node* p)
{
    if (p == nullptr) return ;
    switch (p->m_Attribute)
    {
        case AST::Attribute::Constant:
            switch (p->m_Constant.Type)
            {
                case AST::ConstantType::Integer: emitCode(2, "ldc", std::to_string(p->m_Constant.iValue).c_str()); break;
                case AST::ConstantType::Real: emitCode(2, "ldc", std::to_string(p->m_Constant.dValue).c_str()); break;
                case AST::ConstantType::Char: emitCode(2, "ldc", p->m_Constant.cValue); break;
                case AST::ConstantType::String: emitCode(2, "ldc", p->m_Constant.sValue); break;
                case AST::ConstantType::Boolean: emitCode(2, "ldc", std::to_string(p->m_Constant.bValue).c_str()); break;
            }
            break;
        case AST::Attribute::Identifier:
            emitCode(2, "lod", p->m_Identifier.Name);
            break;
        case AST::Attribute::Operation:
        {
            switch (p->m_Operation.Operator)
            {
                // 二院操作符
                case GE: case GT: case LE: case LT: case OR: case AND:
                case EQUAL: case UNEQUAL: case PLUS: case MINUS: case MOD:
                case MUL: case DIV:
                    genCode(p->m_Operation.List_Operands[0]);
                    genCode(p->m_Operation.List_Operands[1]);
                    // TODO: 把token变为字符串
//                    emitCode(1, "ge");
                    break;
                case SEMI:
                    genCode(p->m_Operation.List_Operands[0]);
                    genCode(p->m_Operation.List_Operands[1]);
                    break;
            }
        }

    }
}

llvm::Type *CodeGenerator::toLLVMType(AST::Node *node)
{
    Typing::Node* type = node->m_Type;
    if (!type)
    {   // 没有推出这个结点的类型/不存在类型
        std::stringstream msg;
        msg << "Unknown Type of AST Node (id = " << node->m_Id << ")";
        raiseError(msg.str());
    }
    switch (type->m_Type)
    {
        case Typing::NodeType::t_SYS_TYPE: case Typing::NodeType::t_CONSTANT:
        {
            Typing::sysNode* sysNode;
            if (type->m_Type == Typing::NodeType::t_SYS_TYPE)
            {
                sysNode = dynamic_cast<Typing::sysNode*>(type);
            }
            else if (type->m_Type == Typing::NodeType::t_CONSTANT)
            {
                sysNode = dynamic_cast<Typing::constNode*>(type)->m_Sys;
            }
            else
            {
                raiseError("Something wrong with the case here");
            }

            if (sysNode->m_DataType == Typing::DataType::d_BOOLEAN) return Builder.getInt1Ty();
            else if (sysNode->m_DataType == Typing::DataType::d_CHAR) return Builder.getInt8Ty();
            else if (sysNode->m_DataType == Typing::DataType::d_INTEGER) return Builder.getInt32Ty();
            else if (sysNode->m_DataType == Typing::DataType::d_REAL) return Builder.getDoubleTy();
        }
        case Typing::NodeType::t_ENUM:
        {
            return Builder.getInt32Ty();
        }
        case Typing::NodeType::t_ARRAY:
        {
            auto arrayType = dynamic_cast<Typing::arrayNode*>(type);
            if (arrayType->m_IdxType->m_Type == Typing::NodeType::t_ENUM)
            {   //  数组索引为enum
                arrayType->
                return llvm::ArrayType::get(toLLVMType(arrayType->m_EleType),
                                            )
            }
        }
    }
}
