#include "SymbolTable.hpp"
#include "AST.hpp"
#include "yacc.tab.hpp"


Typing::Node* ST::getType(AST::Node* p, Scope scope)
{ 
    switch (p->m_Attribute)
    {
        case AST::Attribute::Constant:
            switch (p->m_Constant.Type)
            {
                case AST::ConstantType::Integer:
                    return new Typing::constNode(get("integer", 0) , p->m_Constant);
                case AST::ConstantType::Real:
                    return new Typing::constNode(get("real", 0) , p->m_Constant);
                case AST::ConstantType::Boolean:
                    return new Typing::constNode(get("boolean", 0) , p->m_Constant);
                case AST::ConstantType::Char:
                    return new Typing::constNode(get("char", 0) , p->m_Constant);
                case AST::ConstantType::String:
                    return new Typing::constNode(get("string", 0) , p->m_Constant);
                default:
                    raiseError("Unknown constant Type!");
            }
            break;
        case AST::Attribute::Typename:
            {
                return get(p->m_Typename.Name, p->m_Line);
            }
        case AST::Attribute::Identifier:
            if (scope == Scope::s_RANGE)
            {
                return get(p->m_Identifier.Name, p->m_Line);
            }
        case AST::Attribute::Operation:
            switch (p->m_Operation.Operator)
            {
                case PROCEDURE:
                {
                    Typing::procNode* procedure = dynamic_cast<Typing::procNode*>(getType(p->m_Operation.List_Operands[0]));
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
                    Typing::procNode* procedure = new Typing::procNode(nullptr);
                    this->insert(name, procedure, // 过程的行数取过程名的函数
                                 p->m_Operation.List_Operands[p->m_Operation.NumOperands]->m_Line); 
                    if (p->m_Operation.NumOperands > 0)
                    { // 具有参数
                        AST::Node* paraList = p->m_Operation.List_Operands[0];
                        for (int i = 0;i < paraList->m_Operation.NumOperands; ++i)
                        {
                            AST::Node* para_group = paraList->m_Operation.List_Operands[i];
                            Typing::Node* type = getType(para_group->m_Operation.List_Operands[0]);
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
                    Typing::functNode* function = dynamic_cast<Typing::functNode*>(getType(p->m_Operation.List_Operands[0]));
                    if (p->m_Operation.NumOperands == 2)
                    {   // 具有subroutine 
                        AST::Node* subroutine = p->m_Operation.List_Operands[1];
                        function->m_body = subroutine->m_Operation.List_Operands[0];

                        // 检查函数体的类型
                        for (auto& it : function->m_val_table->Table)
                        {   // 先把函数的参数表暂时加入符号表中
                            insert(it.first, it.second, function->m_val_table->LineTable[it.first]);
                        }   
                        for (auto& it : function->m_var_table->Table)
                        {   // 类型检查时不区分引用类型
                            insert(it.first, it.second, function->m_val_table->LineTable[it.first]);
                        }

                        // 检查函数体
                        check(function->m_body);

                        // 把刚才加入的符号弹出
                        for (auto& it : function->m_val_table->Table)
                        {
                            pop(it.first);
                        }
                        for (auto& it : function->m_var_table->Table)
                        {
                            pop(it.first);
                        }
                    }
                    
                    return function;
                }
                case FUNCTION_HEAD:
                {
                    std::string name = p->m_Operation.List_Operands[p->m_Operation.NumOperands]->m_Identifier.Name;
                    Typing::functNode* function = new Typing::functNode(name, getType(p->m_Operation.List_Operands[p->m_Operation.NumOperands-1]), nullptr);
                    this->insert(name, function, // 函数的行数取函数名的函数
                                 p->m_Operation.List_Operands[p->m_Operation.NumOperands]->m_Line); 
                    if (p->m_Operation.NumOperands > 1)
                    { // 具有参数
                        AST::Node* paraList = p->m_Operation.List_Operands[0];
                        for (int i = 0;i < paraList->m_Operation.NumOperands; ++i)
                        {
                            AST::Node* para_group = paraList->m_Operation.List_Operands[i];
                            Typing::Node* type = getType(para_group->m_Operation.List_Operands[0]);
                            for (int j = 1;j < para_group->m_Operation.NumOperands; ++j)
                            {
                                auto param = para_group->m_Operation.List_Operands[j];
                                
                                if (para_group->m_Operation.Operator == VAL_PARAM)
                                { // 添加形参表
                                    function->addParam(true, param->m_Identifier.Name, type, param->m_Line);
                                }
                                else if (para_group->m_Operation.Operator == VAR_PARAM)
                                { // 添加引用参数表
                                    function->addParam(false, param->m_Identifier.Name, type, param->m_Line);
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
                        auto TypeNode = dynamic_cast<Typing::constNode*>(getType(p->m_Operation.List_Operands[0]));
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
                    getType(p->m_Operation.List_Operands[0]);
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
                        auto node = new Typing::enumNode(enunList);
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
                        auto Field = new std::map<std::string, Typing::Node*>();
                        Typing::Node* temp;
                        
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
                        return new Typing::recordNode(Field);
                    }
                case ARRAY:
                    {
                        // 见test4.spl的AST
                        auto IdxType = getType(p->m_Operation.List_Operands[1]);
                        auto EleType = getType(p->m_Operation.List_Operands[0]);
                        return new Typing::arrayNode(IdxType, EleType);
                    }
                case DOTDOT:
                    {
                        auto LowerBound = getType(p->m_Operation.List_Operands[0], Scope::s_RANGE);
                        auto UpperBound = getType(p->m_Operation.List_Operands[1], Scope::s_RANGE);
                        return new Typing::rangeNode(LowerBound, UpperBound);
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
        
    std::vector<std::pair<std::string, Typing::Node*>> functions;
    std::vector<std::pair<std::string, Typing::Node*>> procedures;
    for (auto& it : Table)
    {
        int hPos = ALIGN_WIDTH + ALIGN_WIDTH/2;
        std::cout   << std::setfill(' ') << std::setw(ALIGN_WIDTH) << it.first
                    << std::setfill(' ') << std::setw(ALIGN_WIDTH / 2) << LineTable[it.first]
                    << it.second->toString(hPos) << std::endl;
        if ((it.second)->m_Type == Typing::NodeType::t_FUNCTION)
        {   // 函数储存起来，之后要输出函数的参数表
            functions.push_back(it);
        }
        if ((it.second)->m_Type == Typing::NodeType::t_PROCEDURE)
        {   // 过程储存起来，之后要输出过程的参数表
            procedures.push_back(it);
        }
    }
    for (auto& it : functions)
    {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "function: \"" << it.first << "\"" << std::endl;
        Typing::functNode* function = dynamic_cast<Typing::functNode*>(it.second);
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
        std::cout << "----------------------------------------" << std::endl;

    }
    for (auto& it : procedures)
    {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "procedure: \"" << it.first << "\"" << std::endl;
        Typing::procNode* procedure = dynamic_cast<Typing::procNode*>(it.second);
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
        std::cout << "----------------------------------------" << std::endl;
    }
}

bool ST::insert(std::string str, Typing::Node* node, unsigned int Line)
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

Typing::Node* ST::get(std::string str, unsigned int line)
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

Typing::Node* ST::pop(std::string str)
{
    if (Table.find(str) == Table.end())
    { // 如果不存在，没办法删除
        std::stringstream msg;
        msg << "当前符号表中不存在名称: \"" << str << "\"" << std::endl;
        raiseError(msg.str())
    }
    else 
    {   // 取出链表尾部
        Typing::Node* res = Table[str];
        Typing::Node* prev = Table[str]->prev;  // 上一个在这一位置的符号
        if (prev)
        {
            Table[str] = prev;
            Table[str]->next = nullptr;
        }
        else 
        {
            Table.erase(str);
        }
        res->prev = nullptr;
        return res;
    }
}

Typing::Node* ST::check(AST::Node* p)
{
    if (!p) return nullptr;
    switch (p->m_Attribute)
    {
        case AST::Attribute::Constant:
            // 具体类型是所对应的sys类型
            switch (p->m_Constant.Type)
            {
                case AST::ConstantType::Integer: 
                    p->m_Type = get("integer", 0);
                    return p->m_Type;
                case AST::ConstantType::Real: 
                    p->m_Type = get("real", 0);
                    return p->m_Type;
                case AST::ConstantType::Char:
                    p->m_Type = get("char", 0);
                    return p->m_Type;
                case AST::ConstantType::String:
                    p->m_Type = get("string", 0);
                    return p->m_Type;
                case AST::ConstantType::Boolean:
                    p->m_Type = get("boolean", 0);
                    return p->m_Type;
                default:
                {
                    std::stringstream msg;
                    msg << "Invalid Constant Type: " << p->m_Constant.Type << "!!";
                    raiseError(msg.str());
                }
            }

        case AST::Attribute::Identifier:
            {
                auto type = get(p->m_Identifier.Name, p->m_Line);
                // 函数体中，函数名就是返回参数
                if (type->m_Type == Typing::NodeType::t_FUNCTION)
                {   // 这时候对应的类型是函数返回类型
                    type = dynamic_cast<Typing::functNode*>(type)->m_resType;
                }
                p->m_Type = type;
                return p->m_Type;
            }
        case AST::Attribute::Typename:
            p->m_Type = get(p->m_Typename.Name, p->m_Line);
            return p->m_Type;
        case AST::Attribute::Operation:
            switch (p->m_Operation.Operator)
            {
                /* 数组访问 */
                case BRACKET:
                { // 关于数组的例子请见swap.spl
                    auto node = check(p->m_Operation.List_Operands[0]);
                    if (node->m_Type != Typing::NodeType::t_ARRAY)
                    {
                        std::stringstream msg;
                        msg << std::endl << "In line " << p->m_Line << ". 无法对下面的类型进行数组访问" << std::endl;
                        int hPos = 0;
                        msg << "given: " << node->toString(hPos) << std::endl;
                        raiseError(msg.str());
                    }
                    auto array = dynamic_cast<Typing::arrayNode*>(node);
                    auto idxType = check(p->m_Operation.List_Operands[1]);

                    // 检查数组访问下标类型是否一致
                    // 不检查越界！
                    auto target = array->m_IdxType;
                    if (target->m_Type == Typing::NodeType::t_RANGE)
                    {   // range本质上的类型就是integer
                        target = get("integer", 0);
                    }
                    if (Typing::Node::isEqual(target, idxType))
                    {
                        // 返回数组元素类型
                        p->m_Type = array->m_EleType;
                        return p->m_Type;
                    }
                    std::stringstream msg;
                    msg << std::endl << "In line " << p->m_Line << ". 数组访问下标不匹配" << std::endl;
                    int hPos = 0;
                    msg << "expected: " << target->toString(hPos) << std::endl;
                    hPos = 0;
                    msg << "given: " << idxType->toString(hPos) << std::endl;
                    raiseError(msg.str());
                }
                case CASE_STMT:
                {   // case部分详见is_even.spl生成的语法树
                    // 子节点格式为[表达式，case-list]
                    auto expression = check(p->m_Operation.List_Operands[0]);
                    auto case_list = p->m_Operation.List_Operands[1];
                    // case-list子节点的格式为[case, case, ..., ...]
                    for (int i = 0;i < case_list->m_Operation.NumOperands; ++i)
                    {   // 每个case的子节点格式为[表达式，语句]
                        auto case_unit = case_list->m_Operation.List_Operands[i];
                        auto case_exp = check(case_unit->m_Operation.List_Operands[0]);
                        // 检查是否和条件表达式的类型匹配
                        if (!Typing::Node::isEqual(expression, case_exp))
                        {   // 如果不相同，那么switch<real> case <integer>也是可以的
                            if (!Typing::Node::isEqual(expression, get("real", 0))
                                && Typing::Node::isEqual(case_exp, get("integer", 0)))
                            {
                                std::stringstream msg;
                                msg << std::endl << "In line " << p->m_Line << ". case条件类型不匹配" << std::endl;
                                int hPos = 0;
                                msg << "expected: " << expression->toString(hPos) << std::endl;
                                hPos = 0;
                                msg << "given: " << case_exp->toString(hPos) << std::endl;
                                raiseError(msg.str());
                            }
                        }
                        // 检查case内部语句
                        check(case_unit->m_Operation.List_Operands[1]);
                    }
                    // 本身没有类型
                    return nullptr;
                }
                /* 函数调用 */
                case CALL_FUNCT:
                {   // 注意，这里是调用函数，而非定义函数
                    auto function = dynamic_cast<Typing::functNode*>(get(p->m_Operation.List_Operands[0]->m_Identifier.Name, p->m_Line));

                    int size = function->m_Params.size();

                    if (size != p->m_Operation.NumOperands - 1)
                    {
                        std::stringstream msg;
                        msg << std::endl << "In line " << p->m_Line << ". 函数参数数目不匹配" << std::endl;
                        int hPos = 0;
                        msg << function->toString(hPos) << std::endl;
                        msg << "expected: " << size << std::endl;
                        msg << "given: " << p->m_Operation.NumOperands - 1 << std::endl;
                        raiseError(msg.str());
                    }
                    int i = 1;
                    for (auto it = function->m_Params.begin();it != function->m_Params.end(); ++it)
                    {
                        auto input = check(p->m_Operation.List_Operands[i++]); // 第i个输入的参数
                        Typing::Node* param;

                        if (it->second)
                        {   // is var = true
                            param = function->m_var_table->get(it->first, p->m_Line);
                        }
                        else 
                        {
                            param = function->m_val_table->get(it->first, p->m_Line);
                        }

                        if (!Typing::Node::isEqual(param, input))
                        {
                            std::stringstream msg;
                            msg << std::endl << "In line " << p->m_Line << ". 函数参数类型不匹配" << std::endl;
                            int hPos = 0;
                            msg << "expected: " << param->toString(hPos) << std::endl;
                            hPos = 0;
                            msg << "input: " << input->toString(hPos) << std::endl;
                            raiseError(msg.str());
                        }
                    }
                    // 函数返回类型
                    p->m_Type = function->m_resType;
                    return p->m_Type;
                }
                case SEMI:
                {   // 语句分隔符，子节点为[上一语句，下一语句]
                    // 检查所有子节点即可
                    for (int i = 0;i < p->m_Operation.NumOperands; ++i)
                    {
                        check(p->m_Operation.List_Operands[i]);
                    }
                    return nullptr; // 本身没类型
                }
                case IF:
                {
                    // 子节点为[条件, if-claus, <else-clause>]
                    Typing::Node* condition = check(p->m_Operation.List_Operands[0]);
                    if (Typing::Node::isEqual(condition, get("boolean", 0)))
                    {   // 条件一定要是布尔值
                        check(p->m_Operation.List_Operands[1]); // 检查if-clause
                        if (p->m_Operation.NumOperands == 3)
                        {   // 存在else-clause
                            check(p->m_Operation.List_Operands[2]);
                        }
                        return nullptr; // 本身无类型
                    }
                }
                /* 函数体 */
                case ROUTINE_BODY: 
                    return check(p->m_Operation.List_Operands[0]);
                case DOT:
                {   // 结构体成员访问
                    // 子节点为[record名，成员名]
                    auto node = get(p->m_Operation.List_Operands[0]->m_Identifier.Name, p->m_Line);
                    Typing::recordNode* record;
                    if (node->m_Type == Typing::NodeType::t_RECORD)
                    {
                        record = dynamic_cast<Typing::recordNode*>(node);
                    }
                    else if (node->m_Type == Typing::NodeType::t_FUNCTION)
                    {   // 在函数内部，函数名就是返回值
                        auto function = dynamic_cast<Typing::functNode*>(node);

                        if (function->m_resType->m_Type == Typing::NodeType::t_RECORD)
                        {
                            record = dynamic_cast<Typing::recordNode*>(function->m_resType);
                        }
                        else
                        {
                            std::stringstream msg;
                            msg << std::endl << "In line " << p->m_Line << ". 函数类型不是record！" << std::endl;
                            int hPos = 0;
                            msg << "函数: " << function->toString(hPos) << std::endl;
                            raiseError(msg.str());
                        }
                    }
                    else 
                    {
                        std::stringstream msg;
                        msg << std::endl << "In line " << p->m_Line << ". 不是结构类型，无法访问成员！" << std::endl;
                        int hPos = 0;
                        msg << "变量: " << node->toString(hPos) << std::endl;
                        raiseError(msg.str());
                    }
                    std::string member = p->m_Operation.List_Operands[1]->m_Identifier.Name;
                    record->m_Field->find(member);
                    if (record->m_Field->find(member) == record->m_Field->end())
                    {   
                            std::stringstream msg;
                            msg << std::endl << "In line " << p->m_Line << ". 结构体访问的成员不存在!" << std::endl;
                            int hPos = 0;
                            msg << "结构体: " << record->toString(hPos) << std::endl;
                            msg << "访问名: " << member << std::endl;
                            raiseError(msg.str());
                    }

                    // 返回成员的类型
                    p->m_Type = (*(record->m_Field))[member];
                    return p->m_Type;
                }
                /* 赋值运算 */
                case ASSIGN:
                {   // 返回两边类型
                    // 子节点为[被赋值id，值]
                    Typing::Node* left = check(p->m_Operation.List_Operands[0]);
                    Typing::Node* right = check(p->m_Operation.List_Operands[1]);
                    
                    if (!Typing::Node::isEqual(left, right))
                    {
                        if (Typing::Node::isEqual(right, get("integer", 0)) && Typing::Node::isEqual(left, get("real", 0)))
                        { // 有且仅有左边是real也是没有问题的
                          // 但是不能把real赋值给integer
                          // 这时候返回值就是real
                            p->m_Type = get("real", 0);
                            return p->m_Type;
                        }
                        else 
                        {
                            std::stringstream msg;
                            msg << std::endl << "In line " << p->m_Line << ". 该操作两边的类型不匹配" << std::endl;
                            int hPos = 0;
                            msg << "LHS: " << left->toString(hPos) << std::endl;
                            msg << "RHS: " << right->toString(hPos) << std::endl;
                            raiseError(msg.str());
                        }
                    }
                    p->m_Type = right;
                    return p->m_Type;
                }
                /* 比较运算 */
                case GE: case GT: case LE: case LT: case EQUAL: case UNEQUAL:
                {
                    Typing::Node* left = check(p->m_Operation.List_Operands[0]);
                    Typing::Node* right = check(p->m_Operation.List_Operands[1]);
                    if (!Typing::Node::isEqual(left, right))
                    {
                        if (Typing::Node::isEqual(left, get("real", 0)) || Typing::Node::isEqual(right, get("real", 0)))
                        { // 有且仅有一边是real
                          // 也是没有问题的
                        }
                        else 
                        {
                            std::stringstream msg;
                            msg << std::endl << "In line " << p->m_Line << ". 该操作两边的类型不一致" << std::endl;
                            int hPos = 0;
                            msg << "LHS: " << left->toString(hPos) << std::endl;
                            msg << "RHS: " << right->toString(hPos) << std::endl;
                            raiseError(msg.str());
                        }
                    }
                    // 比较的结果是布尔值
                    p->m_Type = get("boolean", p->m_Line);
                    return p->m_Type;
                }
                /* 算数运算 */
                case PLUS: case MUL: case DIV: case MINUS:
                {
                    Typing::Node* left = check(p->m_Operation.List_Operands[0]);
                    Typing::Node* right = check(p->m_Operation.List_Operands[1]);
                    Typing::Node* int_target = get("integer", p->m_Line);
                    Typing::Node* real_target = get("real", p->m_Line);
                    if (p->m_Operation.NumOperands == 1 && p->m_Operation.Operator == MINUS)
                    {   // 单元取负
                        if (Typing::Node::isEqual(left, real_target) || Typing::Node::isEqual(left, int_target))
                        {   // 取负之后类型不变
                            return left;
                        }
                        std::stringstream msg;
                        msg << std::endl << "In line " << p->m_Line << ". 只能对数取负！" << std::endl;
                        int hPos = 0;
                        msg << "Operand: " << left->toString(hPos) << std::endl;
                        raiseError(msg.str());
                    }

                    // 操作数为整数或浮点都可以，如果有一方为浮点，则结果为浮点
                    if (Typing::Node::isEqual(left, real_target))
                    {   // 左为浮点
                        if (Typing::Node::isEqual(right, int_target)
                         || Typing::Node::isEqual(right, real_target))
                        {   // 右边是数就行
                            p->m_Type = real_target;
                            return real_target;
                        }
                    }
                    else if (Typing::Node::isEqual(left, int_target))
                    {   // 左为整数
                        if (Typing::Node::isEqual(right, real_target))
                        {   // 右为浮点
                            p->m_Type = real_target;
                            return real_target;
                        }
                        else if (Typing::Node::isEqual(right, int_target))
                        {   // 两边都是整数
                            p->m_Type = int_target;
                            return int_target;
                        }
                    }
                    // 报错
                    std::stringstream msg;
                    msg << std::endl << "In line " << p->m_Line << ". 算数运算中，两边都应该是数" << std::endl;
                    int hPos = 0;
                    msg << "LHS: " << left->toString(hPos) << std::endl;
                    msg << "RHS: " << right->toString(hPos) << std::endl;
                    raiseError(msg.str());
                }
                /* 整数运算 */
                case MOD:
                {
                    Typing::Node* left = check(p->m_Operation.List_Operands[0]);
                    Typing::Node* right = check(p->m_Operation.List_Operands[1]);
                    Typing::Node* target = get("integer", p->m_Line);
                    // 取模运算要求都是整数
                    if (Typing::Node::isEqual(target, left)
                        && Typing::Node::isEqual(target, right))
                    {
                        p->m_Type = target;
                        return p->m_Type;
                    }
                    std::stringstream msg;
                    msg << std::endl << "In line " << p->m_Line << ". 去模运算中，两边的操作都应该是整数" << std::endl;
                    int hPos = 0;
                    msg << "LHS: " << left->toString(hPos) << std::endl;
                    msg << "RHS: " << right->toString(hPos) << std::endl;
                    raiseError(msg.str());
                }
                /* 逻辑算数，单元 */
                case NOT:
                {   // 返回结果还是布尔值
                    Typing::Node* type = check(p->m_Operation.List_Operands[0]);
                    Typing::Node* target = get("boolean", p->m_Line);
                    if (Typing::Node::isEqual(type, target))
                    {
                        p->m_Type = target;
                        return target;
                    }
                    std::stringstream msg;
                    msg << std::endl << "In line " << p->m_Line << ". 下面的类型不能进行逻辑运算" << std::endl;
                    int hPos = 0;
                    msg << "Operand: " << type->toString(hPos) << std::endl;
                    raiseError(msg.str());
                }
                /* 逻辑算数 */
                case OR: case AND:
                {   // 逻辑运算，两边都应该是布尔值
                    Typing::Node* target = get("boolean", p->m_Line);
                    Typing::Node* left = check(p->m_Operation.List_Operands[0]);
                    Typing::Node* right = check(p->m_Operation.List_Operands[1]);
                    if (Typing::Node::isEqual(target, left)
                        && Typing::Node::isEqual(target, right))
                    {
                        p->m_Type = target;
                        return target;
                    }
                    std::stringstream msg;
                    msg << std::endl << "In line " << p->m_Line << ". 逻辑运算中，两边的操作都应该是布尔值" << std::endl;
                    int hPos = 0;
                    msg << "LHS: " << left->toString(hPos) << std::endl;
                    msg << "RHS: " << right->toString(hPos) << std::endl;
                    raiseError(msg.str());
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