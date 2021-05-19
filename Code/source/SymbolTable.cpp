#include "SymbolTable.hpp"
#include "AST.hpp"
#include "yacc.tab.hpp"


TypeNode* ST::getType(AST::Node* p, Scope scope)
{ 
    switch (p->m_Type)
    {
        case AST::NodeType::Constant:
            switch (p->m_Constant.Type)
            {
                case AST::ConstantType::Integer:
                    return new constNode(get("integer", p->m_Line), p->m_Constant);
                case AST::ConstantType::Real:
                    return new constNode(get("real", p->m_Line), p->m_Constant);
                case AST::ConstantType::Boolean:
                    return new constNode(get("boolean", p->m_Line), p->m_Constant);
                case AST::ConstantType::Char:
                    return new constNode(get("char", p->m_Line), p->m_Constant);
                case AST::ConstantType::String:
                    return new constNode(get("string", p->m_Line), p->m_Constant);
                default:
                    raiseError("Unknown constant Type!");
            }
            break;
        case AST::NodeType::Typename:
            {
                return get(p->m_Typename.Name, p->m_Line);
            }
        case AST::NodeType::Identifier:
            if (scope == Scope::s_RANGE)
            {
                return get(p->m_Identifier.Name, p->m_Line);
            }
        case AST::NodeType::Operation:
            switch (p->m_Operation.Operator)
            {
                case PROCEDURE:
                {
                    procNode* procedure = dynamic_cast<procNode*>(getType(p->m_Operation.List_Operands[0]));
                    if (p->m_Operation.NumOperands == 2)
                    { // 具有subroutine 
                        AST::Node* subroutine = p->m_Operation.List_Operands[1];
                        procedure->m_body = subroutine->m_Operation.List_Operands[0];
                    }
                    return procedure;
                }
                case PROCEDURE_HEAD:
                {
                    std::string name = p->m_Operation.List_Operands[p->m_Operation.NumOperands]->m_Identifier.Name;
                    procNode* procedure = new procNode(nullptr);
                    this->insert(name, procedure, // 过程的行数取过程名的函数
                                 p->m_Operation.List_Operands[p->m_Operation.NumOperands]->m_Line); 
                    if (p->m_Operation.NumOperands > 0)
                    { // 具有参数
                        AST::Node* paraList = p->m_Operation.List_Operands[0];
                        for (int i = 0;i < paraList->m_Operation.NumOperands; ++i)
                        {
                            AST::Node* para_group = paraList->m_Operation.List_Operands[i];
                            TypeNode* type = getType(para_group->m_Operation.List_Operands[0]);
                            for (int j = 1;j < para_group->m_Operation.NumOperands; ++j)
                            {
                                auto param = para_group->m_Operation.List_Operands[j];
                                if (para_group->m_Operation.Operator == VAL_PARAM)
                                { // 添加形参表
                                    procedure->m_val_table->insert(param->m_Identifier.Name, type, param->m_Line);
                                }
                                else if (para_group->m_Operation.Operator == VAR_PARAM)
                                { // 添加引用参数表
                                    procedure->m_var_table->insert(param->m_Identifier.Name, type, param->m_Line);
                                }
                                else 
                                {
                                    raiseError("Unknown param type!");
                                }
                            }
                        }
                    }
                    return procedure;
                }
                case FUNCTION:
                {
                    functNode* function = dynamic_cast<functNode*>(getType(p->m_Operation.List_Operands[0]));
                    if (p->m_Operation.NumOperands == 2)
                    { // 具有subroutine 
                        AST::Node* subroutine = p->m_Operation.List_Operands[1];
                        function->m_body = subroutine->m_Operation.List_Operands[0];
                    }
                    return function;
                }
                case FUNCTION_HEAD:
                {
                    std::string name = p->m_Operation.List_Operands[p->m_Operation.NumOperands]->m_Identifier.Name;
                    functNode* function = new functNode(getType(p->m_Operation.List_Operands[p->m_Operation.NumOperands-1]), nullptr);
                    this->insert(name, function, // 函数的行数取函数名的函数
                                 p->m_Operation.List_Operands[p->m_Operation.NumOperands]->m_Line); 
                    if (p->m_Operation.NumOperands > 1)
                    { // 具有参数
                        AST::Node* paraList = p->m_Operation.List_Operands[0];
                        for (int i = 0;i < paraList->m_Operation.NumOperands; ++i)
                        {
                            AST::Node* para_group = paraList->m_Operation.List_Operands[i];
                            TypeNode* type = getType(para_group->m_Operation.List_Operands[0]);
                            for (int j = 1;j < para_group->m_Operation.NumOperands; ++j)
                            {
                                auto param = para_group->m_Operation.List_Operands[j];
                                if (para_group->m_Operation.Operator == VAL_PARAM)
                                { // 添加形参表
                                    function->m_val_table->insert(param->m_Identifier.Name, type, param->m_Line);
                                }
                                else if (para_group->m_Operation.Operator == VAR_PARAM)
                                { // 添加引用参数表
                                    function->m_var_table->insert(param->m_Identifier.Name, type, param->m_Line);
                                }
                                else 
                                {
                                    raiseError("Unknown param type!");
                                }
                            }
                        }
                    }
                    return function;
                }
                case CONST_PART:
                    for (int i = 0;i < p->m_Operation.NumOperands; ++i)
                    {
                        getType(p->m_Operation.List_Operands[i], Scope::s_CONST_PART);
                    }
                    break;
                case EQUAL:
                    if (scope == Scope::s_CONST_PART)
                    { // const part的常数定义
                        insert(p->m_Operation.List_Operands[0]->m_Identifier.Name,
                                    getType(p->m_Operation.List_Operands[1]), p->m_Operation.List_Operands[0]->m_Line);
                    }
                    break;
                case MINUS:
                    if (scope == Scope::s_RANGE)
                    { // 在range中，一定是负数
                        auto TypeNode = dynamic_cast<constNode*>(getType(p->m_Operation.List_Operands[0]));
                        if (TypeNode->m_Constant.Type == AST::ConstantType::Integer)
                        {
                            TypeNode->m_Constant.iValue = -TypeNode->m_Constant.iValue;
                        }
                        else if (TypeNode->m_Constant.Type == AST::ConstantType::Real)
                        {
                            TypeNode->m_Constant.dValue = -TypeNode->m_Constant.dValue;
                        }
                        else 
                        {
                            // 只有整数和实数可以去负号
                            std::stringstream msg;
                            msg << "你无法对常数类型类型\"" << TypeNode->m_Constant.Type << "\"" << "取负！";
                            raiseError(msg.str());
                        }
                        return TypeNode;
                    }
                    break;
                case ROUTINE:
                    for (int i = 0; i < p->m_Operation.NumOperands; ++i)
                    {
                        getType(p->m_Operation.List_Operands[i]);
                    }
                    break;
                case ROUTINE_HEAD:
                    for (int i = 0;i < p->m_Operation.NumOperands; ++i)
                    {
                        getType(p->m_Operation.List_Operands[i]);
                    }
                    break;
                // 加入新类型
                case TYPE_PART:
                    // 见test3.spl以及对应的AST
                    for (int i = 0;i < p->m_Operation.NumOperands; ++i)
                    {
                        getType(p->m_Operation.List_Operands[i]);
                    }
                    break;
                case TYPE: // 左边是类型名字，右边是这个名字对应的类型statement
                    // 见test3.spl以及对应的AST
                    // std::cout << p->m_Operation.List_Operands[1]->m_Type << std::endl;
                    insert(p->m_Operation.List_Operands[0]->m_Identifier.Name,
                                getType(p->m_Operation.List_Operands[1]), p->m_Operation.List_Operands[0]->m_Line);
                    
                    break;
            
                // 加入(变量名， 类型指针)
                case VAR_PART: 
                    for (int i = 0;i < p->m_Operation.NumOperands; ++i)
                    { // 见test3.spl以及对应的AST
                        getType(p->m_Operation.List_Operands[i], Scope::s_VAR_PART);
                    }
                    break;
                case VAR: 
                    if (scope == Scope::s_VAR_PART)
                    { // var part部分的var，声明全局变量的类型
                        for (int i = 1; i < p->m_Operation.NumOperands; ++i)
                        {  
                            insert(p->m_Operation.List_Operands[i]->m_Identifier.Name,
                                    getType(p->m_Operation.List_Operands[0]), p->m_Operation.List_Operands[i]->m_Line);
                    
                        }
                    }
                    else
                    { // 函数参数部分的var，声明参数的引用类型

                    }
                    break;
                case ENUM:
                    {
                        auto enunList = new std::vector<std::string>();
                        for (int i = 0;i < p->m_Operation.NumOperands; ++i)
                        {
                            enunList->push_back(p->m_Operation.List_Operands[i]->m_Identifier.Name);
                        }
                        auto node = new enumNode(enunList);
                        for (int i = 0;i < p->m_Operation.NumOperands; ++i)
                        {
                            insert(p->m_Operation.List_Operands[i]->m_Identifier.Name,
                                        node, p->m_Operation.List_Operands[i]->m_Line);
                        }
                        return node;
                    }
                    break;
                case RECORD:
                    {
                        auto Field = new std::unordered_map<std::string, TypeNode*>();
                        TypeNode* temp;
                        
                        for (int i = 0;i < p->m_Operation.NumOperands; ++i)
                        {  
                            auto Child = p->m_Operation.List_Operands[i];
                            temp = getType(Child->m_Operation.List_Operands[0]);
                            // 见test3.spl的AST
                            for (int j = 1; j < Child->m_Operation.NumOperands; ++j)
                            {
                                std::string Name = Child->m_Operation.List_Operands[j]->m_Identifier.Name;
                                (*Field)[Name] = temp;
                            }
                        }
                        return new recordNode(Field);
                    }
                case ARRAY:
                    {
                        // 见test4.spl的AST
                        auto IdxType = getType(p->m_Operation.List_Operands[1]);
                        auto EleType = getType(p->m_Operation.List_Operands[0]);
                        return new arrayNode(IdxType, EleType);
                    }
                case DOTDOT:
                    {
                        auto LowerBound = getType(p->m_Operation.List_Operands[0], Scope::s_RANGE);
                        auto UpperBound = getType(p->m_Operation.List_Operands[1], Scope::s_RANGE);
                        return new rangeNode(LowerBound, UpperBound);
                    }
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return nullptr;
}

void ST::setup(AST::Node* p)
{
    getType(p);
}

void ST::show()
{
    std::cout   << std::setfill(' ') << std::setw(ALIGN_WIDTH) << "name"
                << std::setfill(' ') << std::setw(ALIGN_WIDTH / 2) << "line"
                << std::setfill(' ') << std::setw(ALIGN_WIDTH) << "type"
                << std::setfill(' ') << std::setw(ALIGN_WIDTH) << "attribute" << std::endl;
        
    std::vector<std::pair<std::string, TypeNode*>> functions;
    std::vector<std::pair<std::string, TypeNode*>> procedures;
    for (auto& it : Table)
    {
        int hPos = ALIGN_WIDTH + ALIGN_WIDTH/2;
        std::cout   << std::setfill(' ') << std::setw(ALIGN_WIDTH) << it.first
                    << std::setfill(' ') << std::setw(ALIGN_WIDTH / 2) << LineTable[it.first]
                    << it.second->toString(hPos) << std::endl;
        if ((it.second)->m_Type == DataType::d_FUNCTION)
        {   // 函数储存起来，之后要输出函数的参数表
            functions.push_back(it);
        }
        if ((it.second)->m_Type == DataType::d_PROCEDURE)
        {   // 过程储存起来，之后要输出过程的参数表
            procedures.push_back(it);
        }
    }
    for (auto& it : functions)
    {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "function: \"" << it.first << "\"" << std::endl;
        functNode* function = dynamic_cast<functNode*>(it.second);
        if (!function->m_val_table->isEmpty())
        {
            std::cout << "value param:" << std::endl;
            function->m_val_table->show();
        }
        if (!function->m_var_table->isEmpty())
        {
            std::cout << "ref param:" << std::endl;
            function->m_var_table->show();
        }
    }
    for (auto& it : procedures)
    {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "procedure: \"" << it.first << "\"" << std::endl;
        procNode* procedure = dynamic_cast<procNode*>(it.second);
        if (!procedure->m_val_table->isEmpty())
        {
            std::cout << "value param:" << std::endl;
            procedure->m_val_table->show();
        }
        if (!procedure->m_var_table->isEmpty())
        {
            std::cout << "ref param:" << std::endl;
            procedure->m_var_table->show();
        }
    }
}

bool ST::insert(std::string str, TypeNode* node, unsigned int Line)
{
    if (Table.find(str) == Table.end())
    {
        node->prev = node->next = nullptr;
        Table[str] = node;
        LineTable[str] = Line;
        return true;
    }
    else
    { // 原本就存在str这一个key
        // 用指针连接
        Table[str]->next = node;
        node->prev = Table[str];
        Table[str] = node;
        return false;
    }
}

TypeNode* ST::get(std::string str, unsigned int line)
{
    if (Table.find(str) != Table.end())
    {
        return Table[str];
    }
    // 报错
    std::stringstream msg;
    msg << std::endl << "In line: " << line << ". The type \"" << str << "\" is not available in the symbol table!";
    raiseError(msg.str());
    return nullptr;
}

TypeNode* ST::pop(std::string str)
{
    if (Table.find(str) == Table.end())
    { // 如果不存在，没办法删除
        std::stringstream msg;
        msg << "当前符号表中不存在名称: \"" << str << "\"" << std::endl;
        raiseError(msg.str())
    }
    else 
    {   // 取出链表尾部
        TypeNode* res = Table[str];
        Table[str] = Table[str]->prev;
        Table[str]->next = nullptr;
        res->prev = nullptr;
        return res;
    }
}

TypeNode* ST::check(AST::Node* p)
{
    if (!p) return nullptr;
    switch (p->m_Type)
    {
        case AST::NodeType::Constant:
            switch (p->m_Constant.Type)
            {
                case AST::ConstantType::Integer: return new constNode(new sysNode("integer"), p->m_Constant);
                case AST::ConstantType::Real: return new constNode(new sysNode("real"), p->m_Constant);
                case AST::ConstantType::Char: return new constNode(new sysNode("char"), p->m_Constant);
                case AST::ConstantType::String: return new constNode(new sysNode("string"), p->m_Constant);
                case AST::ConstantType::Boolean: return new constNode(new sysNode("boolean"), p->m_Constant);
                default:
                {
                    std::stringstream msg;
                    msg << "Invalid Constant Type: " << p->m_Constant.Type << "!!";
                    raiseError(msg.str());
                }
            }
        case AST::NodeType::Identifier:
            return get(p->m_Identifier.Name, p->m_Line);
        case AST::NodeType::Typename:
            return get(p->m_Typename.Name, p->m_Line);
        case AST::NodeType::Operation:
            switch (p->m_Operation.Operator)
            {
                case GE: case GT: case LE: case LT: case EQUAL: case UNEQUAL:
                case ASSIGN: 
                {
                    TypeNode* left = check(p->m_Operation.List_Operands[0]);
                    TypeNode* right = check(p->m_Operation.List_Operands[1]);
                    if (!left->isEqual(left))
                    {
                        std::stringstream msg;
                        msg << std::endl << "In line " << p->m_Line << ". 该操作两边的类型不一致" << std::endl;
                        int hPos = 0;
                        msg << "LHS: " << left->toString(hPos) << std::endl;
                        msg << "RHS: " << right->toString(hPos) << std::endl;
                        raiseError(msg.str());
                    }
                    // 比较的结果是布尔值
                    return new sysNode("boolean");
                }
                case OR: case AND: case NOT:
                {   // 逻辑运算，两边都应该是布尔值
                    TypeNode* target = get("boolean", p->m_Line);
                    TypeNode* left = check(p->m_Operation.List_Operands[0]);
                    TypeNode* right = check(p->m_Operation.List_Operands[1]);
                    if (!target->isEqual(left) || !target->isEqual(right))
                    {
                        std::stringstream msg;
                        msg << std::endl << "In line " << p->m_Line << ". 逻辑运算中，两边的操作都应该是布尔值" << std::endl;
                        int hPos = 0;
                        msg << "LHS: " << left->toString(hPos) << std::endl;
                        msg << "RHS: " << right->toString(hPos) << std::endl;
                        raiseError(msg.str());
                    }
                }
                default:
                {
                    std::stringstream msg;
                    msg << "In line " << p->m_Line << ". 未知的操作符\"" << p->m_Operation.Operator << "\"";
                    raiseError(msg.str());
                }
            }
        
        default:
            break;
    }
}