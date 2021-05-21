#pragma once
#include <fstream>
#include <functional>
#include <set>
#include <sstream>
#include <map>
 
#include "AST.hpp"
#include "Typing.hpp"
#include "SymbolTable.hpp"



class Interpreter
{
public:
    ST* symbol_table = nullptr;
    AST::Node* main_entry = nullptr;  // 主函数的入口，指向跟节点下面的routine-body
public:
    Interpreter()
    {
        symbol_table = new ST();
    }
    static int plot_txt(AST::Node* p, std::ofstream& Out);
    static int plot_py(AST::Node* p, std::ofstream& Out);
    int execute(AST::Node* p, std::string& Filename, std::string& Program) const;
};