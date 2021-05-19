#pragma once
#include "AST.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <unordered_map>


#define ALIGN_WIDTH 12


enum DataType
{
    d_SYS_TYPE, // integer, real等
    d_ENUM, // 枚举类型，如(red, green, blue)
    d_RECORD, // 结构体
    d_ARRAY, // 数组
    d_RANGE, // 如1 .. 30, x .. y
    d_CONSTANT, // const part中定义的常量
    d_FUNCTION, // 函数
    d_PROCEDURE,    // 过程
    // ...
};
class TypeNode
{
public:
    DataType m_Type;
    TypeNode* prev;
    TypeNode* next;
    // TypeNode* prev, next;
public:
    virtual bool isEqual(TypeNode* node) const {return false;}; // 检查类型是否一致
    virtual std::string toString(int& hPos) const = 0; // 输出类型信息
    // hPos当前光标水平位置
};
class enumNode : public TypeNode
{
public:
    std::vector<std::string>* m_List;
    unsigned int m_ID;
    static unsigned int Counter;
public:
    enumNode(std::vector<std::string>* List)
        : m_ID(Counter++)
    {
        m_Type = DataType::d_ENUM;
        m_List = List;
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
    virtual bool isEqual(TypeNode* node) const override
    {
        if (node->m_Type == DataType::d_ENUM)
        {
            if (m_ID == dynamic_cast<enumNode*>(node)->m_ID)
            {
                return true;
            }
        }
        return false;
    }
};


class sysNode : public TypeNode
{
public:
    std::string m_Keyword; // "integer", "real"等
public:
    virtual std::string toString(int& hPos) const override
    {
        std::stringstream ss;

        ss << std::setfill(' ') << std::setw(ALIGN_WIDTH) << "sys_type";
        ss << std::setfill(' ') << std::setw(ALIGN_WIDTH) << m_Keyword;
        return ss.str();
    }
    sysNode(std::string&& Keyword)
    {
        m_Type = DataType::d_SYS_TYPE;
        m_Keyword = Keyword;
    }
    virtual bool isEqual(TypeNode* node) const override
    {
        if (node->m_Type == m_Type)
        {
            if (m_Keyword == dynamic_cast<sysNode*>(node)->m_Keyword)
            {
                return true;
            }
        }
        return false;
    }
};

class recordNode : public TypeNode
{
public:
    std::unordered_map<std::string, TypeNode*>* m_Field; // 成员名字到类型的映射
public:
    TypeNode* getAttribute(std::string str) const
    {
        if (m_Field->find(str) != m_Field->end())
        {
            return (*m_Field)[str];
        }
        return nullptr;
    }
    recordNode(std::unordered_map<std::string, TypeNode*>* Field)
    {
        m_Field = Field;
    }
    virtual std::string toString(int& hPos) const override;
};


class constNode : public TypeNode
{
public:
    sysNode* m_sysNode;
    AST::ValConstant m_Constant;
    constNode(TypeNode* node, AST::ValConstant Constant)
    {
        if (node->m_Type != DataType::d_SYS_TYPE)
        { // 常数的类型只能是系统原始类型
            std::cout << "Invalid constant type!" << std::endl;
            exit(1);
        }
        m_Type = DataType::d_CONSTANT;
        m_sysNode = dynamic_cast<sysNode*>(node);
        m_Constant = Constant;
    }
    virtual std::string toString(int& hPos) const override;
};
class rangeNode : public TypeNode
{
public:
    int m_LowerBound; 
    int m_UpperBound;
    rangeNode(TypeNode* LowerBound, TypeNode* UpperBound)
    {
        if (LowerBound->m_Type != DataType::d_CONSTANT)
        {
            std::cout << "Invalid range!" << std::endl;
            exit(1);
        }
        m_Type = DataType::d_RANGE;
        AST::ValConstant temp_lower = dynamic_cast<constNode*>(LowerBound)->m_Constant;
        AST::ValConstant temp_upper = dynamic_cast<constNode*>(UpperBound)->m_Constant;
        
        if (temp_lower.Type != AST::ConstantType::Integer || temp_upper.Type != AST::ConstantType::Integer)
        {
            std::cout << "range只支持整型范围！" << std::endl;
        }
        m_LowerBound = temp_lower.iValue;
        m_UpperBound = temp_upper.iValue;
    }
    virtual std::string toString(int& hPos) const override;
};

class arrayNode : public TypeNode
{
public:
    TypeNode* m_EleType; // 元素类型
    TypeNode* m_IdxType; // 索引类型
    arrayNode(TypeNode* IdxType, TypeNode* EleType)
        : m_IdxType(IdxType), m_EleType(EleType)
    {
        m_Type = DataType::d_ARRAY;
    }
    virtual std::string toString(int& hPos) const override;
};



class ST; // 提前声明符号表类
class functNode : public TypeNode
{
public:
    TypeNode* m_resType; // 返回类型
    ST* m_val_table;    // 形参表
    ST* m_var_table;    // 引用参数表
    AST::Node* m_body; // 函数体的指针，指向<Routine-Body>
public:
    functNode(TypeNode* resType, AST::Node* body);
    virtual std::string toString(int& hPos) const override;
};

class procNode : public TypeNode 
{
public:
    ST* m_val_table;    // 形参表
    ST* m_var_table;    // 引用参数表
    AST::Node* m_body;  // 过程体的指针，指向<Routine-body>
public:
    procNode(AST::Node* body);
    virtual std::string toString(int& hPos) const override;
};