%{
#include <iostream>
#include "AST.hpp"
#include "yacc.tab.hpp"
#include <sstream>

std::stringstream ss;
extern unsigned int line_number;
%}

%option yylineno

/* 读取字符串的状态 */
%x READING_STRING
/* 注释状态 */
%x COMMENT

Letter  [a-zA-Z]
Digit   [0-9]
Integer (0|[1-9]{Digit}*)
Real    {Integer}.[0-9]+
Identifier  {Letter}({Letter}|{Digit}|_)*


%%

<INITIAL>"//" {
    // 注释
    ss.clear();
    ss.str("");
    BEGIN COMMENT;
}
<COMMENT>"\n" {
    // 注释碰到回车结束
    BEGIN INITIAL;
}
<COMMENT>. ;

"(" {
    yylloc.first_line=line_number;
    return _LP_;
}
")" {
    yylloc.first_line=line_number;
    return RP;}
"[" {
    yylloc.first_line=line_number;
    return LB;}
"]" {
    yylloc.first_line=line_number;
    return RB;}
".." {
    yylloc.first_line=line_number;
    return DOTDOT;
}
"." {
    yylloc.first_line=line_number;
    return DOT;
}
"," {
    yylloc.first_line=line_number;
    return COMMA;}
":=" {
    yylloc.first_line=line_number;
    return ASSIGN;}
":" {
    yylloc.first_line=line_number;
    return COLON;}
"*" {
    yylloc.first_line=line_number;
    return MUL;}
"/" {
    yylloc.first_line=line_number;
    return DIV;}
"<>" {
    yylloc.first_line=line_number;
    return UNEQUAL;}
"NOT" {
    yylloc.first_line=line_number;
    return NOT;}
"+" {
    yylloc.first_line=line_number;
    return PLUS;}
"-" {
    yylloc.first_line=line_number;
    return MINUS;}
">=" {
    yylloc.first_line=line_number;
    return GE;}
">" {
    yylloc.first_line=line_number;
    return GT;}
"<=" {
    yylloc.first_line=line_number;
    return _LE_;}
"<" {
    yylloc.first_line=line_number;
    return _LT_;}
"=" {
    yylloc.first_line=line_number;
    return EQUAL;}
"MOD"|"%" {
    yylloc.first_line=line_number;
    return MOD;}
";" {
    yylloc.first_line=line_number;
    return SEMI;
}


"false"|"maxint"|"true" {
    yylval.sValue=new char[strlen(yytext)];
    yylloc.first_line=line_number;
    strcpy(yylval.sValue,yytext);
    return SYS_CON;
}
"abs"|"chr"|"odd"|"ord"|"pred"|"sqr"|"sqrt"|"succ" {
    yylval.sValue=new char[strlen(yytext)];
    yylloc.first_line=line_number;
    strcpy(yylval.sValue,yytext);
    return SYS_FUNCT;
}
"write"|"writeln"|"read" {
    yylval.sValue=new char[strlen(yytext)];
    yylloc.first_line=line_number;
    strcpy(yylval.sValue,yytext);
    return SYS_PROC;
}
"boolean"|"char"|"integer"|"real"|"string" {
    yylval.sValue=new char[strlen(yytext)];
    yylloc.first_line=line_number;
    strcpy(yylval.sValue,yytext);
    return SYS_TYPE;
}

 /* Keyword List */
"and" {
    yylloc.first_line=line_number;
    return AND;}
"array" {
    yylloc.first_line=line_number;
    return ARRAY;}
"begin" {
    yylloc.first_line=line_number;
    return _BEGIN;}
"case" {
    yylloc.first_line=line_number;
    return CASE;}
"const" {
    yylloc.first_line=line_number;
    return CONST;}
"div" {
    yylloc.first_line=line_number;
    return DIV;}
"do" {
    yylloc.first_line=line_number;
    return DO;}
"downto" {
    yylloc.first_line=line_number;
    return DOWNTO;}
"else" {
    yylloc.first_line=line_number;
    return ELSE;}
"end" {
    yylloc.first_line=line_number;
    return END;}
"for" {
    yylloc.first_line=line_number;
    return FOR;}
"function" {
    yylloc.first_line=line_number;
    return FUNCTION;}
"goto" {
    yylloc.first_line=line_number;
    return GOTO;}
"if" {
    yylloc.first_line=line_number;
    return IF;}
"mod" {
    yylloc.first_line=line_number;
    return MOD;}
"not" {
    yylloc.first_line=line_number;
    return NOT;}
"of" {
    yylloc.first_line=line_number;
    return OF;}
"or" {
    yylloc.first_line=line_number;
    return OR;}
"packed" {
    yylloc.first_line=line_number;
    return PACKED;}
"procedure" {
    yylloc.first_line=line_number;
    return PROCEDURE;
}
"program" {
    yylloc.first_line=line_number;
    return PROGRAM;
}
"record" {
    yylloc.first_line=line_number;
    return RECORD;
}
"repeat" {
    yylloc.first_line=line_number;
    return REPEAT;
}
"then" {
    yylloc.first_line=line_number;
    return THEN;
}
"to" {
    yylloc.first_line=line_number;
    return TO;
}
"type" {
    yylloc.first_line=line_number;
    return TYPE;
}
"until" {
    yylloc.first_line=line_number;
    return UNTIL;
}
"var" {
    yylloc.first_line=line_number;
    return VAR;
}
"while" {
    yylloc.first_line=line_number; 
    return WHILE;
}

"\"" {
    //开始读取字符串
    BEGIN READING_STRING;
    //清空string stream
    ss.clear();
    ss.str("");
}
<READING_STRING>"\"" {
    //结束字符串读取
    BEGIN INITIAL;
    yylval.sValue=new char[ss.str().length()];
    strcpy(yylval.sValue,ss.str().c_str());
    return STRING;
}
<READING_STRING>. {
    ss<<yytext[0];
}
"'"."'" {
    yylval.cValue=yytext[1];
    yylloc.first_line=line_number;
    return CHAR;
}
{Integer}   {
    yylval.iValue=atoi(yytext);
    yylloc.first_line=line_number;
    return INTEGER;
}
{Real}  {
    std::stringstream ss;
    ss<<yytext;
    ss>>yylval.dValue;
    yylloc.first_line=line_number;
    return REAL;
}
{Identifier}    {
    yylval.sValue=new char[strlen(yytext)];
    yylloc.first_line=line_number;
    strcpy(yylval.sValue,yytext);
    return _ID_;
}

"\n" {
    line_number ++;
}
. ;

%%

int yywrap(void)
{
	puts("-----the file is end");
	return 1;//返回1表示读取全部结束。如果要接着读其它文件，可以这里fopen该文件，文件指针赋给yyin，并返回0
}
