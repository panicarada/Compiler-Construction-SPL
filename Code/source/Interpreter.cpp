#include <stdio.h> 
#include "Interpreter.hpp"
#include <unordered_map>
#include "Plot_txt.hpp"
#include "Plot_py.hpp"
#include "yacc.tab.hpp"



int Interpreter::draw(AST::Node* p, std::ofstream& Out)
{
    int rte, rtm;
    Plot_txt::init();
    Plot_txt::drawNode(p, 0, 0, rte, rtm);
    Plot_txt::finish(Out);
    return 0;
}
int Interpreter::plot(AST::Node* p, std::ofstream& Out)
{
    int id = 0;
    Plot_py::plotNode(p, id, Out);
    return 0;
}

int Interpreter::execute(AST::Node* p, std::string& Filename, std::string& Program)
{
    if (p->m_Operation.NumOperands >= 2)
    {   // 如果存在主函数
        main_entry = p->m_Operation.List_Operands[1];
        std::cout << "main entry set!" << std::endl;
    }

    symbol_table->setup(p);
    symbol_table->show();
    std::ofstream ast_txt("./Output/AST_txt/" + Filename + ".txt.ast");
    ast_txt << "program:  " << Program << std::endl;
    draw(p, ast_txt);
    ast_txt.close();

    std::ofstream ast_raw("./Output/AST_raw/" + Filename + ".raw.ast");
    plot(p, ast_raw);
    ast_raw.close();
    return 0;
}
