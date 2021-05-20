#pragma once

// 这条是为了抑制lex产生的warning
// 'register' storage class specifier is deprecated 
// and incompatible with C++17 [-Wdeprecated-register]

#if __cplusplus > 199711L
#define register      // Deprecated in C++11.
#endif  // #if __cplusplus > 199711L

#include <iostream>
#include <vector>
#include <stdarg.h>
#include <map>

#define raiseError(...) {\
    std::cerr << "In " << __FILE_NAME__ << ". Line " << __LINE__ << ".\t"\
    << __VA_ARGS__ << std::endl;\
    exit(1);\
}


namespace Typing
{   // 提前声明Typing类型节点
    class Node;
}
namespace AST
{
    enum Attribute
    {
        Constant,
        Identifier,  
        Operation,
        Typename
    };

    enum ConstantType
    { 
        Integer, // integer
        Real, // real
        Char,
        String,
        Boolean
    };
    // 常数数据
    struct ValConstant
    {
        ConstantType Type;
        union {
            // Value of the constant
            int iValue;
            double dValue;
            char cValue;
            char* sValue;
            bool bValue;
        };
    };

    // 名字数据
    struct ValIdentifier
    {
        char* Name; // Index to symbol table
    };

    // 提前声明Node类
    class Node;
    // 操作数据
    struct ValOperation
    {
        int Operator; // 操作符，都是yacc.y中定义的token
        int NumOperands; // 子节点数目
        Node** List_Operands; // 子节点
    };

    class Node
    {
    public:
        Typing::Node* m_Type;   // 节点真正的数据类型，在语义分析之后获得
        int m_Id; // 在语法树上的ID，在语义分析之后获得，方便检查
    public:
        Attribute m_Attribute;
        unsigned int m_Line; // 所在行数
        union 
        {
            ValConstant m_Constant;
            ValIdentifier m_Identifier;
            ValIdentifier m_Typename;
            ValOperation m_Operation;
        };
        Node(unsigned int Line, ValConstant& Cons);
        Node(unsigned int Line, char* Name, Attribute attribute);
        Node(unsigned int Line, int Operator, std::vector<Node*>* List);
        Node(unsigned int Line, int Operator, int NumOperands, ...);
        void add(Node* node);
        void add(std::vector<Node *>* List);
        ~Node();
    };
}