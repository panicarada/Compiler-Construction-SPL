#pragma once
#include <fstream>
#include <functional>
#include <set>
#include <sstream>
#include <unordered_map>
 
#include "AST.hpp"
#include "Typing.hpp"
#include "SymbolTable.hpp"



class Interpreter
{
public:
    ST* symbol_table;
    AST::Node* main_entry;  // 主函数的入口，指向跟节点下面的routine-body
public:
    Interpreter()
    {
        symbol_table = new ST();
        main_entry = nullptr;
    }
    int draw(AST::Node* p, std::ofstream& Out);
    int plot(AST::Node* p, std::ofstream& Out);
    int execute(AST::Node* p, std::string& Filename, std::string& Program);
};