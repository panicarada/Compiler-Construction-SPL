#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "AST.hpp"
#include "yacc.tab.hpp"
 
namespace Plot_py
{
    void plotNode(AST::Node* p, int& id ,std::ofstream& Out);
}