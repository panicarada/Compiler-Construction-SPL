#include <iostream>
#include <unordered_map>

#include "Typing.hpp"


class ST
{
    std::unordered_map<std::string, TypeNode*> Table;
    std::unordered_map<std::string, unsigned int> LineTable;
private:
    enum Scope
    {
        s_GLOBAL,
        s_CONST_PART,
        s_VAR_PART,
        s_RANGE,
    };
    TypeNode* getType(AST::Node* p, Scope scope = Scope::s_GLOBAL);
public:
    inline bool isEmpty() const
    {
        return Table.empty();
    }
    ST(bool addSys = true)
    { // 初始化Table，塞入系统类型
        if (addSys)
        {   // 是否要默认添加系统类型
            insert("integer", new sysNode("integer"), 0);
            insert("real", new sysNode("real"), 0);
            insert("boolean", new sysNode("boolean"), 0);
            insert("char", new sysNode("char"), 0);
            insert("string", new sysNode("string"), 0);
        }
    }
    // 给定语法树的根节点，构造符号表
    void setup(AST::Node* p);

    // 输出符号表
    void show(); 

    // 向符号表中加入符号以及对应的属性
    // 返回是否为首次插入
    bool insert(std::string str, TypeNode* node, unsigned int Line);

    // 根据符号名获取对应类型
    // 如果不存在，则返回nullptr
    TypeNode* get(std::string str, unsigned int line);

    // 按照当前符号表检查节点
    TypeNode* check(AST::Node* p);

    // 弹出该名字对应的最近一次加入到符号表的符号
    // 返回弹出的类型节点
    TypeNode* pop(std::string str);
};