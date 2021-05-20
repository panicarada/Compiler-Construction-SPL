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
    std::cout<<"comment: "<<ss.str()<<std::endl;
}
<COMMENT>. {
    // 注释状态忽略一切，为了调试，输出一下注释内容
    ss<<yytext[0];
}

"(" return LP;
")" return RP;
"[" return LB;
"]" return RB;
".." {
    // std::cout<<"Hello DOTDOT"<<std::endl;
    return DOTDOT;
}
"." {
    // std::cout<<"Hello DOT"<<std::endl;
    return DOT;
}
"," return COMMA;
":=" return ASSIGN;
":" return COLON;
"*" return MUL;
"/" return DIV;
"<>" return UNEQUAL;
"NOT" return NOT;
"+" return PLUS;
"-" return MINUS;
">=" return GE;
">" return GT;
"<=" return LE;
"<" return LT;
"=" return EQUAL;
"MOD"|"%" return MOD;
";" {
    // std::cout<<"Hello SEMI"<<std::endl;
    return SEMI;
}


"false"|"maxint"|"true" {
    yylval.sValue=new char[strlen(yytext)];
    strcpy(yylval.sValue,yytext);
    return SYS_CON;
}
"abs"|"chr"|"odd"|"ord"|"pred"|"sqr"|"sqrt"|"succ" {
    yylval.sValue=new char[strlen(yytext)];
    strcpy(yylval.sValue,yytext);
    return SYS_FUNCT;
}
"write"|"writeln" {
    yylval.sValue=new char[strlen(yytext)];
    strcpy(yylval.sValue,yytext);
    return SYS_PROC;
}
"boolean"|"char"|"integer"|"real"|"string" {
    yylval.sValue=new char[strlen(yytext)];
    strcpy(yylval.sValue,yytext);
    return SYS_TYPE;
}
"read" return READ;

 /* Keyword List */
"and" return AND;
"array" return ARRAY;
"begin" return _BEGIN;
"case" return CASE;
"const" return CONST;
"div" return DIV;
"do" return DO;
"downto" return DOWNTO;
"else" return ELSE;
"end" return END;
"for" return FOR;
"function" return FUNCTION;
"goto" return GOTO;
"if" return IF;
"mod" return MOD;
"not" return NOT;
"of" return OF;
"or" return OR;
"packed" return PACKED;
"procedure" return PROCEDURE;
"program" {
    // std::cout<<"Hello PROGRAM"<<std::endl;
    return PROGRAM;
}
"record" return RECORD;
"repeat" return REPEAT;
"then" return THEN;
"to" return TO;
"type" return TYPE;
"until" return UNTIL;
"var" return VAR;
"while" return WHILE;

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
    return CHAR;
}
{Integer}   {
    yylval.iValue=atoi(yytext);
    // std::cout<<"integer number: "<<yylval.iValue<<std::endl;
    return INTEGER;
}
{Real}  {
    std::stringstream ss;
    ss<<yytext;
    ss>>yylval.dValue;
    // std::cout<<"real number: "<<yylval.dValue<<std::endl;
    return REAL;
}
{Identifier}    {
    yylval.sValue=new char[strlen(yytext)];
    yylloc.first_line=line_number;
    strcpy(yylval.sValue,yytext);
    return ID;
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
