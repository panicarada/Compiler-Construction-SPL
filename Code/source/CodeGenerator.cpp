//
// Created by 邱泽鸿 on 2021/6/15.
//

#include "CodeGenerator.hpp"
#include "yacc.tab.hpp"



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