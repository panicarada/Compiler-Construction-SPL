#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <set>
#include <unordered_map>


enum DataType
{
    d_SYS_TYPE, // integer, real等
    d_ENUM, // 枚举类型，如(red, green, blue)
    d_RECORD, // 结构体
    d_ARRAY, // 数组
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
        ss << std::setfill(' ') << std::setw(10) << "enum";
        ss << std::setfill(' ') << std::setw(10);
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

        ss << std::setfill(' ') << std::setw(10) << "sys_type";
        ss << std::setfill(' ') << std::setw(10) << m_Keyword;
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
        ss << std::setfill(' ') << std::setw(10) << "record";
        ss << std::setfill(' ') << std::setw(10);
        hPos += 20;
        for (auto& it : *m_Field)
        {
            ss << it.first << ": ";
            hPos += 2;
            ss << it.second->toString(hPos) << std::endl;
            hPos -= 2;
            ss << std::setfill(' ') << std::setw(hPos);
        }
        // 恢复到原来位置
        hPos -= 20;

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
        ss << std::setfill(' ') << std::setw(10) << "array";
        hPos += 10;
        ss << m_IdxType->toString(hPos) << std::endl;
        ss << std::setfill(' ') << std::setw(hPos) << " ";
        ss << m_EleType->toString(hPos) << std::endl;
        return ss.str();
    }
};