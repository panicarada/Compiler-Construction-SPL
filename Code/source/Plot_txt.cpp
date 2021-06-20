#include "Plot_txt.hpp"
#include "Typing.hpp"
#include <sstream>

namespace Plot_txt
{
    void plotNode (
        AST::Node* p,
        int Col_Start, int Line_Start, // 绘制前所在column和line
        int& Col_End, // 绘制结束后所在Col（绘制一个节点不会换行）
        int& Col_Mid) // 绘制前后Col的中点
    {
        int Width, Height; // 节点的宽和高
        std::stringstream sText; // 节点的text
        int real_Col_Start; // real Col_Start【以所有子节点平均的Col为中心】
        int Kids_Col_End, Kids_Col_Mid;
        int Kids_Col_Start;
        if (!p) return;
        sText << p->m_Id << ": ";
        switch (p->m_Attribute)
        {
            case AST::Attribute::Constant:
                sText << "c(";
                switch (p->m_Constant.Type)
                {
                    case AST::ConstantType::Integer: sText << p->m_Constant.iValue; break;
                    case AST::ConstantType::Real: sText << p->m_Constant.dValue; break;
                    case AST::ConstantType::Char: sText << "'" << (char)p->m_Constant.cValue << "'"; break;
                    case AST::ConstantType::String: sText << "\"" << p->m_Constant.sValue << "\""; break;
                    case AST::ConstantType::Boolean: sText << (p->m_Constant.bValue ? "true" : "false"); break;
                    default:
                        std::stringstream msg;
                            msg << "Invalid Constant Type: " << p->m_Constant.Type << "!!";
                            raiseError(msg.str());
                }
                sText << ")";
                break;
            case AST::Attribute::Identifier:
                sText << "id(" << p->m_Identifier.Name << ")";
                break;
            case AST::Attribute::Typename:
                sText << p->m_Typename.Name;
                break;
            case AST::Attribute::Operation:
                switch (p->m_Operation.Operator)
                {
                    case _GE_: sText << "[>=]"; break;
                    case _GT_: sText << "[>]"; break;
                    case _LE_: sText << "[<=]"; break;
                    case _LT_: sText << "[<]"; break;
                    case OR: sText << "[or]"; break;
                    case AND: sText << "[and]"; break;
                    case NOT: sText << "[not]"; break;
                    case EQUAL: sText << "[=]"; break;
                    case UNEQUAL: sText << "[!=]"; break;
                    case PLUS: sText << "[+]"; break;
                    case MINUS: sText << "[-]"; break;
                    case MOD: sText << "[%]"; break; 
                    case MUL: sText << "[*]"; break;
                    case DIV: sText << "[/]"; break;
                    case CONST_PART: sText << "[const part]"; break;
                    case VAR_PART: sText << "[var part]"; break;
                    case ASSIGN: sText << "[:=]"; break;
                    case SEMI: sText << ";"; break;
                    case VAR: sText << "[var]"; break;
                    case ROUTINE_HEAD:
                        sText << "[Routine Head]"; break;
                    case ROUTINE_BODY:
                        sText << "[Routine Body]"; break;
                    case DOWNTO:
                        sText << "<Down to>"; break;
                    case TO:
                        sText << "<To>"; break;
                    case IF:
                        // 根处显示条件，并删去最后一个孩子（条件）
                        sText << "<if>"; break;
                    case BRACKET:
                        sText << "[~]"; break;
                    case DOT:
                        sText << "."; break;
                    case WHILE:
                        sText << "<while>"; break;
                    case CASE:
                        sText << "[case]"; break;
                    case CASE_STMT:
                        sText << "[case statement]"; break;
                    case CASE_LIST:
                        sText << "[case list]"; break;
                    case GOTO:
                        sText << "[goto]"; break;
                    case REPEAT:
                        sText << "[repeat-until]"; break;
                    case TYPE:
                        sText << "[Type]"; break;
                    case TYPE_PART:
                        sText << "[type part]"; break;
                    case VAL_PARAM:
                        sText << "[Value]"; break;
                    case VAR_PARAM:
                        sText << "[Variant]"; break;
                    case PARA_LIST:
                        sText << "[para list]"; break;
                    case FUNCTION_HEAD:
                        // Hacking Trick, 根处显示类型，并删去最后一个孩子（类型名）
                        sText << "function: " << p->m_Operation.List_Operands[p->m_Operation.NumOperands]->m_Identifier.Name;
                        break;
                    case PROCEDURE_HEAD:
                        // Hacking Trick, 根处显示类型，并删去最后一个孩子（类型名）
                        sText << "procedure: " << p->m_Operation.List_Operands[p->m_Operation.NumOperands]->m_Identifier.Name;
                        break;
                    case SUB_ROUTINE:
                        sText << "[subroutine]"; break;
                    case FUNCTION:
                        sText << "[Function]"; break;
                    case PROCEDURE:
                        sText << "[Procedure]"; break;
                    case SYS_PROC: case READ:
                        sText << "[Sys procedure]"; break;
                    case CALL_PROC:
                        sText << "[Call Procedure]"; break;
                    case LABEL_STMT:
                        sText << "[Label]"; break;
                    case SYS_FUNCT:
                        sText << "[Sys Function]"; break;
                    case CALL_FUNCT:
                        sText << "[Call Function]"; break;
                    case FIELD_DECL:
                        sText << "[Field Decl]"; break;
                    case RECORD:
                        sText << "[Record]"; break;
                    case DOTDOT:
                        sText << "[..]"; break;
                    case ENUM:
                        sText << "[Enum]"; break;
                    case ARRAY:
                        sText << "[Array]"; break;
                    case ROUTINE:
                        sText << "[Routine]"; break;
                    default:
                    {
                        std::stringstream msg;
                        msg << "未知的操作符\"" << p->m_Operation.Operator << "\"" << std::endl;
                        raiseError(msg.str());
                    }
                }
                break;
            }
            std::string Text = sText.str();
            // construct node text box
            calBox(Text, Width, Height);
            real_Col_Start = Col_Start;
            Col_End = Col_Start + Width;
            Col_Mid = Col_Start + Width / 2;

            // 如果node is leaf
            if (p->m_Attribute == AST::Attribute::Constant ||
                p->m_Attribute == AST::Attribute::Identifier ||
                p->m_Attribute == AST::Attribute::Typename ||
                p->m_Operation.NumOperands == 0)
            {
                drawBox(Text, real_Col_Start, Line_Start);
                return;
            }

            Kids_Col_Start = Col_Start;
            for (int i = 0;i < p->m_Operation.NumOperands; ++i)
            {
                plotNode(p->m_Operation.List_Operands[i], Kids_Col_Start, Line_Start + Height + LineGap, Kids_Col_End, Kids_Col_Mid);
                Kids_Col_Start = Kids_Col_End;
            }

            // total node width
            if (Width < Kids_Col_End - Col_Start)
            {
                real_Col_Start += (Kids_Col_End - Col_Start - Width) / 2;
                Col_End = Kids_Col_End;
                Col_Mid = (Col_Start + Kids_Col_End) / 2;
            }

            // draw node
            drawBox(Text, real_Col_Start, Line_Start);
            
            // draw arrows
            Kids_Col_Start = Col_Start;
            for (int i = 0;i < p->m_Operation.NumOperands; ++i)
            {
                plotNode(p->m_Operation.List_Operands[i], Kids_Col_Start, Line_Start+Height+LineGap, Kids_Col_End, Kids_Col_Mid);
                drawArrow(Col_Mid, Line_Start + Height, Kids_Col_Mid, Line_Start + Height + LineGap - 1);
                Kids_Col_Start = Kids_Col_End;
            }
    }
    char Graph[maxLine][maxCol];
    int GraphNumber = 0;
    void test(int Line, int Col)
    {
        bool Ok = true;
        if (Line < 0 || Line >= maxLine || Col < 0 || Col >= maxCol) Ok = false;
        if (!Ok)
        {
            std::cout << ("语法树太大，无法绘制成txt版本，请用运行python代码查看图片版的语法树") << std::endl;
        }
    }

    void init()
    {
        for (auto & i : Graph)
        {
            for (char & j : i)
            {
                j = ' ';
            }
        }
    }

    void finish(std::ofstream& Out)
    {
        int i, j;
        for (i = 0;i < maxLine; ++i)
        {
            for (j = maxCol - 1; j > 0 && Graph[i][j] == ' '; --j);
            Graph[i][maxCol - 1] = 0;
            if (j < maxCol - 1) Graph[i][j + 1] = 0;
            if (Graph[i][j] == ' ') Graph[i][j] = 0;
        }
        for (i = maxLine - 1; i > 0 && Graph[i][0] == 0; --i);

        Out << std::endl << "Graph " << GraphNumber++ << ":" << std::endl;
        for (j = 0;j <= i; ++j) 
            Out << std::endl << Graph[j];
        Out << std::endl;
    }

    void calBox(std::string& str, int& Width, int& Height)
    {
        Width = str.length() + ColGap;
        Height = 1;
    }

    void drawBox(std::string& str, int Col, int Line)
    {
        test(Line, Col + str.length() - 1 + ColGap);
        for (int i = 0;i < str.length(); ++i)
        {
            Graph[Line][Col + i + ColGap] = str.at(i);
        }
    }

    void drawArrow(int Col_Start, int Line_Start, int Col_End, int Line_End)
    {
        int Line_Mid;
        test(Line_Start, Col_Start);
        test(Line_End, Col_End);
        Line_Mid = (Line_Start + Line_End) / 2;
        while (Line_Start != Line_Mid)
        {
            Graph[Line_Start][Col_Start] = '|';
            if (Line_Start < Line_End)
                Line_Start ++;
            else 
                Line_Start --;
        }
        while (Col_Start != Col_End)
        {
            Graph[Line_Start][Col_Start] = '-';
            if (Col_Start < Col_End) 
                Col_Start ++;
            else
                Col_Start --;
        }
        while (Line_Start != Line_End)
        {
            Graph[Line_Start][Col_Start] = '|';
            if (Line_Start < Line_End)
                Line_Start ++;
            else 
                Line_Start --;
        }
        Graph[Line_Start][Col_Start] = '|';
    }
}