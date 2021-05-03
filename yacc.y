%{
    #include <iostream>    
    #include <stdarg.h>
	#include <vector>
    #include "Utils.hpp"
    #include "Interpreter.hpp"
	#include <fstream>

	int line_number = 1;
    int yylex(void);
    void yyerror(const char *);
%}

%union {
    int iValue; // integer value
    double dValue; // double value
    char cValue; // char value
    char* sValue;
    Node* NodePtr; // Node Pointer
	std::vector<Node*>* NodePtrList; // List
};
// token数据类型
%token <iValue> INTEGER
%token <dValue> REAL
%token <cValue> CHAR
%token <sValue> STRING SYS_TYPE
%token <sValue> ID

// 语法树节点
%type <NodePtr> expr term factor const_value expression routine
%type <NodePtr> routine_head routine_body const_part type_part var_part 
%type <NodePtrList> const_expr_list name_list var_para_list val_para_list routine_part
%type <NodePtrList> expression_list args_list field_decl_list
%type <NodePtr> compound_stmt stmt_list stmt non_label_stmt if_stmt goto_stmt
%type <NodePtr> while_stmt case_stmt case_expr case_expr_list proc_stmt
%type <NodePtr> assign_stmt var_decl var_decl_list for_stmt else_clause
%type <NodePtr> repeat_stmt type_decl_list type_definition function_decl function_head parameters
%type <NodePtr> para_decl_list para_type_list sub_routine procedure_decl procedure_head
%type <NodePtr> simple_type_decl type_decl field_decl record_type_decl array_type_decl
%type <sValue> program_head 
%type <iValue> direction

// 运算符、定界符
%token LP RP LB RB DOT COMMA COLON MUL DIV UNEQUAL NOT
%token PLUS MINUS GE GT LE LT EQUAL ASSIGN MOD DOTDOT SEMI

// 系统函数、过程、常数、类型等单词
%token READ
%token <sValue> SYS_PROC SYS_FUNCT SYS_CON

// 关键字
%token AND ARRAY _BEGIN CASE CONST
%token DO DOWNTO ELSE END
%token FOR FUNCTION GOTO IF
%token OF OR PACKED
%token PROCEDURE PROGRAM RECORD REPEAT
%token THEN TO TYPE UNTIL VAR WHILE

// 语法树中自定义的token
%token ROUTINE ROUTINE_BODY ROUTINE_HEAD CONST_PART VAR_PART BRACKET
%token CASE_STMT CASE_LIST TYPE_PART VAL_PARAM VAR_PARAM PARA_LIST FUNCTION_HEAD
%token SUB_ROUTINE PROCEDURE_HEAD PROC LABEL_STMT FUNCT FIELD_DECL 
%token ENUM
%%
program 
	:  program_head routine DOT
	{
		std::ofstream outFile("AST.out");
		outFile << "Program Name: " << $1 << std::endl;
		Interpreter::execute($2, outFile);
		exit(0);
	}
	;
program_head 
	: PROGRAM ID SEMI
	{
		$$ = new char[strlen($2)];
		strcpy($$, $2);
	}
	;

routine
	: routine_head routine_body
	{
		// 因为两个都nullable
		// 所以把所有非空部分拼成一个列表再一次性构造$$，避免了很多的if-else语句
		
		std::vector<Node*>* Temp = new std::vector<Node*>();
		if ($1 != NULL) Temp->push_back($1);
		if ($2 != NULL) Temp->push_back($2);
		if (Temp->size() > 0) $$ = new Node(ROUTINE, Temp);
		else $$ = NULL;
	}
	;

sub_routine
	: routine_head routine_body
	{
		// 因为两个都nullable
		// 所以把所有非空部分拼成一个列表再一次性构造$$，避免了很多的if-else语句
		
		std::vector<Node*>* Temp = new std::vector<Node*>();
		if ($1) Temp->push_back($1);
		if ($2) Temp->push_back($2);
		if (Temp->size() > 0)
			$$ = new Node(SUB_ROUTINE, Temp);
		else
			$$ = NULL;
	}
	;

routine_head
	: label_part const_part type_part var_part routine_part
	{
		// 因为很多部分有nullable
		// 所以把所有非空部分拼成一个列表再一次性构造$$，避免了很多的if-else语句
		
		std::vector<Node*>* Temp = new std::vector<Node*>();
		if ($2 != NULL) Temp->push_back($2);
		if ($3 != NULL) Temp->push_back($3);
		if ($4 != NULL) Temp->push_back($4);
		if ($5 != NULL) 
		{
			for (auto node : *($5))
				Temp->push_back(node);
		}
		if (Temp->size() > 0)
			$$ = new Node(ROUTINE_HEAD, Temp);
		else
			$$ = NULL;
	}
	;

label_part
	: 
	;

const_part
	: CONST const_expr_list
	{
		$$ = new Node(CONST_PART, $2);
	}
	| {$$ = NULL;}
	;

const_expr_list
	: const_expr_list ID EQUAL const_value SEMI
	{
		$$->push_back(new Node(EQUAL, 2, new Node($2, NodeType::Identifier), $4));
	}
	| ID EQUAL const_value SEMI
	{
		$$ = new std::vector<Node *>();
		$$->push_back(new Node(EQUAL, 2, new Node($1, NodeType::Identifier), $3));
	}
	;

const_value
	: INTEGER
    {
        ValConstant temp;
        temp.Type = ConstantType::Integer;
        temp.iValue = $1;
        $$ = new Node(temp);
    }
	| REAL
    {
        ValConstant temp;
        temp.Type = ConstantType::Real;
        temp.dValue = $1;
        $$ = new Node(temp);
    }
	| CHAR
    {
        ValConstant temp;
        temp.Type = ConstantType::Char;
		// std::cout << $1 << std::endl;
        temp.cValue = $1;
        $$ = new Node(temp);
    }
	| STRING
	{
		ValConstant temp;
        temp.Type = ConstantType::String;
		// std::cout << $1 << std::endl;
        temp.sValue = $1;
        $$ = new Node(temp);
	}
	| SYS_CON
	{
		ValConstant temp;
		temp.Type = ConstantType::Boolean;
		// std::cout << $1 << std::endl;
		temp.bValue = $1;
		$$ = new Node(temp);
	}
	;

type_part
	: TYPE type_decl_list
	{
		$$ = $2;
	}
	| {$$ = NULL;}
	;

type_decl_list
	: type_decl_list type_definition 
	{
		$$->add($2);
	}
	| type_definition
	{
		$$ = new Node(TYPE_PART, 1, $1);
	}
	;

type_definition
	: ID EQUAL type_decl SEMI
	{
		$$ = new Node(TYPE, 2
					  , new Node($1, NodeType::Typename)
					  , $3);
	}
	;

type_decl
	: simple_type_decl
	{
		$$ = $1;
	}
	| array_type_decl
	{
		$$ = $1;
	}
	| record_type_decl
	{
		$$ = $1;
	}
	;

simple_type_decl
	: SYS_TYPE
	{
		$$ = new Node($1, NodeType::Typename);
	}
	| ID
	{
		$$ = new Node($1, NodeType::Typename);
	}
	| LP name_list RP
	{
		$$ = new Node(ENUM, $2);
	}
	| const_value DOTDOT const_value
	{
		$$ = new Node(DOTDOT, 2, $1, $3);
	}
	| MINUS const_value DOTDOT const_value
	{
		$$ = new Node(DOTDOT, 2,
					  new Node(MINUS, 1, $2),
					  $4);
	}
	| MINUS const_value DOTDOT MINUS const_value
	{
		$$ = new Node(DOTDOT, 2,
					  new Node(MINUS, 1, $2),
					  new Node(MINUS, 1, $5));
	}
	| ID DOTDOT ID
	{
		$$ = new Node(DOTDOT, 2,
					  new Node($1, NodeType::Identifier),
					  new Node($3, NodeType::Identifier));
	}
	;

array_type_decl
	: ARRAY LB simple_type_decl RB OF type_decl
	{
		$$ = new Node(ARRAY, 1, $6);
		$$->add($3);
	}
	;

record_type_decl
	: RECORD field_decl_list END
	{
		$$ = new Node(RECORD, $2);
	}
	;

field_decl_list
	: field_decl_list field_decl 
	{
		$$->push_back($2);
	}
	| field_decl
	{
		$$ = new std::vector<Node *>();
		$$->push_back($1);
	}
	;

field_decl
	: name_list COLON type_decl SEMI
	{
		$$ = new Node(FIELD_DECL, 1, $3);
		$$->add($1);
	}
	;

name_list
	: name_list COMMA ID 
	{
		$$->push_back(new Node($3, NodeType::Identifier));
	}
	| ID
	{
		$$ = new std::vector<Node *>();
		$$->push_back(new Node($1, NodeType::Identifier));
	}
	;

var_part
	: VAR var_decl_list
	{
		$$ = $2;
	}
	| {$$ = NULL;}
	;

var_decl_list
	: var_decl_list var_decl
	{
		$$->add($2);
	}
	| var_decl
	{
		$$ = new Node(VAR_PART, 1, $1);
	}
	;

var_decl
	: name_list COLON type_decl SEMI
	{

		std::cout << "line no: " << line_number << std::endl;
		$$ = new Node(VAR, 1, $3);
		$$->add($1);
	}
	;

routine_part
	: routine_part function_decl
	{
		$$->push_back($2);
	}
	| routine_part procedure_decl
	{
		$$->push_back($2);
	}
	| function_decl
	{
		$$ = new std::vector<Node *>();
		$$->push_back($1);
	}
	| procedure_decl
	{
		$$ = new std::vector<Node *>();
		$$->push_back($1);
	}
	| {$$ = NULL;}
	;

function_decl
	: function_head SEMI sub_routine SEMI
	{
		if ($3)
			$$ = new Node(FUNCTION, 2, $1, $3);
		else
			$$ = new Node(FUNCTION, 1, $1);
	}
	;
function_head
	: FUNCTION ID parameters COLON simple_type_decl
	{
		if ($3)
		{
			$$ = new Node(FUNCTION_HEAD, 2, $3, $5);
		}
		else
		{
			$$ = new Node(FUNCTION_HEAD, 1, $5);
		}
		$$->add(new Node($2, NodeType::Identifier));
		/*
			Hacking Trick: 最后一个孩子是类型名称，
			在语法树中，不希望类型和变量为sibling，但是父节点Operation无法记录类型名称，
			所以在数组中保留类型名称，在构造语法树时父节点可以访问，
			但是在数目上假装其不存在，这样按for循环绘制就不会绘制出来
		*/
		$$->m_Operation.NumOperands -= 1;
	}
	;

procedure_decl
	: procedure_head SEMI sub_routine SEMI
	{
		$$ = new Node(PROCEDURE, 2, $1, $3);
	}
	;

procedure_head
	: PROCEDURE ID parameters
	{
		if ($3)
		{
			$$ = new Node(PROCEDURE_HEAD, 1, $3);
			$$->add(new Node($2, NodeType::Identifier));
		}
		else
		{
			$$ = new Node($2, NodeType::Identifier);
		}
		/*
			Hacking Trick: 最后一个孩子是类型名称，
			在语法树中，不希望类型和变量为sibling，但是父节点Operation无法记录类型名称，
			所以在数组中保留类型名称，在构造语法树时父节点可以访问，
			但是在数目上假装其不存在，这样按for循环绘制就不会绘制出来
		*/
		$$->m_Operation.NumOperands -= 1;
	}
	;

parameters
	: LP para_decl_list RP
	{ 
		$$ = $2;
	}
	| {$$ = NULL;}
	;
para_decl_list
	: para_decl_list SEMI para_type_list
	{
		$$->add($3);
	}
	| para_type_list
	{
		$$ = new Node(PARA_LIST, 1, $1);
	}
	;
para_type_list
	: var_para_list COLON simple_type_decl // var x,y,z : integer，引用传递
	{
		$$ = new Node(VAR_PARAM, 1, $3);
		$$->add($1);
	}
	| val_para_list COLON simple_type_decl // x,y,z : integer，形参传递
	{
		$$ = new Node(VAL_PARAM, 1, $3);
		$$->add($1);
	}
	;
var_para_list
	: VAR name_list
	{
		$$ = $2;
	}
	;
val_para_list
	: name_list
	{
		$$ = $1;
	}
	;

routine_body
	: compound_stmt
	{
		if ($1)
		{
			$$ = new Node(ROUTINE_BODY, 1, $1);
		}
		else
		{
			$$ = NULL;
		}
	}
	;
compound_stmt
	: _BEGIN stmt_list END
	{
		$$ = $2;
	}
	;
stmt_list
	: stmt_list stmt SEMI
	{
		if ($1 == NULL)
		{
			$$ = $2;
		}
		else
		{
			$$ = new Node(SEMI, 2, $1, $2);
		}
	}
	| {$$ = NULL;}
	;
stmt
	: INTEGER COLON non_label_stmt
	{
		ValConstant temp;
		temp.Type = ConstantType::Integer;
		temp.iValue = $1;
		$$ = new Node(LABEL_STMT, 2, new Node(temp), $3);
	}
	| non_label_stmt
	{
		$$ = $1;
	}
	;
non_label_stmt
	: assign_stmt {$$ = $1;}
	| proc_stmt {$$ = $1;}
	| compound_stmt {$$ = $1;}
	| if_stmt {$$ = $1;}
	| repeat_stmt {$$ = $1;}
	| while_stmt {$$ = $1;}
	| for_stmt {$$ = $1;}
	| case_stmt {$$ = $1;}
	| goto_stmt {$$ = $1;}
	;

assign_stmt
	: ID ASSIGN expression
	{
		$$ = new Node(ASSIGN, 2, new Node($1, NodeType::Identifier), $3);
	}
	| ID LB expression RB ASSIGN expression
	{
		$$ = new Node(ASSIGN, 2, 
					  new Node(BRACKET, 2, new Node($1, NodeType::Identifier), $3),
					  $6);
	}
	| ID DOT ID ASSIGN expression
	{
		$$ = new Node(ASSIGN, 2,
					  new Node(DOT, 2, new Node($1, NodeType::Identifier),
					  				   new Node($3, NodeType::Identifier))
					  , $5);
	}
	;

proc_stmt
	: ID
	{
		$$ = new Node(PROC, 1, new Node($1, NodeType::Identifier));
	}
	| ID LP args_list RP
	{
		$$ = new Node(PROC, 1, new Node($1, NodeType::Identifier));
		$$->add($3);
	}
	| SYS_PROC
	{
		$$ = new Node(SYS_PROC, 1, new Node($1, NodeType::Identifier));
	}
	| SYS_PROC LP expression_list RP
	{
		$$ = new Node(SYS_PROC, 1, new Node($1, NodeType::Identifier));
		$$->add($3);
	}
	| READ LP factor RP // unknown
	;

if_stmt
	: IF expression THEN stmt else_clause
	{
		if ($5)
		{
			$$ = new Node(IF, 3, $2, $4, $5);
		}
		else 
		{
			$$ = new Node(IF, 2, $2, $4);
		}
	}
	;
else_clause
	: ELSE stmt {$$ = $2;}
	| {$$ = NULL;}
	;
repeat_stmt
	: REPEAT stmt_list UNTIL expression
	{
		$$ = new Node(REPEAT, 2, $2, $4);
	}
	;
while_stmt
	: WHILE expression DO stmt
	{
		$$ = new Node(WHILE, 2, $2, $4);
	}
	;

for_stmt
	: FOR ID ASSIGN expression direction expression DO stmt
	{
		$$ = new Node($5, 4, new Node($2, NodeType::Identifier), 
						$4, $6, $8);
	}
	;
direction // 这条是没问题的，返回token
	: TO {$$ = TO;}
	| DOWNTO {$$ = DOWNTO;}
	;
case_stmt
	: CASE expression OF case_expr_list END
	{
		$$ = new Node(CASE_STMT, 2, $2, $4);
	}
	;
case_expr_list
	: case_expr_list case_expr 
	{
		$$->add($2);
	}
	| case_expr
	{
		$$ = new Node(CASE_LIST, 1, $1);
	}
	;
case_expr
	: const_value COLON stmt SEMI
	{
		$$ = new Node(CASE, 2, $1, $3);
	}
	| ID COLON stmt SEMI
	{
		$$ = new Node(CASE, 2
					  , new Node($1, NodeType::Identifier)
					  , $3);
	}
	;
goto_stmt
	: GOTO INTEGER
	{
		ValConstant temp;
		temp.Type = ConstantType::Integer;
        temp.iValue = $2;
		$$ = new Node(GOTO, 1, new Node(temp));
	}
	;
expression_list
	: expression_list COMMA expression
	{
		$$->push_back($3);
	}
	| expression
	{
		$$ = new std::vector<Node*>();
		$$->push_back($1);
	}
	;
expression
	: expression GE expr 
    {
        $$ = new Node(GE, 2, $1, $3);
    }
	| expression GT expr
    {
        $$ = new Node(GT, 2, $1, $3);
    }
	| expression LE expr
    {
        $$ = new Node(LE, 2, $1, $3);
    }
	| expression LT expr
    {
        $$ = new Node(LT, 2, $1, $3);
    }
	| expression EQUAL expr
    {
        $$ = new Node(EQUAL, 2, $1, $3);
    }
	| expression UNEQUAL expr
    {
        $$ = new Node(UNEQUAL, 2, $1, $3);
    }
	| expr
    {
        $$ = $1;
    }
	;
expr
	: expr PLUS term
    {
        $$ = new Node(PLUS, 2, $1, $3);
    }
	| expr MINUS term
    {
        $$ = new Node(MINUS, 2, $1, $3);
    }
	| expr OR term
	{
		$$ = new Node(OR, 2, $1, $3);
	}
	| term
    {
        $$ = $1;
    }
	;
term
	: term MUL factor
    {
        $$ = new Node(MUL, 2, $1, $3);
    }
	| term DIV factor
    {
        $$ = new Node(DIV, 2, $1, $3);
    }
	| term MOD factor
    {
        $$ = new Node(MOD, 2, $1, $3);
    }
	| term AND factor
	{
		$$ = new Node(AND, 2, $1, $3);
	}
	| factor
    {
        $$ = $1;
    }
	;
factor
	: ID
    {
        $$ = new Node($1, NodeType::Identifier);
    }
	| ID LP args_list RP
	{
		$$ = new Node(FUNCT, 1
					  , new Node($1, NodeType::Identifier));
		$$->add($3);
	}
	| SYS_FUNCT 
	{
		$$ = new Node(SYS_FUNCT, 1
					  , new Node($1, NodeType::Identifier));
	}
	| SYS_FUNCT LP args_list RP
	{
		$$ = new Node(SYS_FUNCT, 1
					  , new Node($1, NodeType::Identifier));
		$$->add($3);
	}
	| const_value
    {
        $$ = $1;
    }
	| LP expression RP
    {
        $$ = $2;
    }
	| NOT factor
	{
		$$ = new Node(NOT, 1, $2);
	}
	| MINUS factor
	{
		$$ = new Node(MINUS, 1, $2);
	}
	| ID LB expression RB
	{
		$$ = new Node(BRACKET, 2
					  , new Node($1, NodeType::Identifier)
					  , $3);
	}
	| ID DOT ID
	{
		$$ = new Node(DOT, 2
					  , new Node($1, NodeType::Identifier)
					  , new Node($3, NodeType::Identifier));
	}
	;
args_list
	: args_list COMMA expression
	{
		$$->push_back($3);
	}
	| expression
	{
		$$ = new std::vector<Node *>();
		$$->push_back($1);
	}
	;
%%
void yyerror(const char* s)
{
    fprintf(stdout, "%s\n", s);
}

int main(int argc, char* argv[])
{
	FILE* fp = NULL;
	extern FILE* yyin;
	yyin = stdin;
	if (argc > 1)
	{
		std::cout << argv[1] << std::endl;
		fp = fopen(argv[1], "r");
		if (fp)
		{ // 成功打开文件
			yyin = fp;
		}
	}
    yyparse();
	if (fp) fclose(fp);
    return 0;
}