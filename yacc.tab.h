/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEGER = 258,
     REAL = 259,
     CHAR = 260,
     STRING = 261,
     SYS_TYPE = 262,
     ID = 263,
     LP = 264,
     RP = 265,
     LB = 266,
     RB = 267,
     DOT = 268,
     COMMA = 269,
     COLON = 270,
     MUL = 271,
     DIV = 272,
     UNEQUAL = 273,
     NOT = 274,
     PLUS = 275,
     MINUS = 276,
     GE = 277,
     GT = 278,
     LE = 279,
     LT = 280,
     EQUAL = 281,
     ASSIGN = 282,
     MOD = 283,
     DOTDOT = 284,
     SEMI = 285,
     READ = 286,
     SYS_PROC = 287,
     SYS_FUNCT = 288,
     SYS_CON = 289,
     AND = 290,
     ARRAY = 291,
     _BEGIN = 292,
     CASE = 293,
     CONST = 294,
     DO = 295,
     DOWNTO = 296,
     ELSE = 297,
     END = 298,
     FOR = 299,
     FUNCTION = 300,
     GOTO = 301,
     IF = 302,
     OF = 303,
     OR = 304,
     PACKED = 305,
     PROCEDURE = 306,
     PROGRAM = 307,
     RECORD = 308,
     REPEAT = 309,
     THEN = 310,
     TO = 311,
     TYPE = 312,
     UNTIL = 313,
     VAR = 314,
     WHILE = 315,
     ROUTINE = 316,
     ROUTINE_BODY = 317,
     ROUTINE_HEAD = 318,
     CONST_PART = 319,
     VAR_PART = 320,
     BRACKET = 321,
     CASE_STMT = 322,
     CASE_LIST = 323,
     TYPE_PART = 324,
     VAL_PARAM = 325,
     VAR_PARAM = 326,
     PARA_LIST = 327,
     FUNCTION_HEAD = 328,
     SUB_ROUTINE = 329,
     PROCEDURE_HEAD = 330,
     PROC = 331,
     LABEL_STMT = 332,
     FUNCT = 333,
     FIELD_DECL = 334,
     ENUM = 335
   };
#endif
/* Tokens.  */
#define INTEGER 258
#define REAL 259
#define CHAR 260
#define STRING 261
#define SYS_TYPE 262
#define ID 263
#define LP 264
#define RP 265
#define LB 266
#define RB 267
#define DOT 268
#define COMMA 269
#define COLON 270
#define MUL 271
#define DIV 272
#define UNEQUAL 273
#define NOT 274
#define PLUS 275
#define MINUS 276
#define GE 277
#define GT 278
#define LE 279
#define LT 280
#define EQUAL 281
#define ASSIGN 282
#define MOD 283
#define DOTDOT 284
#define SEMI 285
#define READ 286
#define SYS_PROC 287
#define SYS_FUNCT 288
#define SYS_CON 289
#define AND 290
#define ARRAY 291
#define _BEGIN 292
#define CASE 293
#define CONST 294
#define DO 295
#define DOWNTO 296
#define ELSE 297
#define END 298
#define FOR 299
#define FUNCTION 300
#define GOTO 301
#define IF 302
#define OF 303
#define OR 304
#define PACKED 305
#define PROCEDURE 306
#define PROGRAM 307
#define RECORD 308
#define REPEAT 309
#define THEN 310
#define TO 311
#define TYPE 312
#define UNTIL 313
#define VAR 314
#define WHILE 315
#define ROUTINE 316
#define ROUTINE_BODY 317
#define ROUTINE_HEAD 318
#define CONST_PART 319
#define VAR_PART 320
#define BRACKET 321
#define CASE_STMT 322
#define CASE_LIST 323
#define TYPE_PART 324
#define VAL_PARAM 325
#define VAR_PARAM 326
#define PARA_LIST 327
#define FUNCTION_HEAD 328
#define SUB_ROUTINE 329
#define PROCEDURE_HEAD 330
#define PROC 331
#define LABEL_STMT 332
#define FUNCT 333
#define FIELD_DECL 334
#define ENUM 335




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 14 "yacc.y"
{
    int iValue; // integer value
    double dValue; // double value
    char cValue; // char value
    char* sValue;
    Node* NodePtr; // Node Pointer
	std::vector<Node*>* NodePtrList; // List
}
/* Line 1529 of yacc.c.  */
#line 218 "yacc.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

