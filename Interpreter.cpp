#include <stdio.h> 
#include "Interpreter.hpp"
#include "Graph.hpp"
#include "yacc.tab.h"


namespace Interpreter
{
    int run(Node* p, std::ofstream& Out)
    { 
        return 0;
    }

    int draw(Node* p, std::ofstream& Out)
    {
        int rte, rtm;
        Graph::init();
        Graph::drawNode(p, 0, 0, rte, rtm);
        Graph::finish(Out);
        return 0;
    }

    int execute(Node* p, std::ofstream& Out)
    {
        return draw(p, Out);
    }
}
