%{
    #include <iostream>    
    #include <stdarg.h>
	#include <vector>
	#include <fstream>
	#include <filesystem>

    #include "AST.hpp"
    #include "Interpreter.hpp"
    #include "CodeGenerator.hpp"

	// 构建语法树的解释器
	Interpreter* ipt;

	#define YYDEBUG 1 // This is new

	extern void yyset_in(FILE * in_str);

	unsigned int line_number = 1;
    extern int yylex(void);
	extern int yylineno;
    void yyerror(const char *);
	int yyparse(void);
	std::string inFilename;
%}



%union {
    int iValue; // integer value
    double dValue; // double value
    char cValue; // char value
    char* sValue;
    AST::Node* NodePtr; // Node Pointer
	std::vector<AST::Node*>* NodePtrList; // List
};
// token数据类型
%token <iValue> INTEGER
%token <dValue> REAL
%token <cValue> CHAR
%token <sValue> STRING SYS_TYPE
%token <sValue> _ID_

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

// 运算符、定界符
%token _LP_ RP LB RB DOT COMMA COLON MUL DIV UNEQUAL NOT
%token PLUS MINUS _GE_ _GT_ _LE_ _LT_ EQUAL ASSIGN MOD DOTDOT SEMI

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
%token SUB_ROUTINE PROCEDURE_HEAD CALL_PROC LABEL_STMT CALL_FUNCT FIELD_DECL
%token ENUM
%%
program 
	:  program_head routine DOT
	{
		std::string Program = $1;
		ipt = new Interpreter();
		ipt->execute($2, inFilename, Program);
		exit(0);
	}
	;
program_head 
	: PROGRAM _ID_ SEMI
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
		std::vector<AST::Node*>* Temp = new std::vector<AST::Node*>();
		if ($1 != NULL) Temp->push_back($1);
		if ($2 != NULL) Temp->push_back($2);
		if (Temp->size() > 0) $$ = new AST::Node(0, ROUTINE, Temp);
		else $$ = nullptr;
	}
	;

sub_routine
	: routine_head routine_body
	{
		// 因为两个都nullable
		// 所以把所有非空部分拼成一个列表再一次性构造$$，避免了很多的if-else语句
		
		std::vector<AST::Node*>* Temp = new std::vector<AST::Node*>();
		if ($1) Temp->push_back($1);
		if ($2) Temp->push_back($2);
		if (Temp->size() > 0)
			$$ = new AST::Node(0, SUB_ROUTINE, Temp);
		else
			$$ = NULL;
	}
	;

routine_head
	: label_part const_part type_part var_part routine_part
	{
		// 因为很多部分有nullable
		// 所以把所有非空部分拼成一个列表再一次性构造$$，避免了很多的if-else语句
		
		std::vector<AST::Node*>* Temp = new std::vector<AST::Node*>();
		if ($2 != NULL) Temp->push_back($2);
		if ($3 != NULL) Temp->push_back($3);
		if ($4 != NULL) Temp->push_back($4);
		if ($5 != NULL) 
		{
			for (auto node : *($5))
				Temp->push_back(node);
		}
		if (Temp->size() > 0)
			$$ = new AST::Node(0, ROUTINE_HEAD, Temp);
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
		$$ = new AST::Node(@1.first_line, CONST_PART, $2);
	}
	| {$$ = NULL;}
	;

const_expr_list
	: const_expr_list _ID_ EQUAL const_value SEMI
	{
		$$->push_back(new AST::Node(@3.first_line, EQUAL, 2, new AST::Node(@2.first_line, $2, AST::Attribute::Identifier), $4));
	}
	| _ID_ EQUAL const_value SEMI
	{
		$$ = new std::vector<AST::Node*>();
		$$->push_back(new AST::Node(@2.first_line, EQUAL, 2, new AST::Node(@1.first_line, $1, AST::Attribute::Identifier), $3));
	}
	;

const_value
	: INTEGER
    {
        AST::ValConstant temp;
        temp.Type = AST::ConstantType::Integer;
        temp.iValue = $1;
        $$ = new AST::Node(@1.first_line, temp);
    }
	| REAL
    {
        AST::ValConstant temp;
        temp.Type = AST::ConstantType::Real;
        temp.dValue = $1;
        $$ = new AST::Node(@1.first_line, temp);
    }
	| CHAR
    {
        AST::ValConstant temp;
        temp.Type = AST::ConstantType::Char;
        temp.cValue = $1;
        $$ = new AST::Node(@1.first_line, temp);
    }
	| STRING
	{
		AST::ValConstant temp;
        temp.Type = AST::ConstantType::String;
		// std::cout << $1 << std::endl;
        temp.sValue = $1;
        $$ = new AST::Node(@1.first_line, temp);
	}
	| SYS_CON
	{
		AST::ValConstant temp;
		temp.Type = AST::ConstantType::Boolean;
		// std::cout << $1 << std::endl;
		temp.bValue = (strcmp($1, "true") == 0);
		$$ = new AST::Node(@1.first_line, temp);
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
		$$ = new AST::Node(0, TYPE_PART, 1, $1);
	}
	;

type_definition
	: _ID_ EQUAL type_decl SEMI
	{
		$$ = new AST::Node(@2.first_line, TYPE, 2
					  , new AST::Node(@1.first_line, $1, AST::Attribute::Typename)
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
		$$ = new AST::Node(@1.first_line, $1, AST::Attribute::Typename);
	}
	| _ID_
	{
		$$ = new AST::Node(@1.first_line, $1, AST::Attribute::Typename);
	}
	| _LP_ name_list RP
	{
		$$ = new AST::Node(@1.first_line, ENUM, $2);
	}
	| const_value DOTDOT const_value
	{
		$$ = new AST::Node(@2.first_line, DOTDOT, 2, $1, $3);
	}
	| MINUS const_value DOTDOT const_value
	{
		$$ = new AST::Node(@3.first_line, DOTDOT, 2,
					  new AST::Node(@1.first_line, MINUS, 1, $2),
					  $4);
	}
	| MINUS const_value DOTDOT MINUS const_value
	{
		$$ = new AST::Node(@3.first_line, DOTDOT, 2,
					  new AST::Node(@1.first_line, MINUS, 1, $2),
					  new AST::Node(@1.first_line, MINUS, 1, $5));
	}
	| _ID_ DOTDOT _ID_
	{
		$$ = new AST::Node(@2.first_line, DOTDOT, 2,
					  new AST::Node(@1.first_line, $1, AST::Attribute::Identifier),
					  new AST::Node(@1.first_line, $3, AST::Attribute::Identifier));
	}
	;

array_type_decl
	: ARRAY LB simple_type_decl RB OF type_decl
	{
		$$ = new AST::Node(@1.first_line, ARRAY, 1, $6);
		$$->add($3);
	}
	;

record_type_decl
	: RECORD field_decl_list END
	{
		$$ = new AST::Node(@1.first_line, RECORD, $2);
	}
	;

field_decl_list
	: field_decl_list field_decl 
	{
		$$->push_back($2);
	}
	| field_decl
	{
		$$ = new std::vector<AST::Node*>();
		$$->push_back($1);
	}
	;

field_decl
	: name_list COLON type_decl SEMI
	{
		$$ = new AST::Node(0, FIELD_DECL, 1, $3);
		$$->add($1);
	}
	;

name_list
	: name_list COMMA _ID_
	{
		$$->push_back(new AST::Node(@3.first_line, $3, AST::Attribute::Identifier));
	}
	| _ID_
	{
		// std::cout << "line no: " << @1.first_line << std::endl;
		$$ = new std::vector<AST::Node*>();
		$$->push_back(new AST::Node(@1.first_line, $1, AST::Attribute::Identifier));
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
		$$ = new AST::Node(0, VAR_PART, 1, $1);
	}
	;

var_decl
	: name_list COLON type_decl SEMI
	{
		$$ = new AST::Node(@2.first_line, VAR, 1, $3);
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
		$$ = new std::vector<AST::Node*>();
		$$->push_back($1);
	}
	| procedure_decl
	{
		$$ = new std::vector<AST::Node*>();
		$$->push_back($1);
	}
	| {$$ = NULL;}
	;

function_decl
	: function_head SEMI sub_routine SEMI
	{
		if ($3)
			$$ = new AST::Node(@2.first_line, FUNCTION, 2, $1, $3);
		else
			$$ = new AST::Node(@2.first_line, FUNCTION, 1, $1);
	}
	;
function_head
	: FUNCTION _ID_ parameters COLON simple_type_decl
	{
		if ($3)
		{
			$$ = new AST::Node(@1.first_line, FUNCTION_HEAD, 2, $3, $5);
		}
		else
		{
			$$ = new AST::Node(@1.first_line, FUNCTION_HEAD, 1, $5);
		}
		$$->add(new AST::Node(@2.first_line, $2, AST::Attribute::Identifier));
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
		$$ = new AST::Node(0, PROCEDURE, 2, $1, $3);
	}
	;

procedure_head
	: PROCEDURE _ID_ parameters
	{
		if ($3)
		{
			$$ = new AST::Node(@1.first_line, PROCEDURE_HEAD, 1, $3);
			$$->add(new AST::Node(@2.first_line, $2, AST::Attribute::Identifier));
		}
		else
		{
			$$ = new AST::Node(@2.first_line, $2, AST::Attribute::Identifier);
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
	: _LP_ para_decl_list RP
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
		$$ = new AST::Node(0, PARA_LIST, 1, $1);
	}
	;
para_type_list
	: var_para_list COLON simple_type_decl // var x,y,z : integer，引用传递
	{
		$$ = new AST::Node(0, VAR_PARAM, 1, $3);
		$$->add($1);
	}
	| val_para_list COLON simple_type_decl // x,y,z : integer，形参传递
	{
		$$ = new AST::Node(0, VAL_PARAM, 1, $3);
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
			$$ = new AST::Node(0, ROUTINE_BODY, 1, $1);
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
			$$ = new AST::Node(0, SEMI, 2, $1, $2);
		}
	}
	| {$$ = NULL;}
	;
stmt
	: INTEGER COLON non_label_stmt
	{
		AST::ValConstant temp;
		temp.Type = AST::ConstantType::Integer;
		temp.iValue = $1;
		$$ = new AST::Node(@1.first_line, LABEL_STMT, 2, new AST::Node(@1.first_line, temp), $3);
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
	: _ID_ ASSIGN expression
	{
		$$ = new AST::Node(@2.first_line, ASSIGN, 2, new AST::Node(@1.first_line, $1, AST::Attribute::Identifier), $3);
	}
	| _ID_ LB expression RB ASSIGN expression
	{
		$$ = new AST::Node(@5.first_line, ASSIGN, 2, 
					  new AST::Node(@2.first_line, BRACKET, 2, new AST::Node(@1.first_line, $1, AST::Attribute::Identifier), $3),
					  $6);
	}
	| _ID_ DOT _ID_ ASSIGN expression
	{
		$$ = new AST::Node(@4.first_line, ASSIGN, 2,
					  new AST::Node(@2.first_line, DOT, 2, new AST::Node(@1.first_line, $1, AST::Attribute::Identifier),
					  				   new AST::Node(@3.first_line, $3, AST::Attribute::Identifier))
					  , $5);
	}
	;

proc_stmt
	: _ID_
	{
		$$ = new AST::Node(@1.first_line, CALL_PROC, 1, new AST::Node(@1.first_line, $1, AST::Attribute::Identifier));
	}
	| _ID_ _LP_ args_list RP
	{
		$$ = new AST::Node(@1.first_line, CALL_PROC, 1, new AST::Node(@1.first_line, $1, AST::Attribute::Identifier));
		$$->add($3);
	}
	| SYS_PROC
	{
		$$ = new AST::Node(@1.first_line, SYS_PROC, 1, new AST::Node(@1.first_line, $1, AST::Attribute::Identifier));
	}
	| SYS_PROC _LP_ expression_list RP
	{
		$$ = new AST::Node(@1.first_line, SYS_PROC, 1, new AST::Node(@1.first_line, $1, AST::Attribute::Identifier));
		$$->add($3);
	}
	;

if_stmt
	: IF expression THEN stmt else_clause
	{
		if ($5)
		{
			$$ = new AST::Node(@1.first_line, IF, 3, $2, $4, $5);
		}
		else 
		{
			$$ = new AST::Node(@1.first_line, IF, 2, $2, $4);
		}
	}
	;
else_clause
	: ELSE stmt {$$ = $2;}
	| {$$ = NULL;}
	;
repeat_stmt
	: REPEAT stmt_list UNTIL expression
	{	// $4, $2的顺序是为了和while语句保持一致
		$$ = new AST::Node(@1.first_line, REPEAT, 2, $4, $2);
	}
	;
while_stmt
	: WHILE expression DO stmt
	{
		$$ = new AST::Node(@1.first_line, WHILE, 2, $2, $4);
	}
	;

for_stmt
	: FOR _ID_ ASSIGN expression TO expression DO stmt
	{
		$$ = new AST::Node(@1.first_line, TO, 4, new AST::Node(@2.first_line, $2, AST::Attribute::Identifier),
						$4, $6, $8);
	}
	| FOR _ID_ ASSIGN expression DOWNTO expression DO stmt
	{
		$$ = new AST::Node(@1.first_line, DOWNTO, 4, new AST::Node(@2.first_line, $2, AST::Attribute::Identifier),
						$4, $6, $8);
	}
	;
case_stmt
	: CASE expression OF case_expr_list END
	{
		$$ = new AST::Node(@1.first_line, CASE_STMT, 2, $2, $4);
	}
	;
case_expr_list
	: case_expr_list case_expr 
	{
		$$->add($2);
	}
	| case_expr
	{
		$$ = new AST::Node(0, CASE_LIST, 1, $1);
	}
	;
case_expr
	: const_value COLON stmt SEMI
	{
		$$ = new AST::Node(@1.first_line, CASE, 2, $1, $3);
	}
	| _ID_ COLON stmt SEMI
	{
		$$ = new AST::Node(@1.first_line, CASE, 2
					  , new AST::Node(@1.first_line, $1, AST::Attribute::Identifier)
					  , $3);
	}
	;
goto_stmt
	: GOTO INTEGER
	{
		AST::ValConstant temp;
		temp.Type = AST::ConstantType::Integer;
        temp.iValue = $2;
		$$ = new AST::Node(@1.first_line, GOTO, 1, new AST::Node(@2.first_line, temp));
	}
	;
expression_list
	: expression_list COMMA expression
	{
		$$->push_back($3);
	}
	| expression
	{
		$$ = new std::vector<AST::Node*>();
		$$->push_back($1);
	}
	;
expression
	: expression _GE_ expr
    {
        $$ = new AST::Node(@2.first_line, _GE_, 2, $1, $3);
    }
	| expression _GT_ expr
    {
        $$ = new AST::Node(@2.first_line, _GT_, 2, $1, $3);
    }
	| expression _LE_ expr
    {
        $$ = new AST::Node(@2.first_line, _LE_, 2, $1, $3);
    }
	| expression _LT_ expr
    {
        $$ = new AST::Node(@2.first_line, _LT_, 2, $1, $3);
    }
	| expression EQUAL expr
    {
        $$ = new AST::Node(@2.first_line, EQUAL, 2, $1, $3);
    }
	| expression UNEQUAL expr
    {
        $$ = new AST::Node(@2.first_line, UNEQUAL, 2, $1, $3);
    }
	| expr
    {
        $$ = $1;
    }
	;
expr
	: expr PLUS term
    {
        $$ = new AST::Node(@2.first_line, PLUS, 2, $1, $3);
    }
	| expr MINUS term
    {
        $$ = new AST::Node(@2.first_line, MINUS, 2, $1, $3);
    }
	| expr OR term
	{
		$$ = new AST::Node(@2.first_line, OR, 2, $1, $3);
	}
	| term
    {
        $$ = $1;
    }
	;
term
	: term MUL factor
    {
        $$ = new AST::Node(@2.first_line, MUL, 2, $1, $3);
    }
	| term DIV factor
    {
        $$ = new AST::Node(@2.first_line, DIV, 2, $1, $3);
    }
	| term MOD factor
    {
        $$ = new AST::Node(@2.first_line, MOD, 2, $1, $3);
    }
	| term AND factor
	{
		$$ = new AST::Node(@2.first_line, AND, 2, $1, $3);
	}
	| factor
    	{
		$$ = $1;
    	}
	;
factor
	: _ID_
    	{
       		$$ = new AST::Node(@1.first_line, $1, AST::Attribute::Identifier);
    	}
	| _ID_ _LP_ args_list RP
	{
		$$ = new AST::Node(@1.first_line, CALL_FUNCT, 1
					  , new AST::Node(@1.first_line, $1, AST::Attribute::Identifier));
		$$->add($3);
	}
	| SYS_FUNCT 
	{
		$$ = new AST::Node(@1.first_line, SYS_FUNCT, 1
					  , new AST::Node(@1.first_line, $1, AST::Attribute::Identifier));
	}
	| SYS_FUNCT _LP_ args_list RP
	{
		$$ = new AST::Node(@1.first_line, SYS_FUNCT, 1
					  , new AST::Node(@1.first_line, $1, AST::Attribute::Identifier));
		$$->add($3);
	}
	| const_value
	{
		$$ = $1;
	}
	| _LP_ expression RP
	    {
        	$$ = $2;
    	}
	| NOT factor
	{
		$$ = new AST::Node(@1.first_line, NOT, 1, $2);
	}
	| MINUS factor
	{
		$$ = new AST::Node(@1.first_line, MINUS, 1, $2);
	}
	| _ID_ LB expression RB
	{
		$$ = new AST::Node(@1.first_line, BRACKET, 2
					  , new AST::Node(@1.first_line, $1, AST::Attribute::Identifier)
					  , $3);
	}
	| _ID_ DOT _ID_
	{
		$$ = new AST::Node(@2.first_line, DOT, 2
					  , new AST::Node(@1.first_line, $1, AST::Attribute::Identifier)
					  , new AST::Node(@3.first_line, $3, AST::Attribute::Identifier));
	}
	;
args_list
	: args_list COMMA expression
	{
		$$->push_back($3);
	}
	| expression
	{
		$$ = new std::vector<AST::Node*>();
		$$->push_back($1);
	}
	;
%%
void yyerror(const char* s)
{
	std::cerr << "Error in line " << yylineno << ". " << s << std::endl;
}

int main(int argc, char* argv[])
{
	/* yydebug = 1; // debug时才用 */
	FILE* fp = NULL;
	if (argc > 1)
	{
		inFilename = argv[1];
		/* std::cout << inFilename << std::endl; */
		std::string temp_filename = "./Test/" + inFilename + ".spl";
		fp = fopen(temp_filename.c_str(), "r");
		if (fp)
		{ // 成功打开文件
			yyset_in(fp); // 设置parse对象的指针
		}
		else
		{
			std::string msg = "\nYour current directory is \"";
			msg.append(std::filesystem::current_path());
			msg.append("\"\nFailed to open file \"");
			msg.append(inFilename);
			msg.append("\" !!");
			raiseError(msg)
		}
	}
    yyparse();
	if (fp) fclose(fp);
    return 0;
}
