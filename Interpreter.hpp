#pragma once
#include "Utils.hpp"
#include <fstream>
#include <functional>
 


namespace Interpreter
{
    int run(Node* p, std::ofstream& Out);
    int draw(Node* p, std::ofstream& Out);

    int execute(Node* p, std::ofstream& Out);
} // namespace name