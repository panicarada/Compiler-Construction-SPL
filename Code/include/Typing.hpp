#pragma once
#include "AST.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>


#define ALIGN_WIDTH 12


class ST; // 提前声明符号表类
namespace Typing
{
    enum NodeType
    {
        t_SYS_TYPE, // integer, real等
        t_ENUM, // 枚举类型，如(red, green, blue)
        t_RECORD, // 结构体
        t_ARRAY, // 数组
        t_RANGE, // 如1 .. 30, x .. y
        t_CONSTANT, // const part中定义的常量
        t_FUNCTION, // 函数
        t_PROCEDURE,    // 过程
        // ...
    };
    static std::string NodeType_toString(NodeType type)
    {
        switch (type)
        {
            case t_SYS_TYPE: return "sys_type";
            case t_ENUM: return "enum";
            case t_RECORD: return "record";
            case t_RANGE: return "range";
            case t_CONSTANT: return "constant";
            case t_FUNCTION: return "function";
            case t_PROCEDURE: return "procedure";
            default:
                raiseError("Unknown node type!");
        }
    }

    enum DataType
    {
        d_INTEGER,
        d_REAL,
        d_CHAR,
        d_STRING,
        d_BOOLEAN,
    };
    static std::string DataType_toString(DataType type)
    {
        switch (type)
        {
            case d_INTEGER: return "integer";
            case d_REAL: return "real";
            case d_CHAR: return "char";
            case d_STRING: return "string";
            case d_BOOLEAN: return "boolean";
            default:
                raiseError("Unknown data type!");
        }
    }

    class Node
    {
    public:
        NodeType m_Type;
        Node* prev = nullptr;
        Node* next = nullptr;
    public:
        static bool isEqual(Node* node1, Node* node2); // 检查类型是否一致
        virtual std::string toString(int& hPos) const = 0; // 输出类型信息
        // hPos当前光标水平位置
    };
    class enumNode : public Node
    {
    public:
        std::vector<std::string>* m_List = nullptr;
    public:
        enumNode(std::vector<std::string>* List)
        {
            m_Type = NodeType::t_ENUM;
            m_List = List;
            // 为了便于类型判断，我们对enum类型列表进行排序
            // std::sort(m_List->begin(), m_List->end(), [](std::string& a, std::string& b) -> bool{
            //     if (std::strcmp(a.c_str(), b.c_str()) > 0) return true;
            //     return false;
            // });
        }
        virtual std::string toString(int& hPos) const override
        {
            std::stringstream ss;
            ss << std::setfill(' ') << std::setw(ALIGN_WIDTH) << "enum";
            ss << std::setfill(' ') << std::setw(ALIGN_WIDTH);
            for (auto & it : *m_List)
            {
                ss << it << ", ";
            }
            return ss.str();
        }
    };


    class sysNode : public Node
    {
    public: 
        std::string m_Keyword; // 为了方便输出，把类型的enum变为字符串
        DataType m_DataType;
    public:
        virtual std::string toString(int& hPos) const override
        {
            std::stringstream ss;
            ss << std::setfill(' ') << std::setw(ALIGN_WIDTH) << "sys_type";
            ss << std::setfill(' ') << std::setw(ALIGN_WIDTH) << m_Keyword;
            return ss.str();
        }
        sysNode(DataType&& datatype)
        {
            m_DataType = datatype;
            m_Type = NodeType::t_SYS_TYPE;
            m_Keyword =   (m_DataType == DataType::d_INTEGER)   ? "integer"
                        : (m_DataType == DataType::d_REAL)    ? "real"
                        : (m_DataType == DataType::d_CHAR)    ? "char"
                        : (m_DataType == DataType::d_STRING)  ? "string"
                        : (m_DataType == DataType::d_BOOLEAN) ? "boolean"
                        : "N/A";
        }
    };

    class recordNode : public Node
    {
    public:
        std::map<std::string, Node*>* m_Field = nullptr; // 成员名字到类型的映射
    public:
        Node* getAttribute(std::string str) const
        {
            if (m_Field->find(str) != m_Field->end())
            {
                return (*m_Field)[str];
            }
            return nullptr;
        }
        recordNode(std::map<std::string, Node*>* Field)
        {
            m_Type = NodeType::t_RECORD;
            m_Field = Field;
        }
        virtual std::string toString(int& hPos) const override;
    };


    class constNode : public Node
    {
    public:
        sysNode* m_Sys = nullptr;
        AST::ValConstant m_Constant;
        constNode(Node* Sys, AST::ValConstant Constant)
        {
            if (Sys->m_Type != NodeType::t_SYS_TYPE)
            {   
                raiseError("错误的构造函数输入，只能接受sys类型");
            }
            m_Type = NodeType::t_CONSTANT;
            m_Sys = dynamic_cast<sysNode*>(Sys);
            m_Constant = Constant;
            // switch (Constant.Type)
            // {
            //     case AST::ConstantType::Integer: m_DataType = DataType::d_INTEGER; m_Keyword = "integer"; break;
            //     case AST::ConstantType::Real:    m_DataType = DataType::d_REAL; m_Keyword = "real"; break;
            //     case AST::ConstantType::Boolean: m_DataType = DataType::d_BOOLEAN; m_Keyword = "boolean"; break;
            //     case AST::ConstantType::Char:    m_DataType = DataType::d_CHAR; m_Keyword = "char"; break;
            //     case AST::ConstantType::String:  m_DataType = DataType::d_STRING; m_Keyword = "string"; break;
            //     default:
            //         raiseError("未知的常数类型");
            // }
        }
        virtual std::string toString(int& hPos) const override;
    };
    class rangeNode : public Node
    {
    public:
        int m_LowerBound; 
        int m_UpperBound;
        rangeNode(Node* LowerBound, Node* UpperBound)
        {
            if (LowerBound->m_Type != NodeType::t_CONSTANT)
            {
                raiseError("Invalid range!")
            }
            m_Type = NodeType::t_RANGE;
            AST::ValConstant temp_lower = dynamic_cast<constNode*>(LowerBound)->m_Constant;
            AST::ValConstant temp_upper = dynamic_cast<constNode*>(UpperBound)->m_Constant;
            
            if (temp_lower.Type != AST::ConstantType::Integer || temp_upper.Type != AST::ConstantType::Integer)
            {
                raiseError("range只支持整型范围！");
            }
            m_LowerBound = temp_lower.iValue;
            m_UpperBound = temp_upper.iValue;
        }
        virtual std::string toString(int& hPos) const override;
    };

    class arrayNode : public Node
    {
    public:
        Node* m_EleType = nullptr; // 元素类型
        Node* m_IdxType = nullptr; // 索引类型
        arrayNode(Node* IdxType, Node* EleType)
            : m_IdxType(IdxType), m_EleType(EleType)
        {
            m_Type = NodeType::t_ARRAY;
        }
        virtual std::string toString(int& hPos) const override;
    };


    class functNode : public Node
    {
    public:
        std::string m_name; // 函数名字
        std::vector<std::pair<std::string, bool>> m_Params;    // 参数字符串表，主要是反应参数顺序
        Node* m_resType = nullptr; // 返回类型
        ST* m_val_table = nullptr;    // 形参表
        ST* m_var_table = nullptr;    // 引用参数表
        AST::Node* m_body; // 函数体的指针，指向<Routine-Body>
    public:
        functNode(std::string name, Node* resType, AST::Node* body);
        void addParam(bool isVar, const std::string& paramName, Node* node, unsigned int line);
        virtual std::string toString(int& hPos) const override;
    };
    class procNode : public Node 
    {   // 只是函数去掉返回类型而已
    public:
        std::string m_name; // 过程名字
        std::vector<std::pair<std::string, bool>> m_Params;    // 参数字符串表，主要是反应参数顺序
        ST* m_val_table;    // 形参表
        ST* m_var_table;    // 引用参数表
        AST::Node* m_body;  // 过程体的指针，指向<Routine-body>
    public:
        procNode(std::string name, AST::Node* body);
        void addParam(bool isVar, const std::string& paramName, Node* node, unsigned int line);
        virtual std::string toString(int& hPos) const override;
    };
};