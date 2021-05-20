#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "AST.hpp"
#include "yacc.tab.hpp"


namespace Plot_txt
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
    void plotNode(AST::Node* p, int Col_Start, int Line_Start, 
                int& Col_End, int& Col_Mid);


    const int maxCol = 500;
    const int maxLine = 500;
}