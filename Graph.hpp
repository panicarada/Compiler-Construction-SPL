#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "Utils.hpp"
#include "yacc.tab.h"


namespace Graph
{
    const int ColGap = 1; // distance of graph columns
    const int LineGap = 3; // distance of graph lines

    void init(void);
    void finish(std::ofstream& Out);
    void calBox(std::string& str, int& Width, int& Height);
    void drawBox(std::string& str, int Col, int Line);
    void drawArrow(int Col_Start, int Line_Start,
                        int Col_End, int Line_End);

    /* recursive drawing of the syntax tree */
    void drawNode(Node* p, int Col_Start, int Line_Start, 
                int& Col_End, int& Col_Mid);


    const int maxCol = 500;
    const int maxLine = 500;
}