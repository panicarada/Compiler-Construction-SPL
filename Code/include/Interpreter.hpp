#pragma once
#include <fstream>
#include <functional>
#include <set>
#include <sstream>
#include <unordered_map>
 
#include "Utils.hpp"
#include "Typing.hpp"
#include "SymbolTable.hpp"



namespace Interpreter
{
    static ST st;
    enum Scope
    {
        s_GLOBAL,
        s_CONST_PART,
        s_VAR_PART,
        s_RANGE,
    };
    TypeNode* getType(Node* p, Scope scope = Scope::s_GLOBAL);
    int draw(Node* p, std::ofstream& Out);
    int execute(Node* p, std::ofstream& Out);
} // namespace name