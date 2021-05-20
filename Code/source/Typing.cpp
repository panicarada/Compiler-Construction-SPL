#include "Typing.hpp"
#include "SymbolTable.hpp"


namespace Typing
{
    bool Node::isEqual(Node* node1, Node* node2)
    {
        if (!node1 || !node2)
            raiseError("比较指针有一个为空");
        if (node1->m_Type != node2->m_Type)
        {
            return false;
        }
        switch (node1->m_Type)
        {
            case NodeType::t_SYS_TYPE:
            {
                sysNode* sys1 = dynamic_cast<sysNode*>(node1);
                sysNode* sys2 = dynamic_cast<sysNode*>(node2);
                return (sys1->m_DataType == sys2->m_DataType);
            }
            case NodeType::t_ENUM:
            {
                enumNode* enum1 = dynamic_cast<enumNode*>(node1);
                enumNode* enum2 = dynamic_cast<enumNode*>(node2);
                // 只需比较他们的列表是否相等（在初始化时按照统一规则排序了）
                if (enum1->m_List->size() != enum2->m_List->size()) 
                    return false;
                for (int i = 0;i < enum1->m_List->size(); ++i)
                {
                    if (std::strcmp((*(enum1->m_List))[i].c_str(), 
                                    (*(enum1->m_List))[i].c_str()) != 0)
                    {
                        return false;
                    }
                }
                return true;
            }
            case NodeType::t_RANGE:
            {
                rangeNode* range1 = dynamic_cast<rangeNode*>(node1);
                rangeNode* range2 = dynamic_cast<rangeNode*>(node2);
                return (range1->m_LowerBound == range2->m_LowerBound
                     && range1->m_UpperBound == range2->m_UpperBound);
            }
            case NodeType::t_RECORD:
            {   // 注意，使用的结构是map，本身就已经按照key来排序了
                recordNode* record1 = dynamic_cast<recordNode*>(node1);
                recordNode* record2 = dynamic_cast<recordNode*>(node2);
                if (record1->m_Field->size() != record2->m_Field->size())
                    return false;
                auto it1 = record1->m_Field->begin();
                auto it2 = record1->m_Field->begin();
                for (int i = 0;i < record1->m_Field->size(); ++i)
                {
                    if ((it1->first != it2->first) || !isEqual(it1->second, it2->second))
                    {   // 成员名称和属性都要一致
                        return false;
                    }
                }
                return true;
            }
            case NodeType::t_ARRAY:
            {
                arrayNode* array1 = dynamic_cast<arrayNode*>(node1);
                arrayNode* array2 = dynamic_cast<arrayNode*>(node2);
                return (isEqual(array1->m_IdxType, array2->m_IdxType) 
                        && isEqual(array1->m_EleType, array2->m_EleType));
            }
            default:
            {
                int hPos = 0;
                std::cout << node1->toString(hPos) << std::endl;
                std::cout << node2->toString(hPos) << std::endl;
                raiseError("未知的数据类型");
            }
        }
    }
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
        ss << std::setfill(' ') << std::setw(ALIGN_WIDTH) << m_Sys->m_Keyword;
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

    functNode::functNode(std::string name, Node* resType, AST::Node* body)
        : m_name(name), m_resType(resType), m_body(body)
    {
        m_Type = NodeType::t_FUNCTION;
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
        m_Type = NodeType::t_PROCEDURE;
        m_var_table = new ST(false);
        m_val_table = new ST(false);
    }

    std::string procNode::toString(int& hPos) const 
    { // 只是输出过程名字，后续再完整地显示输入参数，这在Symbol Table::show()中实现
        std::stringstream ss;
        ss << std::setfill(' ') << std::setw(ALIGN_WIDTH) << "procedure";
        return ss.str();
    }
}