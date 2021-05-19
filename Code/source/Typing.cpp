#include "Typing.hpp"
#include "SymbolTable.hpp"


unsigned int enumNode::Counter = 0;


std::string recordNode::toString(int& hPos) const
{ // hPos: 当前水平位置
    std::stringstream ss;
    ss << std::setfill(' ') << std::setw(ALIGN_WIDTH) << "record";
    ss << std::setfill(' ') << std::setw(ALIGN_WIDTH);
    hPos += 2 * ALIGN_WIDTH;

    for (auto it = m_Field->begin(); it != m_Field->end(); )
    {
        ss << it->first << ": ";
        hPos += 2;
        ss << it->second->toString(hPos);
        hPos -= 2;
        if ((++it) != m_Field->end())
            ss << std::endl << std::setfill(' ') << std::setw(hPos);
    }
    // 恢复到原来位置
    hPos -= 2 * ALIGN_WIDTH;

    return ss.str();
}

std::string constNode::toString(int& hPos) const
{
    std::stringstream ss;
    ss << std::setfill(' ') << std::setw(ALIGN_WIDTH) << "const";
    ss << std::setfill(' ') << std::setw(ALIGN_WIDTH) << m_sysNode->m_Keyword;
    ss << std::setfill(' ') << std::setw(ALIGN_WIDTH);
    switch (m_Constant.Type)
    {
        case AST::ConstantType::Integer:
            ss << m_Constant.iValue; break;
        case AST::ConstantType::Real:
            ss << m_Constant.dValue; break;
        case AST::ConstantType::Boolean:
            ss << m_Constant.bValue; break;
        case AST::ConstantType::Char:
            ss << m_Constant.cValue; break;
        case AST::ConstantType::String:
            {
                std::string output = std::string("\"") + m_Constant.sValue + std::string("\"");
                // 字符串长度可能要调整一下
                ss << std::setw(std::max<int>(ALIGN_WIDTH, output.length() + 3)) << output; 
                break;
            }
    }
    return ss.str();
}

std::string rangeNode::toString(int& hPos) const
{
    std::stringstream ss;
    ss << std::setfill(' ') << std::setw(ALIGN_WIDTH) << "range";
    std::string range = std::to_string(m_LowerBound);
    range += " .. ";
    range += std::to_string(m_UpperBound);
    ss << std::setfill(' ') << std::setw(ALIGN_WIDTH) << range;
    return ss.str();
}

std::string arrayNode::toString(int& hPos) const
{
    std::stringstream ss;
    ss << std::setfill(' ') << std::setw(ALIGN_WIDTH) << "array";
    hPos += ALIGN_WIDTH;
    ss << m_IdxType->toString(hPos) << std::endl;
    ss << std::setfill(' ') << std::setw(hPos) << " ";
    ss << m_EleType->toString(hPos);
    hPos -= ALIGN_WIDTH;
    return ss.str();
}

functNode::functNode(TypeNode* resType, AST::Node* body)
    : m_resType(resType), m_body(body)
{
    m_Type = DataType::d_FUNCTION;
    m_var_table = new ST(false);
    m_val_table = new ST(false);
}

std::string functNode::toString(int& hPos) const
{ // 只是输出函数名字和返回参数，后续再完整地显示输入参数，这在Symbol Table::show()中实现
    std::stringstream ss;
    ss << std::setfill(' ') << std::setw(ALIGN_WIDTH) << "function";
    hPos += ALIGN_WIDTH;
    ss << m_resType->toString(hPos);
    hPos -= ALIGN_WIDTH;
    return ss.str();
}

procNode::procNode(AST::Node* body)
    : m_body(body)
{
    m_Type = DataType::d_PROCEDURE;
    m_var_table = new ST(false);
    m_val_table = new ST(false);
}

std::string procNode::toString(int& hPos) const 
{ // 只是输出过程名字，后续再完整地显示输入参数，这在Symbol Table::show()中实现
    std::stringstream ss;
    ss << std::setfill(' ') << std::setw(ALIGN_WIDTH) << "procedure";
    return ss.str();
}