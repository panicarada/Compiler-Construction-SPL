#include <stdio.h> 
#include "Interpreter.hpp"
#include <unordered_map>
#include "Graph.hpp"
#include "yacc.tab.h"


namespace Interpreter
{
    TypeNode* getType(Node* p, bool isVarPart)
    { 
        switch (p->m_Type)
        {
        case NodeType::Constant:
            switch (p->m_Constant.Type)
            {
            case ConstantType::Integer:
                return new sysNode("integer", DataType::d_SYS_TYPE);
            case ConstantType::Real:
                return new sysNode("real", DataType::d_SYS_TYPE);
            case ConstantType::Boolean:
                return new sysNode("boolean", DataType::d_SYS_TYPE);
            case ConstantType::Char:
                return new sysNode("char", DataType::d_SYS_TYPE);
            case ConstantType::String:
                return new sysNode("string", DataType::d_SYS_TYPE);
            default:
                std::cout << "Unknown constant type!" << std::endl;
                exit(1);
            }
            break;
        case NodeType::Typename:
            return st.get(p->m_Typename.Name);
            break;
        case NodeType::Operation:
            switch (p->m_Operation.Operator)
            {
            case ROUTINE:
                for (int i = 0; i < p->m_Operation.NumOperands; ++i)
                {
                    getType(p->m_Operation.List_Operands[i]);
                }
                break;
            case ROUTINE_HEAD:
                for (int i = 0;i < p->m_Operation.NumOperands; ++i)
                {
                    getType(p->m_Operation.List_Operands[i]);
                }
                break;
            // 加入新类型
            case TYPE_PART:
                // 见test3.spl以及对应的AST
                for (int i = 0;i < p->m_Operation.NumOperands; ++i)
                {
                    getType(p->m_Operation.List_Operands[i]);
                }
                break;
            case TYPE: // 左边是类型名字，右边是这个名字对应的类型statement
                // 见test3.spl以及对应的AST
                st.insert(p->m_Operation.List_Operands[0]->m_Typename.Name,
                          getType(p->m_Operation.List_Operands[1]));
                break;
        
            // 加入(变量名， 类型指针)
            case VAR_PART: 
                for (int i = 0;i < p->m_Operation.NumOperands; ++i)
                { // 见test3.spl以及对应的AST
                    getType(p->m_Operation.List_Operands[i], true);
                }
                break;
            case VAR: 
                if (isVarPart)
                { // var part部分的var，声明全局变量的类型
                    st.insert(p->m_Operation.List_Operands[1]->m_Identifier.Name,
                              getType(p->m_Operation.List_Operands[0]));
                }
                else
                { // 函数参数部分的var，声明参数的引用类型

                }
                break;
            case ENUM:
                {
                    auto enumSet = new std::set<std::string>();
                    for (int i = 0;i < p->m_Operation.NumOperands; ++i)
                    {
                        enumSet->insert(p->m_Operation.List_Operands[i]->m_Identifier.Name);
                    }
                    auto node = new enumNode(enumSet);
                    for (int i = 0;i < p->m_Operation.NumOperands; ++i)
                    {
                        st.insert(p->m_Operation.List_Operands[i]->m_Identifier.Name,
                                  node);
                    }
                    return node;
                }
                break;
            case RECORD:
                {
                    auto Field = new std::unordered_map<std::string, TypeNode*>();
                    TypeNode* temp;
                    
                    for (int i = 0;i < p->m_Operation.NumOperands; ++i)
                    {  
                        auto Child = p->m_Operation.List_Operands[i];
                        temp = getType(Child->m_Operation.List_Operands[0]);
                        // 见test3.spl的AST
                        for (int j = 1; j < Child->m_Operation.NumOperands; ++j)
                        {
                            std::string Name = Child->m_Operation.List_Operands[j]->m_Identifier.Name;
                            (*Field)[Name] = temp;
                        }
                    }
                    return new recordNode(Field);
                }
                break;
            case ARRAY:
                {
                    // 见test4.spl的AST
                    auto IdxType = getType(p->m_Operation.List_Operands[1]);
                    int hPos = 0;
                    auto EleType = getType(p->m_Operation.List_Operands[0]);
                    return new arrayNode(IdxType, EleType);
                }
            default:
                break;
            }
            break;
        default:
            break;
        }
        return NULL;
    }

    int draw(Node* p, std::ofstream& Out)
    {
        int rte, rtm;
        Graph::init();
        Graph::drawNode(p, 0, 0, rte, rtm);
        Graph::finish(Out);
        return 0;
    }

    int execute(Node* p, std::ofstream& Out)
    {
        getType(p);
        st.show();
        return draw(p, Out);
    }
}
