#include <iostream>
#include <unordered_map>

#include "Typing.hpp"


class ST
    {
        std::unordered_map<std::string, TypeNode*> Table;
        std::unordered_map<std::string, unsigned int> LineTable;
    public:
        ST()
        { // 初始化Table，塞入系统类型
            insert("integer", new sysNode("integer", DataType::d_SYS_TYPE), 0);
            insert("real", new sysNode("real", DataType::d_SYS_TYPE), 0);
            insert("boolean", new sysNode("boolean", DataType::d_SYS_TYPE), 0);
            insert("char", new sysNode("char", DataType::d_SYS_TYPE), 0);
            insert("string", new sysNode("string", DataType::d_SYS_TYPE), 0);
        }
        void show()
        {
            std::cout << std::setfill(' ') << std::setw(ALIGN_WIDTH) << "name"
                      << std::setfill(' ') << std::setw(ALIGN_WIDTH / 2) << "line"
                      << std::setfill(' ') << std::setw(ALIGN_WIDTH) << "type"
                      << std::setfill(' ') << std::setw(ALIGN_WIDTH) << "attribute" << std::endl;
                    


            for (auto& it : Table)
            {
                int hPos = ALIGN_WIDTH + ALIGN_WIDTH/2;
                std::cout << std::setfill(' ') << std::setw(ALIGN_WIDTH) << it.first
                          << std::setfill(' ') << std::setw(ALIGN_WIDTH / 2) << LineTable[it.first]
                          << it.second->toString(hPos) << std::endl;
            }

        }
        bool insert(std::string str, TypeNode* node, unsigned int Line)
        {
            if (Table.find(str) == Table.end())
            {
                node->prev = node->next = nullptr;
                Table[str] = node;
                LineTable[str] = Line;
                return true;
            }
            else
            { // 原本就存在str这一个key
                // 用指针连接
                Table[str]->next = node;
                node->prev = Table[str];
                Table[str] = node;
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
        TypeNode* pop(std::string str)
        {
            if (Table.find(str) == Table.end())
            { // 如果不存在，没办法删除
                std::cout << "当前符号表中不存在名称: \"" << str << "\"" << std::endl;
                exit(1);
            }
            else 
            {   // 取出链表尾部
                TypeNode* res = Table[str];
                Table[str] = Table[str]->prev;
                Table[str]->next = nullptr;
                res->prev = nullptr;

                return res;
            }
        }
    };