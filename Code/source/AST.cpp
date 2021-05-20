#include "AST.hpp"
#include "Typing.hpp"

namespace AST
{
    Node::Node(unsigned int Line, ValConstant& Cons)
        : m_Line(Line), m_Attribute(Attribute::Constant)
    {
        m_Constant = Cons;
    }
    Node::Node(unsigned int Line, char* Name, Attribute attribute)
        : m_Line(Line), m_Attribute(attribute)
    {
        if (attribute == Attribute::Identifier)
        {
            m_Identifier.Name = new char[strlen(Name)];
            strcpy(m_Identifier.Name, Name);
        }
        else if (attribute == Attribute::Typename)
        {
            m_Typename.Name = new char[strlen(Name)];
            strcpy(m_Typename.Name, Name);
        }
        else 
        {
            std::string msg = "Unknown attribute: ";
            msg.append(std::to_string(attribute));
            raiseError(msg.c_str());
        }
    }
    Node::Node(unsigned int Line, int Operator, std::vector<Node*>* List)
        : m_Line(Line), m_Attribute(Attribute::Operation)
    {
        m_Operation.Operator = Operator;
        m_Operation.NumOperands = List->size();
        m_Operation.List_Operands = new Node*[List->size()];
        for (int i = 0;i < List->size(); ++i)
        {
            m_Operation.List_Operands[i] = (*List)[i];
        }
    }
    Node::Node(unsigned int Line, int Operator, int NumOperands, ...)
        : m_Line(Line), m_Attribute(Attribute::Operation)
    {
        va_list ap;
        m_Operation.Operator = Operator;
        m_Operation.NumOperands = NumOperands;
        m_Operation.List_Operands = new Node*[NumOperands];
        va_start(ap, NumOperands);
        for (int i = 0;i < NumOperands; ++i)
        {
            m_Operation.List_Operands[i] = va_arg(ap, Node*);
        }
        va_end(ap);
    }
    void Node::add(Node* node)
    {
        m_Operation.NumOperands += 1;
        m_Operation.List_Operands = (Node **) realloc(m_Operation.List_Operands, 
                                                    m_Operation.NumOperands * sizeof(Node *));
        m_Operation.List_Operands[m_Operation.NumOperands - 1] = node;
    }
    void Node::add(std::vector<Node *>* List)
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
    Node::~Node()
    {
        if (m_Attribute == Attribute::Identifier && m_Identifier.Name)
        {
            delete m_Identifier.Name;
        }
        else if (m_Attribute == Attribute::Operation)
        {
            for (int i = 0;i < m_Operation.NumOperands; ++i)
            {
                delete m_Operation.List_Operands[i];
            }
            delete m_Operation.List_Operands;
        }
    }
}