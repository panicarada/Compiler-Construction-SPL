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
#include <unordered_map>
enum NodeType
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

struct ValIdentifier
{
    char* Name; // Index to symbol table
};

class Node;

struct ValOperation
{
    int Operator;
    int NumOperands;
    Node** List_Operands;
};

class Node
{
public:
    NodeType m_Type;
    union 
    {
        ValConstant m_Constant;
        ValIdentifier m_Identifier;
        ValIdentifier m_Typename;
        ValOperation m_Operation;
    };
    Node(ValConstant& Cons)
        : m_Type(NodeType::Constant)
    {
        m_Constant = Cons;
    }
    Node(char* Name, NodeType Type)
        : m_Type(Type)
    {
        if (Type == NodeType::Identifier)
        {
            m_Identifier.Name = new char[strlen(Name)];
            strcpy(m_Identifier.Name, Name);
        }
        else if (Type == NodeType::Typename)
        {
            m_Typename.Name = new char[strlen(Name)];
            strcpy(m_Typename.Name, Name);
        }
        
    }
    Node(int Operator, std::vector<Node*>* List)
        : m_Type(NodeType::Operation)
    {
        m_Operation.Operator = Operator;
        m_Operation.NumOperands = List->size();
        m_Operation.List_Operands = new Node*[List->size()];
        for (int i = 0;i < List->size(); ++i)
        {
            m_Operation.List_Operands[i] = (*List)[i];
        }
    }
    inline void add(Node* node)
    {
        m_Operation.NumOperands += 1;
        m_Operation.List_Operands = (Node **) realloc(m_Operation.List_Operands, 
                                                      m_Operation.NumOperands * sizeof(Node *));
        m_Operation.List_Operands[m_Operation.NumOperands - 1] = node;
    }
    inline void add(std::vector<Node *>* List)
    {
        int Offset = m_Operation.NumOperands;
        m_Operation.NumOperands += List->size();
        m_Operation.List_Operands = (Node **) realloc(m_Operation.List_Operands,
                                                      m_Operation.NumOperands * sizeof(Node *));
        for (int i = 0;i < List->size(); ++i)
        {
            m_Operation.List_Operands[Offset + i] = (*List)[i];
        }
    }
    Node(int Operator, int NumOperands, ...)
        : m_Type(NodeType::Operation)
    {
        va_list ap;
        m_Operation.Operator = Operator;
        m_Operation.NumOperands = NumOperands;
        m_Operation.List_Operands = new Node*[NumOperands];
        // int i;
        va_start(ap, NumOperands);
        for (int i = 0;i < NumOperands; ++i)
        {
            m_Operation.List_Operands[i] = va_arg(ap, Node*);
        }
        va_end(ap);
    }
    ~Node()
    {
        if (m_Type == NodeType::Identifier && m_Identifier.Name)
        {
            delete m_Identifier.Name;
        }
        else if (m_Type == NodeType::Operation)
        {
            for (int i = 0;i < m_Operation.NumOperands; ++i)
            {
                delete m_Operation.List_Operands[i];
            }
            delete m_Operation.List_Operands;
        }
    }
};

union TableValue
{
    int iValue;
    double dValue;
};


static std::unordered_map<std::string, TableValue> SymbolTable;