#pragma once
#include "Utils.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <set>
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
    // ...
};
class TypeNode
{
public:
    DataType m_Type;
public:
    virtual bool isEqual(TypeNode* node) const {return false;}; // 检查类型是否一致
    virtual std::string toString(int& hPos) const = 0; // 输出类型信息
    // hPos当前光标水平位置
};
class enumNode : public TypeNode
{
public:
    std::set<std::string>* m_Set;
    unsigned int m_ID;
    static unsigned int Counter;
public:
    enumNode(std::set<std::string>* Set)
        : m_ID(Counter++)
    {
        m_Type = DataType::d_ENUM;
        m_Set = Set;
    }
    virtual std::string toString(int& hPos) const override
    {
        std::stringstream ss;
        ss << std::setfill(' ') << std::setw(ALIGN_WIDTH) << "enum";
        ss << std::setfill(' ') << std::setw(ALIGN_WIDTH);
        for (auto & it : *m_Set)
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
private:
    std::string m_Keyword; // "integer", "real"等
public:
    virtual std::string toString(int& hPos) const override
    {
        std::stringstream ss;

        ss << std::setfill(' ') << std::setw(ALIGN_WIDTH) << "sys_type";
        ss << std::setfill(' ') << std::setw(ALIGN_WIDTH) << m_Keyword;
        return ss.str();
    }
    sysNode(std::string&& Keyword, DataType Type)
    {
        if (Type != DataType::d_SYS_TYPE)
        {
            std::cout << "Invalid Constructor!!" << std::endl;
            exit(1);
        }
        else
        {
            m_Type = Type;
            m_Keyword = Keyword;
            std::cout << "Keyword: " << m_Keyword << std::endl;
        }
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
    virtual std::string toString(int& hPos) const override
    { // hPos: 当前水平位置
        std::stringstream ss;
        ss << std::setfill(' ') << std::setw(ALIGN_WIDTH) << "record";
        ss << std::setfill(' ') << std::setw(ALIGN_WIDTH);
        hPos += 2 * ALIGN_WIDTH;

        for (auto it = m_Field->begin(); it != m_Field->end(); )
        {
            ss << it->first << ": ";
            hPos += 2;
            ss << it->second->toString(hPos);
            hPos -= 2;
            if ((++it) != m_Field->end())
                ss << std::endl << std::setfill(' ') << std::setw(hPos);
        }
        // 恢复到原来位置
        hPos -= 2 * ALIGN_WIDTH;

        return ss.str();
    }
};


class constNode : public TypeNode
{
public:
    TypeNode* m_Const;
    constNode(TypeNode* Const)
    {
        std::cout << Const->m_Type << std::endl;
        if (Const->m_Type != DataType::d_SYS_TYPE)
        { // 常数的类型只能是系统原始类型
            std::cout << "Invalid constant type!" << std::endl;
            exit(1);
        }
        m_Type = DataType::d_CONSTANT;
        m_Const = Const;
    }
    virtual std::string toString(int& hPos) const override
    {
        std::stringstream ss;
        ss << std::setfill(' ') << std::setw(ALIGN_WIDTH) << "const";
        hPos += ALIGN_WIDTH;
        ss << m_Const->toString(hPos);
        hPos -= ALIGN_WIDTH;
        return ss.str();
    }
};
class rangeNode : public TypeNode
{
public:
    TypeNode* m_LowerBound; 
    TypeNode* m_UpperBound;
    rangeNode(TypeNode* LowerBound, TypeNode* UpperBound)
    {
        if (LowerBound->m_Type != DataType::d_CONSTANT)
        {
            std::cout << "Invalid range!" << std::endl;
            exit(1);
        }
        m_Type = DataType::d_RANGE;
        m_LowerBound = LowerBound;
        m_UpperBound = UpperBound;
    }

    virtual std::string toString(int& hPos) const override
    {
        std::stringstream ss;
        ss << std::setfill(' ') << std::setw(ALIGN_WIDTH) << "range";
        return ss.str();
    }
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
    virtual std::string toString(int& hPos) const override
    {
        std::stringstream ss;
        ss << std::setfill(' ') << std::setw(ALIGN_WIDTH) << "array";
        hPos += ALIGN_WIDTH;
        ss << m_IdxType->toString(hPos) << std::endl;
        ss << std::setfill(' ') << std::setw(hPos) << " ";
        ss << m_EleType->toString(hPos);
        hPos -= ALIGN_WIDTH;
        return ss.str();
    }
};