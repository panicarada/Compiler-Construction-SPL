#pragma once
#include "Utils.hpp"
#include "Typing.hpp"
#include <fstream>
#include <functional>
#include <set>
#include <sstream>
#include <unordered_map>
 



namespace Interpreter
{
    class ST
    {
        std::unordered_map<std::string, TypeNode*> Table;
    public:
        ST()
        { // 初始化Table，塞入系统类型
            insert("integer", new sysNode("integer", DataType::d_SYS_TYPE));
            insert("real", new sysNode("real", DataType::d_SYS_TYPE));
            insert("boolean", new sysNode("boolean", DataType::d_SYS_TYPE));
            insert("char", new sysNode("char", DataType::d_SYS_TYPE));
            insert("string", new sysNode("string", DataType::d_SYS_TYPE));
        }
        void show()
        {
            for (auto& it : Table)
            {
                int hPos = 10;
                std::cout << std::setfill(' ') << std::setw(10) << it.first
                          << it.second->toString(hPos) << std::endl;
            }

        }
        bool insert(std::string str, TypeNode* node)
        {
            if (Table.find(str) == Table.end())
            {
                Table[str] = node;
                return true;
            }
            else
            { // 原本就存在str这一个key
                // ...
                return false;
            }
        }
        TypeNode* get(std::string str)
        {
            if (Table.find(str) != Table.end())
            {
                return Table[str];
            }
            return NULL;
        }
    };
    static ST st;
    TypeNode* getType(Node* p, bool isVarPart = false);
    int draw(Node* p, std::ofstream& Out);
    int execute(Node* p, std::ofstream& Out);
} // namespace name