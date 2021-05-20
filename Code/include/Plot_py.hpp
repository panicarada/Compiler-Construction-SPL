#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "AST.hpp"
#include "yacc.tab.hpp"
 
namespace Plot_py
{
    void plotNode(AST::Node* p, int& id ,std::ofstream& Out)
    {   // id: 现在可用的标识符
        if (p == nullptr) return ;
        Out << "\n" << (id ++) << "\n";
        switch (p->m_Attribute)
        {
            case AST::Attribute::Constant:
                // 写入(id, 显示内容，node形状)
                switch (p->m_Constant.Type)
                {
                    case AST::ConstantType::Integer: Out << p->m_Constant.iValue; break;
                    case AST::ConstantType::Real: Out << p->m_Constant.dValue; break;
                    case AST::ConstantType::Char: Out << p->m_Constant.cValue; break;
                    case AST::ConstantType::String: Out << p->m_Constant.sValue; break;
                    case AST::ConstantType::Boolean: Out << (p->m_Constant.bValue ? "true" : "false"); break;
                    default:
                        std::stringstream msg;
                        msg << "Invalid Constant Type: " << p->m_Constant.Type << "!!";
                        raiseError(msg.str());
                } // terminal的形状用方形
                Out << "\nrect";
                break;
            case AST::Attribute::Identifier:
                Out << "id(" << p->m_Identifier.Name << ")\noval"; break;
            case AST::Attribute::Typename:
                Out << p->m_Typename.Name << "\noval"; break;
            case AST::Attribute::Operation:
                {
                    switch (p->m_Operation.Operator)
                    {
                        case GE: Out << ">="; break;
                        case GT: Out << ">"; break;
                        case LE: Out << "<="; break;
                        case LT: Out << "<"; break;
                        case OR: Out << "or"; break;
                        case AND: Out << "and"; break;
                        case NOT: Out << "not"; break;
                        case EQUAL: Out << "="; break;
                        case UNEQUAL: Out << "!="; break;
                        case PLUS: Out << "+"; break;
                        case MINUS: Out << "-"; break;
                        case MUL: Out << "*"; break;
                        case DIV: Out << "/"; break;
                        case CONST_PART: Out << "const-part"; break;
                        case VAR_PART: Out << "var-part"; break;
                        case ASSIGN: Out << ":="; break;
                        case SEMI: Out << ";"; break;
                        case VAR: Out << "var"; break;
                        case ROUTINE_HEAD:
                            Out << "Routine-Head"; break;
                        case ROUTINE_BODY:
                            Out << "Routine-Body"; break;
                        case DOWNTO:
                            Out << "Down-to"; break;
                        case TO:
                            Out << "To"; break;
                        case IF:
                            // 根处显示条件，并删去最后一个孩子（条件）
                            Out << "if"; break;
                            break;
                        case BRACKET:
                            Out << "~"; break;
                        case DOT:
                            Out << "."; break;
                        case WHILE:
                            Out << "while"; break;
                        case CASE:
                            Out << "case"; break;
                        case CASE_STMT:
                            Out << "case-statement"; break;
                        case CASE_LIST:
                            Out << "case-list"; break;
                        case GOTO:
                            Out << "goto"; break;
                        case REPEAT:
                            Out << "repeat-until"; break;
                        case TYPE:
                            Out << "Type"; break;
                        case TYPE_PART:
                            Out << "type-part"; break;
                        case VAL_PARAM:
                            Out << "Value"; break;
                        case VAR_PARAM:
                            Out << "Variant"; break;
                        case PARA_LIST:
                            Out << "para-list"; break;
                        case FUNCTION_HEAD:
                            // Hacking Trick, 根处显示类型，并删去最后一个孩子（类型名）
                            Out << "function:" << p->m_Operation.List_Operands[p->m_Operation.NumOperands]->m_Identifier.Name;
                            break;
                        case PROCEDURE_HEAD:
                            // Hacking Trick, 根处显示类型，并删去最后一个孩子（类型名）
                            Out << "procedure:" << p->m_Operation.List_Operands[p->m_Operation.NumOperands]->m_Identifier.Name;
                            break;
                        case SUB_ROUTINE:
                            Out << "subroutine"; break;
                        case FUNCTION:
                            Out << "Function"; break;
                        case ROUTINE:
                            Out << "Routine"; break;
                        case PROCEDURE:
                            Out << "Procedure"; break;
                        case SYS_PROC:
                            Out << "Sys-procedure"; break;
                        case PROC:
                            Out << "Procedure"; break;
                        case LABEL_STMT:
                            Out << "Label"; break;
                        case SYS_FUNCT:
                            Out << "Sys-Function"; break;
                        case FUNCT:
                            Out << "Function"; break;
                        case FIELD_DECL:
                            Out << "Field-Decl"; break;
                        case RECORD:
                            Out << "Record"; break;
                        case DOTDOT:
                            Out << ".."; break;
                        case ENUM:
                            Out << "Enum"; break;
                        case ARRAY:
                            Out << "Array"; break;
                        default:
                            break;
                    } // 操作符用diamond形状表示
                    Out << "\ndiamond";
                    // 遍历子节点，递归
                    int operation_id = id-1; // 当前操作节点的id
                    for (int i = 0;i < p->m_Operation.NumOperands; ++i)
                    {
                        Out << "\n*edge*\n" << operation_id << "\n" << id;
                        plotNode(p->m_Operation.List_Operands[i], id, Out);
                    }
                    break;
                    }
        }

    }
}