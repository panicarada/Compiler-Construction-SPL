#include "SymbolTable.hpp"
#include "AST.hpp"
#include "yacc.tab.hpp"

#include "Interpreter.hpp"

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
                    auto procedure = dynamic_cast<Typing::procNode*>(getType(p->m_Operation.List_Operands[0]));
                    if (p->m_Operation.NumOperands == 2)
                    {   // 具有subroutine
                        AST::Node* subroutine = p->m_Operation.List_Operands[1];
                        procedure->m_body = subroutine->m_Operation.List_Operands[0];

                        // 检查函数体的类型
                        for (const auto& it : procedure->m_val_table->Table)
                        {   // 先把函数的参数表暂时加入符号表中
                            insert(it.first, it.second.top(), procedure->m_val_table->LineTable[it.first]);
                        }
                        for (const auto& it : procedure->m_var_table->Table)
                        {   // 类型检查时不区分引用类型
                            insert(it.first, it.second.top(), procedure->m_var_table->LineTable[it.first]);
                        }
                        // 检查函数体
                        check(procedure->m_body);

                        // 把刚才加入的符号弹出
                        for (const auto& it : procedure->m_val_table->Table)
                        {
                            pop(it.first);
                        }
                        for (const auto& it : procedure->m_var_table->Table)
                        {
                            pop(it.first);
                        }
                    }
                    return procedure;
                }
                case PROCEDURE_HEAD:
                {
                    std::string name = p->m_Operation.List_Operands[p->m_Operation.NumOperands]->m_Identifier.Name;
                    auto procedure = new Typing::procNode(name, nullptr);
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
                                    procedure->addParam(false, param->m_Identifier.Name, type, param->m_Line);
                                }
                                else if (para_group->m_Operation.Operator == VAR_PARAM)
                                { // 添加引用参数表
                                    procedure->addParam(true, param->m_Identifier.Name, type, param->m_Line);
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
                    auto function = dynamic_cast<Typing::functNode*>(getType(p->m_Operation.List_Operands[0]));
                    if (p->m_Operation.NumOperands == 2)
                    {   // 具有subroutine 
                        AST::Node* subroutine = p->m_Operation.List_Operands[1];
                        function->m_body = subroutine->m_Operation.List_Operands[0];

                        // 检查函数体的类型
                        for (auto& it : function->m_val_table->Table)
                        {   // 先把函数的参数表暂时加入符号表中
                            insert(it.first, it.second.top(), function->m_val_table->LineTable[it.first]);
                        }   
                        for (auto& it : function->m_var_table->Table)
                        {   // 类型检查时不区分引用类型
                            insert(it.first, it.second.top(), function->m_var_table->LineTable[it.first]);
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
                    auto* function = new Typing::functNode(name, getType(p->m_Operation.List_Operands[p->m_Operation.NumOperands-1]), nullptr);
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
                                    function->addParam(false, param->m_Identifier.Name, type, param->m_Line);
                                }
                                else if (para_group->m_Operation.Operator == VAR_PARAM)
                                { // 添加引用参数表
                                    function->addParam(true, param->m_Identifier.Name, type, param->m_Line);
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
                    // 子节点有四种格式，
                    // [<routine-head>, <routine-body>]任意组合
                    for (int i = 0;i < p->m_Operation.NumOperands; ++i)
                    {
                        auto temp = p->m_Operation.List_Operands[i];
                        if (temp->m_Attribute != AST::Attribute::Operation)
                        {
                            raiseError("检查一下routine相关代码");
                        }
                        if (temp->m_Operation.Operator == ROUTINE_HEAD)
                        {   // 定义区，填入符号表
                            getType(temp);
                        }
                        else if (temp->m_Operation.Operator == ROUTINE_BODY)
                        {   // 主函数区域，需要类型检查
                            check(temp);
                            extern Interpreter* ipt;    // 设置一下解释器的主函数入口
                            ipt->main_entry = temp;
                            printf("Main entry has been set up!\n");
                        }
                        else 
                        {
                            std::stringstream msg;
                            msg << "未知的操作符\"" << temp->m_Operation.Operator << "\"";
                            raiseError(msg.str())
                        }
                    }
                    return nullptr;
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
                {
                    // 见test3.spl以及对应的AST
                    std::string TypeName = p->m_Operation.List_Operands[0]->m_Identifier.Name;
                    insert(TypeName,
                           getType(p->m_Operation.List_Operands[1]), p->m_Operation.List_Operands[0]->m_Line);
                    TypeTable.insert(TypeName);
                    break;
                }
            
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
                        auto enumList = new std::vector<std::string>();
                        for (int i = 0;i < p->m_Operation.NumOperands; ++i)
                        {
                            enumList->push_back(p->m_Operation.List_Operands[i]->m_Identifier.Name);
                        }
                        auto node = new Typing::enumNode(enumList);
                        for (int i = 0;i < p->m_Operation.NumOperands; ++i)
                        {
                            insert(p->m_Operation.List_Operands[i]->m_Identifier.Name,
                                        node, p->m_Operation.List_Operands[i]->m_Line);
                        }
                        return node;
                    }
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
                    << it.second.top()->toString(hPos) << std::endl;
        if ((it.second).top()->nType == Typing::NodeType::t_FUNCTION)
        {   // 函数储存起来，之后要输出函数的参数表
            functions.emplace_back(std::make_pair(it.first, it.second.top()));
        }
        if ((it.second).top()->nType == Typing::NodeType::t_PROCEDURE)
        {   // 过程储存起来，之后要输出过程的参数表
            procedures.emplace_back(std::make_pair(it.first, it.second.top()));
        }
    }
    for (auto& it : functions)
    {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "function: \"" << it.first << "\"" << std::endl;
        auto* function = dynamic_cast<Typing::functNode*>(it.second);
        if (!function->m_val_table->isEmpty())
        {
            function->m_val_table->show();
        }
        if (!function->m_var_table->isEmpty())
        {
            function->m_var_table->show();
        }

    }
    for (auto& it : procedures)
    {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "procedure: \"" << it.first << "\"" << std::endl;
        auto* procedure = dynamic_cast<Typing::procNode*>(it.second);
        if (!procedure->m_val_table->isEmpty())
        {
            procedure->m_val_table->show();
        }
        if (!procedure->m_var_table->isEmpty())
        {
            procedure->m_var_table->show();
        }
    }
}

bool ST::insert(const std::string& str, Typing::Node* node, unsigned int Line)
{
    auto res = Table.find(str);
    if (res == Table.end())
    {
        Table[str] = std::stack<Typing::Node*>();
        Table[str].push(node);
        return true;
    }
    else
    {
        Table[str].push(node);
        return false;
    }
}

Typing::Node* ST::get(const std::string& str, unsigned int line)
{
    auto res = Table.find(str);
    if (res != Table.end())
    {
        return res->second.top();
    }
    // 报错
    std::stringstream msg;
    msg << std::endl << "In line: " << line << ". The type \"" << str << "\" is not available in the symbol table!";
    raiseError(msg.str());
}

Typing::Node* ST::pop(const std::string& str)
{
    auto res = Table.find(str);

    if (res == Table.end())
    { // 如果不存在，没办法删除
        std::stringstream msg;
        msg << "当前符号表中不存在名称: \"" << str << "\"" << std::endl;
        raiseError(msg.str())
    }
    else 
    {
        auto* ret = Table[str].top();
        Table[str].pop();
        if (Table[str].empty())
        {
            Table.erase(str);
        }
        return ret;
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
                auto* type = get(p->m_Identifier.Name, p->m_Line);

                // 函数体中，函数名就是返回参数
                if (type->nType == Typing::NodeType::t_FUNCTION)
                {   // 这时候对应的类型是函数返回类型
                    type = dynamic_cast<Typing::functNode*>(type)->m_resType;
                }
                else if (type->nType == Typing::NodeType::t_CONSTANT)
                {   // 常数类型
                    type = dynamic_cast<Typing::constNode*>(type)->m_Sys;
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
                /* goto语句，跳转到对应label */
                case GOTO:
                { // 格式为[integer"]
                    assert(p->m_Operation.List_Operands[0]->m_Attribute == AST::Attribute::Constant);
                    auto jump_label = check(p->m_Operation.List_Operands[0]);
                    if (Typing::Node::isEqual(get("integer", 0), jump_label))
                    {
                        return nullptr;
                    }
                    std::stringstream msg;
                    msg << std::endl << "In line " << p->m_Line << ". goto statement的label必须为整数" << std::endl;
                    raiseError(msg.str());
                }
                case LABEL_STMT:
                {   // 带有标签的statement，用于跳转
                    // 子节点格式为[标签（整数），statement]
                    assert(p->m_Operation.List_Operands[0]->m_Attribute == AST::Attribute::Constant); // 标签必须是常数
                    auto label = check(p->m_Operation.List_Operands[0]);
                    if (Typing::Node::isEqual(get("integer", 0), label))
                    {
                        check(p->m_Operation.List_Operands[1]);
                        // 本身没有类型
                        return nullptr;
                    }
                    std::stringstream msg;
                    msg << std::endl << "In line " << p->m_Line << ". label statement的label必须为整数" << std::endl;
                    raiseError(msg.str());
                }
                case WHILE:
                case REPEAT:
                { // 子节点格式为，[条件，statement]
                    // while和repeat是一致的
                    // 例子请见guess.spl
                    auto condition = check(p->m_Operation.List_Operands[0]);
                    if (Typing::Node::isEqual(get("boolean", 0), condition))
                    {   // 条件需要为布尔值
                        // 检查语句
                        check(p->m_Operation.List_Operands[1]);
                        // 本身没有返回值
                        return nullptr;
                    }
                    std::stringstream msg;
                    msg << std::endl << "In line " << p->m_Line << ". while语句的条件必须为布尔值" << std::endl;
                    raiseError(msg.str());
                }
                    /* for循环 */
                case DOWNTO:
                case TO:
                {   // 四个子节点，格式为[id, 下界，上界，statement]，例子请见bubble_sort.spl
                    auto index_node = check(p->m_Operation.List_Operands[0]);
                    std::stringstream msg;
                    int hPos = 0;
                    msg << std::endl << "In line " << p->m_Line << ". For循环语句只支持整型的上下标和变量" << std::endl;
                    msg << "given: " << std::endl;

                    auto target = get("integer", 0);    // id, 上下界都需要为整型
                    if (Typing::Node::isEqual(target, index_node))
                    {   // 一定是整数变量类型
                        auto lower = check(p->m_Operation.List_Operands[1]);
                        if (Typing::Node::isEqual(target, lower))
                        {
                            auto upper = check(p->m_Operation.List_Operands[2]);
                            if (Typing::Node::isEqual(target, upper))
                            {   // 前三个子节点没有问题，递归检查语句
                                check(p->m_Operation.List_Operands[3]);
                                // 本身没有类型
                                return nullptr;
                            }
                            else
                            {
                                hPos = 0;
                                msg << "upper: " << upper->toString(hPos) << std::endl;
                            }
                        }
                        else
                        {
                            hPos = 0;
                            msg << "lower: " << lower->toString(hPos) << std::endl;
                        }
                    }
                    else
                    {
                        msg << "index: " << index_node->toString(hPos) << std::endl;
                    }
                    raiseError(msg.str());
                }
                case READ:
                {   // 系统过程，类似于scanf读取用户输入，但是一次只能读取一个
                    // 子节点结构为["read", 待读取的变量]
                    auto input_node = p->m_Operation.List_Operands[1];
                    if (input_node->m_Attribute != AST::Attribute::Identifier)
                    {
                        std::stringstream msg;
                        msg << std::endl << "In line " << p->m_Line << ". read的参数只能是变量" << std::endl;
                        msg << "given: " << input_node->m_Attribute << std::endl;
                        raiseError(msg.str());
                    }
                    auto input = get(input_node->m_Identifier.Name, p->m_Line);
                    // 并且只能读取基础类型
                    if (input->nType == Typing::NodeType::t_SYS_TYPE)
                    {   // 返回结果就是读取的值
                        return input;
                    }
                    std::stringstream msg;
                    int hPos = 0;
                    msg << std::endl << "In line " << p->m_Line << ". read只支持基础类型" << std::endl;
                    msg << "given: " << input->toString(hPos) << std::endl;
                    raiseError(msg.str());
                }
                case SYS_PROC:
                {   // 系统过程，只有write和writeln两种，
                    // 支持任意多个参数传入
                    // 但是只支持基础类型
                    for (int i = 1; i < p->m_Operation.NumOperands; ++i)
                    {
                        auto input = check(p->m_Operation.List_Operands[i]);
                        if (input->nType != Typing::NodeType::t_SYS_TYPE)
                        {
                            std::stringstream msg;
                            int hPos = 0;
                            msg << std::endl << "In line " << p->m_Line << ". write/writeln只支持基础类型" << std::endl;
                            msg << "given: " << input->toString(hPos) << std::endl;
                            raiseError(msg.str());
                        }
                    }
                    return nullptr;
                }
                    /* 数组访问 */
                case BRACKET:
                { // 关于数组的例子请见swap.spl
                    // 子节点为[数组名，索引]
                    auto node = check(p->m_Operation.List_Operands[0]);
                    if (node->nType != Typing::NodeType::t_ARRAY)
                    {
                        std::stringstream msg;
                        msg << std::endl << "In line " << p->m_Line << ". 无法对下面的类型进行数组访问" << std::endl;
                        int hPos = 0;
                        msg << "given: " << node->toString(hPos) << std::endl;
                        raiseError(msg.str());
                    }
                    auto array = dynamic_cast<Typing::arrayNode *>(node);
                    auto idxType = check(p->m_Operation.List_Operands[1]);

                    // 检查数组访问下标类型是否一致
                    // 不检查越界！
                    auto target = array->m_IdxType;
                    if (target->nType == Typing::NodeType::t_RANGE)
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
                    msg << "expected: " << std::endl << target->toString(hPos) << std::endl;
                    msg << "given: " << std::endl << idxType->toString(hPos) << std::endl;
                    raiseError(msg.str());
                }
                case CASE_STMT:
                {   // case部分详见is_even.spl生成的语法树
                    // 子节点格式为[表达式，case-list]
                    auto expression = check(p->m_Operation.List_Operands[0]);
                    auto case_list = p->m_Operation.List_Operands[1];
                    // case-list子节点的格式为[case, case, ..., ...]
                    for (int i = 0; i < case_list->m_Operation.NumOperands; ++i)
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
                                msg << "expected: " << std::endl << expression->toString(hPos) << std::endl;
                                msg << "given: " << std::endl << case_exp->toString(hPos) << std::endl;
                                raiseError(msg.str());
                            }
                        }
                        // 检查case内部语句
                        check(case_unit->m_Operation.List_Operands[1]);
                    }
                    // 本身没有类型
                    return nullptr;
                }
                    /* 过程调用 */
                case CALL_PROC:
                {   // 注意，这里是调用过程，而非定义过程
                    auto procedure = dynamic_cast<Typing::procNode *>(get(
                            p->m_Operation.List_Operands[0]->m_Identifier.Name, p->m_Line));
                    int size = procedure->m_Params.size();
                    if (size != p->m_Operation.NumOperands - 1)
                    {
                        std::stringstream msg;
                        msg << std::endl << "In line " << p->m_Line << ". 过程参数数目不匹配" << std::endl;
                        int hPos = 0;
                        msg << procedure->toString(hPos) << std::endl;
                        msg << "expected: " << size << std::endl;
                        msg << "given: " << p->m_Operation.NumOperands - 1 << std::endl;
                        raiseError(msg.str());
                    }
                    int i = 1;
                    for (auto it = procedure->m_Params.begin(); it != procedure->m_Params.end(); ++it)
                    {
                        auto input = check(p->m_Operation.List_Operands[i++]); // 第i个输入的参数
                        Typing::Node *param;
                        if (it->second)
                        {   // is var = true
                            param = procedure->m_var_table->get(it->first, p->m_Line);
                        }
                        else
                        {
                            param = procedure->m_val_table->get(it->first, p->m_Line);
                        }

                        if (!Typing::Node::isEqual(param, input))
                        {
                            std::stringstream msg;
                            msg << std::endl << "In line " << p->m_Line << ". 过程参数类型不匹配" << std::endl;
                            int hPos = 0;
                            msg << "expected: " << std::endl << param->toString(hPos) << std::endl;
                            msg << "input: " << std::endl << input->toString(hPos) << std::endl;
                            raiseError(msg.str());
                        }
                    }
                    // 不具有返回类型
                    return nullptr;
                }
                    /* 函数调用 */
                case CALL_FUNCT:
                {   // 注意，这里是调用函数，而非定义函数
                    // 子节点格式为[函数名, 输入1, 输入2, ...]
                    auto function = dynamic_cast<Typing::functNode *>(get(
                            p->m_Operation.List_Operands[0]->m_Identifier.Name, p->m_Line));

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
                    for (auto it = function->m_Params.begin(); it != function->m_Params.end(); ++it)
                    {
                        auto input = check(p->m_Operation.List_Operands[i++]); // 第i个输入的参数
                        Typing::Node *param;

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
                            msg << "expected: " << std::endl << param->toString(hPos) << std::endl;
                            msg << "input: " << std::endl << input->toString(hPos) << std::endl;
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
                    for (int i = 0; i < p->m_Operation.NumOperands; ++i)
                    {
                        check(p->m_Operation.List_Operands[i]);
                    }
                    return nullptr; // 本身没类型
                }
                case IF:
                {
                    // 子节点为[条件, if-claus, <else-clause>]
                    Typing::Node *condition = check(p->m_Operation.List_Operands[0]);
                    if (Typing::Node::isEqual(condition, get("boolean", 0)))
                    {   // 条件一定要是布尔值
                        check(p->m_Operation.List_Operands[1]); // 检查if-clause
                        if (p->m_Operation.NumOperands == 3)
                        {   // 存在else-clause
                            check(p->m_Operation.List_Operands[2]);
                        }
                        return nullptr; // 本身无类型
                    }
                    std::stringstream msg;
                    msg << std::endl << "In line " << p->m_Line << ". if语句条件必须为布尔值" << std::endl;
                    int hPos = 0;
                    msg << "given: " << condition->toString(hPos) << std::endl;
                    raiseError(msg.str());
                }
                    /* 函数体 */
                case ROUTINE_BODY:
                    return check(p->m_Operation.List_Operands[0]);
                    /* 结构体访问 */
                case DOT:
                {   // 结构体成员访问
                    // 子节点为[record名，成员名]
                    auto node = get(p->m_Operation.List_Operands[0]->m_Identifier.Name, p->m_Line);
                    Typing::recordNode *record;
                    if (node->nType == Typing::NodeType::t_RECORD)
                    {
                        record = dynamic_cast<Typing::recordNode *>(node);
                    }
                    else if (node->nType == Typing::NodeType::t_FUNCTION)
                    {   // 在函数内部，函数名就是返回值
                        auto function = dynamic_cast<Typing::functNode *>(node);

                        if (function->m_resType->nType == Typing::NodeType::t_RECORD)
                        {
                            record = dynamic_cast<Typing::recordNode *>(function->m_resType);
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
                    Typing::Node *left = check(p->m_Operation.List_Operands[0]);
                    Typing::Node *right = check(p->m_Operation.List_Operands[1]);

                    if (!Typing::Node::isEqual(left, right))
                    {
                        if (Typing::Node::isEqual(right, get("integer", 0)) &&
                            Typing::Node::isEqual(left, get("real", 0)))
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
                case _GE_:
                case _GT_:
                case _LE_:
                case _LT_:
                case EQUAL:
                case UNEQUAL:
                {
                    Typing::Node *left = check(p->m_Operation.List_Operands[0]);
                    Typing::Node *right = check(p->m_Operation.List_Operands[1]);
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
                case PLUS:
                case MUL:
                case DIV:
                case MINUS:
                {
                    Typing::Node *left = check(p->m_Operation.List_Operands[0]);
                    Typing::Node *right = check(p->m_Operation.List_Operands[1]);
                    Typing::Node *int_target = get("integer", p->m_Line);
                    Typing::Node *real_target = get("real", p->m_Line);

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
                    Typing::Node *left = check(p->m_Operation.List_Operands[0]);
                    Typing::Node *right = check(p->m_Operation.List_Operands[1]);
                    Typing::Node *target = get("integer", p->m_Line);
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
                    Typing::Node *type = check(p->m_Operation.List_Operands[0]);
                    Typing::Node *target = get("boolean", p->m_Line);
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
                case OR:
                case AND:
                {   // 逻辑运算，两边都应该是布尔值
                    Typing::Node *target = get("boolean", p->m_Line);
                    Typing::Node *left = check(p->m_Operation.List_Operands[0]);
                    Typing::Node *right = check(p->m_Operation.List_Operands[1]);
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
                case SYS_FUNCT:
                { // 系统函数，都是一个输入
                    // 格式为["name", 输入]
                    auto function = p->m_Operation.List_Operands[0];
                    if (function->m_Attribute == AST::Attribute::Identifier)
                    {
                        std::string name = function->m_Identifier.Name;
                        auto int_type = get("integer", 0);
                        auto real_type = get("real", 0);
                        auto char_type = get("char", 0);
                        auto bool_type = get("boolean", 0);
                        // 输入参数
                        auto input = check(p->m_Operation.List_Operands[1]);
                        if (name == "chr")
                        { // 计算ASCII码，必须是整数
                            if (Typing::Node::isEqual(input, int_type))
                            { // 返回字符
                                p->m_Type = char_type;
                                return char_type;
                            }
                        }
                        else if (name == "odd")
                        {   // 判断是否为偶数
                            if (Typing::Node::isEqual(input, int_type))
                            { // 返回布尔值
                                p->m_Type = bool_type;
                                return bool_type;
                            }
                        }
                        else if (name == "abs" || name == "sqr")
                        { // 保持类型不变的算子
                            if (Typing::Node::isEqual(input, int_type) || Typing::Node::isEqual(input, real_type))
                            {
                                p->m_Type = input;
                                return input;
                            }
                        }
                        else if (name == "sqrt")
                        { // 返回都是real
                            if (Typing::Node::isEqual(input, int_type) || Typing::Node::isEqual(input, real_type))
                            {
                                p->m_Type = real_type;
                                return real_type;
                            }
                        }
                        else if (name == "ord" || name == "pred" || name == "succ")
                        { // 只对有序类型有效
                            if (Typing::Node::isEqual(input, int_type)
                                || Typing::Node::isEqual(input, char_type)
                                || input->nType == Typing::NodeType::t_ENUM)
                            {   // 返回本身类型
                                p->m_Type = input;
                                return input;
                            }
                        }
                    }
                    std::stringstream msg;
                    msg << std::endl << "In line " << p->m_Line << ". 错误的系统函数调用\"";
                    raiseError(msg.str());
                }
                default:
                {
                    std::stringstream msg;
                    msg << std::endl << "In line " << p->m_Line << ". 未知的操作符\"" << p->m_Operation.Operator << "\"";
                    raiseError(msg.str());
                }
            }
        default:
            break;
    }
}