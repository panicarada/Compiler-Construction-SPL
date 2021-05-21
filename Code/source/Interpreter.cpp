#include "Interpreter.hpp"
#include <unordered_map>
#include "Plot_txt.hpp"
#include "Plot_py.hpp"
#include "yacc.tab.hpp"



int Interpreter::plot_txt(AST::Node* p, std::ofstream& Out)
{
    int rte, rtm;
    Plot_txt::init();
    Plot_txt::plotNode(p, 0, 0, rte, rtm);
    Plot_txt::finish(Out);
    return 0;
}
int Interpreter::plot_py(AST::Node* p, std::ofstream& Out)
{
    int id = 0;
    Plot_py::plotNode(p, id, Out);
    return 0;
}

int Interpreter::execute(AST::Node* p, std::string& Filename, std::string& Program) const
{
    /* 把刚std::cout重定向，写入到文件 */
    std::ofstream st_out("./Output/Logs/" + Filename + ".st");
    std::streambuf* cout_buffer = std::cout.rdbuf();
    std::streambuf* st_out_buffer = st_out.rdbuf();
    // 替换cout缓存区指针
    std::cout.rdbuf(st_out_buffer);

    std::cout << "Symbol Table: *****************" << std::endl;
    symbol_table->setup(p);
    symbol_table->show();
    std::cout << "Type of AST Node: *****************" << std::endl;

    // 两个绘制顺序不能换，在plot_py过程获得节点id
    std::ofstream ast_raw("./Output/AST_raw/" + Filename + ".raw.ast");
    plot_py(p, ast_raw);
    ast_raw.close();

    std::ofstream ast_txt("./Output/AST_txt/" + Filename + ".txt.ast");
    plot_txt(p, ast_txt);
    ast_txt.close();


    st_out.flush();
    st_out.close();
    // 恢复std::cout为原来的流缓冲区指针
    std::cout.rdbuf(cout_buffer);


    return 0;
}
