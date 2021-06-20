/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



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
     _ID_ = 263,
     _LP_ = 264,
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
     _GE_ = 277,
     _GT_ = 278,
     _LE_ = 279,
     _LT_ = 280,
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
     CALL_PROC = 331,
     LABEL_STMT = 332,
     CALL_FUNCT = 333,
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
#define _ID_ 263
#define _LP_ 264
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
#define _GE_ 277
#define _GT_ 278
#define _LE_ 279
#define _LT_ 280
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
#define CALL_PROC 331
#define LABEL_STMT 332
#define CALL_FUNCT 333
#define FIELD_DECL 334
#define ENUM 335




/* Copy the first part of user declarations.  */
#line 1 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"

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


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 29 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
{
    int iValue; // integer value
    double dValue; // double value
    char cValue; // char value
    char* sValue;
    AST::Node* NodePtr; // Node Pointer
	std::vector<AST::Node*>* NodePtrList; // List
}
/* Line 193 of yacc.c.  */
#line 291 "/Applications/zju/编译原理/final_proj/Code/source/yacc.tab.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 316 "/Applications/zju/编译原理/final_proj/Code/source/yacc.tab.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   355

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  125
/* YYNRULES -- Number of states.  */
#define YYNSTATES  259

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   335

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    11,    14,    17,    23,    24,    27,
      28,    34,    39,    41,    43,    45,    47,    49,    52,    53,
      56,    58,    63,    65,    67,    69,    71,    73,    77,    81,
      86,    92,    96,   103,   107,   110,   112,   117,   121,   123,
     126,   127,   130,   132,   137,   140,   143,   145,   147,   148,
     153,   159,   164,   168,   172,   173,   177,   179,   183,   187,
     190,   192,   194,   198,   202,   203,   207,   209,   211,   213,
     215,   217,   219,   221,   223,   225,   227,   231,   238,   244,
     246,   251,   253,   258,   264,   267,   268,   273,   278,   287,
     296,   302,   305,   307,   312,   317,   320,   324,   326,   330,
     334,   338,   342,   346,   350,   352,   356,   360,   364,   366,
     370,   374,   378,   382,   384,   386,   391,   393,   398,   400,
     404,   407,   410,   415,   419,   423
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      82,     0,    -1,    83,    84,    13,    -1,    52,     8,    30,
      -1,    86,   114,    -1,    86,   114,    -1,    87,    88,    91,
     101,   104,    -1,    -1,    39,    89,    -1,    -1,    89,     8,
      26,    90,    30,    -1,     8,    26,    90,    30,    -1,     3,
      -1,     4,    -1,     5,    -1,     6,    -1,    34,    -1,    57,
      92,    -1,    -1,    92,    93,    -1,    93,    -1,     8,    26,
      94,    30,    -1,    95,    -1,    96,    -1,    97,    -1,     7,
      -1,     8,    -1,     9,   100,    10,    -1,    90,    29,    90,
      -1,    21,    90,    29,    90,    -1,    21,    90,    29,    21,
      90,    -1,     8,    29,     8,    -1,    36,    11,    95,    12,
      48,    94,    -1,    53,    98,    43,    -1,    98,    99,    -1,
      99,    -1,   100,    15,    94,    30,    -1,   100,    14,     8,
      -1,     8,    -1,    59,   102,    -1,    -1,   102,   103,    -1,
     103,    -1,   100,    15,    94,    30,    -1,   104,   105,    -1,
     104,   107,    -1,   105,    -1,   107,    -1,    -1,   106,    30,
      85,    30,    -1,    45,     8,   109,    15,    95,    -1,   108,
      30,    85,    30,    -1,    51,     8,   109,    -1,     9,   110,
      10,    -1,    -1,   110,    30,   111,    -1,   111,    -1,   112,
      15,    95,    -1,   113,    15,    95,    -1,    59,   100,    -1,
     100,    -1,   115,    -1,    37,   116,    43,    -1,   116,   117,
      30,    -1,    -1,     3,    15,   118,    -1,   118,    -1,   119,
      -1,   120,    -1,   115,    -1,   121,    -1,   123,    -1,   124,
      -1,   125,    -1,   126,    -1,   129,    -1,     8,    27,   131,
      -1,     8,    11,   131,    12,    27,   131,    -1,     8,    13,
       8,    27,   131,    -1,     8,    -1,     8,     9,   135,    10,
      -1,    32,    -1,    32,     9,   130,    10,    -1,    47,   131,
      55,   117,   122,    -1,    42,   117,    -1,    -1,    54,   116,
      58,   131,    -1,    60,   131,    40,   117,    -1,    44,     8,
      27,   131,    56,   131,    40,   117,    -1,    44,     8,    27,
     131,    41,   131,    40,   117,    -1,    38,   131,    48,   127,
      43,    -1,   127,   128,    -1,   128,    -1,    90,    15,   117,
      30,    -1,     8,    15,   117,    30,    -1,    46,     3,    -1,
     130,    14,   131,    -1,   131,    -1,   131,    22,   132,    -1,
     131,    23,   132,    -1,   131,    24,   132,    -1,   131,    25,
     132,    -1,   131,    26,   132,    -1,   131,    18,   132,    -1,
     132,    -1,   132,    20,   133,    -1,   132,    21,   133,    -1,
     132,    49,   133,    -1,   133,    -1,   133,    16,   134,    -1,
     133,    17,   134,    -1,   133,    28,   134,    -1,   133,    35,
     134,    -1,   134,    -1,     8,    -1,     8,     9,   135,    10,
      -1,    33,    -1,    33,     9,   135,    10,    -1,    90,    -1,
       9,   131,    10,    -1,    19,   134,    -1,    21,   134,    -1,
       8,    11,   131,    12,    -1,     8,    13,     8,    -1,   135,
      14,   131,    -1,   131,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    80,    80,    89,    97,   110,   126,   147,   152,   156,
     160,   164,   172,   179,   186,   193,   201,   212,   216,   220,
     224,   231,   240,   244,   248,   255,   259,   263,   267,   271,
     277,   283,   292,   300,   307,   311,   319,   327,   331,   340,
     344,   348,   352,   359,   367,   371,   375,   380,   385,   389,
     398,   420,   427,   449,   453,   456,   460,   466,   471,   478,
     484,   491,   504,   510,   521,   524,   531,   537,   538,   539,
     540,   541,   542,   543,   544,   545,   549,   553,   559,   569,
     573,   578,   582,   590,   603,   604,   607,   613,   620,   625,
     632,   638,   642,   648,   652,   660,   669,   673,   680,   684,
     688,   692,   696,   700,   704,   710,   714,   718,   722,   728,
     732,   736,   740,   744,   750,   754,   760,   765,   771,   775,
     779,   783,   787,   793,   801,   805
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "REAL", "CHAR", "STRING",
  "SYS_TYPE", "_ID_", "_LP_", "RP", "LB", "RB", "DOT", "COMMA", "COLON",
  "MUL", "DIV", "UNEQUAL", "NOT", "PLUS", "MINUS", "_GE_", "_GT_", "_LE_",
  "_LT_", "EQUAL", "ASSIGN", "MOD", "DOTDOT", "SEMI", "READ", "SYS_PROC",
  "SYS_FUNCT", "SYS_CON", "AND", "ARRAY", "_BEGIN", "CASE", "CONST", "DO",
  "DOWNTO", "ELSE", "END", "FOR", "FUNCTION", "GOTO", "IF", "OF", "OR",
  "PACKED", "PROCEDURE", "PROGRAM", "RECORD", "REPEAT", "THEN", "TO",
  "TYPE", "UNTIL", "VAR", "WHILE", "ROUTINE", "ROUTINE_BODY",
  "ROUTINE_HEAD", "CONST_PART", "VAR_PART", "BRACKET", "CASE_STMT",
  "CASE_LIST", "TYPE_PART", "VAL_PARAM", "VAR_PARAM", "PARA_LIST",
  "FUNCTION_HEAD", "SUB_ROUTINE", "PROCEDURE_HEAD", "CALL_PROC",
  "LABEL_STMT", "CALL_FUNCT", "FIELD_DECL", "ENUM", "$accept", "program",
  "program_head", "routine", "sub_routine", "routine_head", "label_part",
  "const_part", "const_expr_list", "const_value", "type_part",
  "type_decl_list", "type_definition", "type_decl", "simple_type_decl",
  "array_type_decl", "record_type_decl", "field_decl_list", "field_decl",
  "name_list", "var_part", "var_decl_list", "var_decl", "routine_part",
  "function_decl", "function_head", "procedure_decl", "procedure_head",
  "parameters", "para_decl_list", "para_type_list", "var_para_list",
  "val_para_list", "routine_body", "compound_stmt", "stmt_list", "stmt",
  "non_label_stmt", "assign_stmt", "proc_stmt", "if_stmt", "else_clause",
  "repeat_stmt", "while_stmt", "for_stmt", "case_stmt", "case_expr_list",
  "case_expr", "goto_stmt", "expression_list", "expression", "expr",
  "term", "factor", "args_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    83,    84,    85,    86,    87,    88,    88,
      89,    89,    90,    90,    90,    90,    90,    91,    91,    92,
      92,    93,    94,    94,    94,    95,    95,    95,    95,    95,
      95,    95,    96,    97,    98,    98,    99,   100,   100,   101,
     101,   102,   102,   103,   104,   104,   104,   104,   104,   105,
     106,   107,   108,   109,   109,   110,   110,   111,   111,   112,
     113,   114,   115,   116,   116,   117,   117,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   119,   119,   119,   120,
     120,   120,   120,   121,   122,   122,   123,   124,   125,   125,
     126,   127,   127,   128,   128,   129,   130,   130,   131,   131,
     131,   131,   131,   131,   131,   132,   132,   132,   132,   133,
     133,   133,   133,   133,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   135,   135
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     2,     2,     5,     0,     2,     0,
       5,     4,     1,     1,     1,     1,     1,     2,     0,     2,
       1,     4,     1,     1,     1,     1,     1,     3,     3,     4,
       5,     3,     6,     3,     2,     1,     4,     3,     1,     2,
       0,     2,     1,     4,     2,     2,     1,     1,     0,     4,
       5,     4,     3,     3,     0,     3,     1,     3,     3,     2,
       1,     1,     3,     3,     0,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     6,     5,     1,
       4,     1,     4,     5,     2,     0,     4,     4,     8,     8,
       5,     2,     1,     4,     4,     2,     3,     1,     3,     3,
       3,     3,     3,     3,     1,     3,     3,     3,     1,     3,
       3,     3,     3,     1,     1,     4,     1,     4,     1,     3,
       2,     2,     4,     3,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     7,     0,     1,     0,     0,     9,     3,
       2,    64,     4,    61,     0,    18,     0,     0,     8,     0,
      40,     0,    79,    81,     0,    62,     0,     0,     0,    64,
       0,    69,     0,    66,    67,    68,    70,    71,    72,    73,
      74,    75,     0,     0,     0,    17,    20,     0,    48,     0,
       0,     0,     0,     0,     0,    12,    13,    14,    15,   114,
       0,     0,     0,   116,    16,   118,     0,   104,   108,   113,
       0,    95,     0,     0,     0,    63,     0,     0,     0,    19,
      38,     0,    39,    42,     0,     0,     6,    46,     0,    47,
       0,    65,   125,     0,     0,     0,    76,     0,    97,     0,
       0,     0,     0,   120,   121,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    11,     0,    25,    26,     0,     0,
       0,     0,     0,     0,    22,    23,    24,     0,     0,    41,
      54,    54,    44,    45,     7,     7,    80,     0,     0,     0,
      82,     0,     0,     0,   123,   119,     0,   103,    98,    99,
     100,   101,   102,     0,     0,     0,    92,   105,   106,   107,
     109,   110,   111,   112,     0,    85,    86,    87,    10,     0,
       0,     0,     0,     0,    35,     0,     0,    21,    37,     0,
       0,     0,    52,     0,     0,     0,   124,     0,    78,    96,
     115,   122,   117,     0,     0,    90,    91,     0,     0,     0,
      83,    31,    27,     0,     0,    33,    34,     0,    28,    43,
       0,    60,     0,    56,     0,     0,     0,    49,     5,    51,
      77,     0,     0,     0,     0,    84,     0,    29,     0,     0,
      59,    53,     0,     0,     0,    50,    94,    93,     0,     0,
      30,     0,    36,    55,    57,    58,    89,    88,    32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,   193,   194,     8,    15,    18,    65,
      20,    45,    46,   133,   134,   135,   136,   183,   184,    81,
      48,    82,    83,    86,    87,    88,    89,    90,   191,   222,
     223,   224,   225,    12,    31,    16,    32,    33,    34,    35,
      36,   210,    37,    38,    39,    40,   165,   166,    41,    97,
      92,    67,    68,    69,    93
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -178
static const yytype_int16 yypact[] =
{
     -48,     6,    22,  -178,    -1,  -178,    29,    10,    14,  -178,
    -178,  -178,  -178,  -178,    56,    12,     8,    45,    72,    74,
      31,    77,   118,    89,   232,  -178,    92,   117,   232,  -178,
     232,  -178,    95,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,    80,    96,   106,    74,  -178,   127,   -28,   153,
     232,   232,   129,   232,   232,  -178,  -178,  -178,  -178,    48,
     232,   232,   232,   137,  -178,  -178,   256,    57,   176,  -178,
     122,  -178,   203,   104,   237,  -178,   133,    80,   211,  -178,
    -178,   145,   127,  -178,   160,   161,   -28,  -178,   144,  -178,
     147,  -178,   329,    24,   311,   130,   329,    34,   329,   232,
     232,   170,   296,  -178,  -178,   232,   232,   232,   232,   232,
     232,   232,   105,   232,   232,   232,   232,   232,   232,   232,
     232,   135,   232,   135,  -178,   150,  -178,   167,   127,    80,
     187,   127,   174,   175,  -178,  -178,  -178,   198,   211,  -178,
     199,   199,  -178,  -178,  -178,  -178,  -178,   232,   183,   232,
    -178,   232,    46,   320,  -178,  -178,    81,    57,    57,    57,
      57,    57,    57,   197,   207,   113,  -178,   176,   176,   176,
    -178,  -178,  -178,  -178,     2,   181,   329,  -178,  -178,   216,
      83,   202,   264,     7,  -178,   151,    80,  -178,  -178,   200,
       4,   218,  -178,   204,    10,   209,   329,   232,   329,   329,
    -178,  -178,  -178,   135,   135,  -178,  -178,   232,   232,   135,
    -178,  -178,  -178,   149,   230,  -178,  -178,   211,  -178,  -178,
     127,   229,    11,  -178,   231,   233,   264,  -178,  -178,  -178,
     329,   214,   219,   265,   277,  -178,    80,  -178,   206,   220,
     229,  -178,     4,   264,   264,  -178,  -178,  -178,   135,   135,
    -178,   211,  -178,  -178,  -178,  -178,  -178,  -178,  -178
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -178,  -178,  -178,  -178,   107,   253,  -178,  -178,  -178,   -42,
    -178,  -178,   212,  -136,  -177,  -178,  -178,  -178,    93,  -118,
    -178,  -178,   193,  -178,   208,  -178,   210,  -178,   143,  -178,
      44,  -178,  -178,    98,    -6,   268,  -115,   244,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,   148,  -178,  -178,
     -21,   201,   -10,   -43,   -68
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      76,    13,   189,    66,     1,   214,   175,    72,   177,    74,
     180,    21,    80,   185,     4,    80,    22,    84,   103,   104,
     106,   241,     5,    85,   107,   108,   109,   110,   111,     9,
      94,   152,    96,    98,   146,   125,   132,   156,   147,   102,
      23,   242,    10,   207,   150,    11,    24,    11,   151,   245,
     215,    25,    26,    14,    27,    28,   200,    99,   208,   100,
     147,   101,    29,   220,    17,   185,   254,   255,    30,    19,
     164,    42,   221,   170,   171,   172,   173,   113,   114,   153,
      43,   239,    44,    55,    56,    57,    58,   181,   231,   232,
      47,   202,    49,   212,   235,   147,   132,   137,    54,   174,
      70,   176,   240,   167,   168,   169,   115,    21,    55,    56,
      57,    58,    22,   163,    64,   258,    55,    56,    57,    58,
      71,   163,    77,   164,   221,    75,   196,    50,   198,    51,
     199,    52,    78,   256,   257,    80,    23,    95,    21,    64,
     132,    11,    24,    22,   218,    53,   105,    64,    26,   120,
      27,    28,    55,    56,    57,    58,   205,   149,    29,   137,
     138,    22,   122,   124,    30,   137,   217,    23,   140,   141,
     236,   237,    11,    24,   144,   132,   230,   145,   154,    26,
     178,    27,    28,    64,   132,    23,   233,   234,    13,    29,
      11,    24,   116,   117,   250,    30,   179,    26,   182,    27,
      28,   132,   132,   186,   118,   187,   188,    29,   190,   132,
     197,   119,   203,    30,    55,    56,    57,    58,   126,   127,
     128,   106,   204,   209,   211,   107,   108,   109,   110,   111,
     219,   213,   129,   226,   227,    55,    56,    57,    58,   229,
      59,    60,   238,   137,   246,    64,   243,   130,   244,   247,
     252,    61,   195,    62,   251,   106,     7,    79,   121,   107,
     108,   109,   110,   111,   131,    63,    64,    55,    56,    57,
      58,   126,   127,   128,   106,   139,   216,   123,   107,   108,
     109,   110,   111,   106,   192,   129,   253,   107,   108,   109,
     110,   111,   228,    91,   142,   106,   143,    73,    64,   107,
     108,   109,   110,   111,   112,   248,   155,   157,   158,   159,
     160,   161,   162,   206,   106,     0,     0,   249,   107,   108,
     109,   110,   111,   148,     0,     0,     0,     0,     0,   106,
       0,     0,   201,   107,   108,   109,   110,   111,   106,     0,
       0,     0,   107,   108,   109,   110,   111,   106,     0,     0,
       0,   107,   108,   109,   110,   111
};

static const yytype_int16 yycheck[] =
{
      42,     7,   138,    24,    52,   182,   121,    28,   123,    30,
     128,     3,     8,   131,     8,     8,     8,    45,    61,    62,
      18,    10,     0,    51,    22,    23,    24,    25,    26,    30,
      51,    99,    53,    54,    10,    77,    78,   105,    14,    60,
      32,    30,    13,    41,    10,    37,    38,    37,    14,   226,
      43,    43,    44,    39,    46,    47,    10,     9,    56,    11,
      14,    13,    54,    59,     8,   183,   243,   244,    60,    57,
     112,    26,   190,   116,   117,   118,   119,    20,    21,   100,
       8,   217,     8,     3,     4,     5,     6,   129,   203,   204,
      59,    10,    15,    10,   209,    14,   138,    14,     9,   120,
       8,   122,   220,   113,   114,   115,    49,     3,     3,     4,
       5,     6,     8,     8,    34,   251,     3,     4,     5,     6,
       3,     8,    26,   165,   242,    30,   147,     9,   149,    11,
     151,    13,    26,   248,   249,     8,    32,     8,     3,    34,
     182,    37,    38,     8,   186,    27,     9,    34,    44,    27,
      46,    47,     3,     4,     5,     6,    43,    27,    54,    14,
      15,     8,    58,    30,    60,    14,    15,    32,     8,     8,
      21,   213,    37,    38,    30,   217,   197,    30,     8,    44,
      30,    46,    47,    34,   226,    32,   207,   208,   194,    54,
      37,    38,    16,    17,   236,    60,    29,    44,    11,    46,
      47,   243,   244,    29,    28,    30,     8,    54,     9,   251,
      27,    35,    15,    60,     3,     4,     5,     6,     7,     8,
       9,    18,    15,    42,     8,    22,    23,    24,    25,    26,
      30,    29,    21,    15,    30,     3,     4,     5,     6,    30,
       8,     9,    12,    14,    30,    34,    15,    36,    15,    30,
      30,    19,   145,    21,    48,    18,     3,    45,    55,    22,
      23,    24,    25,    26,    53,    33,    34,     3,     4,     5,
       6,     7,     8,     9,    18,    82,   183,    40,    22,    23,
      24,    25,    26,    18,   141,    21,   242,    22,    23,    24,
      25,    26,   194,    49,    86,    18,    86,    29,    34,    22,
      23,    24,    25,    26,    48,    40,    10,   106,   107,   108,
     109,   110,   111,   165,    18,    -1,    -1,    40,    22,    23,
      24,    25,    26,    12,    -1,    -1,    -1,    -1,    -1,    18,
      -1,    -1,    12,    22,    23,    24,    25,    26,    18,    -1,
      -1,    -1,    22,    23,    24,    25,    26,    18,    -1,    -1,
      -1,    22,    23,    24,    25,    26
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    52,    82,    83,     8,     0,    84,    86,    87,    30,
      13,    37,   114,   115,    39,    88,   116,     8,    89,    57,
      91,     3,     8,    32,    38,    43,    44,    46,    47,    54,
      60,   115,   117,   118,   119,   120,   121,   123,   124,   125,
     126,   129,    26,     8,     8,    92,    93,    59,   101,    15,
       9,    11,    13,    27,     9,     3,     4,     5,     6,     8,
       9,    19,    21,    33,    34,    90,   131,   132,   133,   134,
       8,     3,   131,   116,   131,    30,    90,    26,    26,    93,
       8,   100,   102,   103,    45,    51,   104,   105,   106,   107,
     108,   118,   131,   135,   131,     8,   131,   130,   131,     9,
      11,    13,   131,   134,   134,     9,    18,    22,    23,    24,
      25,    26,    48,    20,    21,    49,    16,    17,    28,    35,
      27,    55,    58,    40,    30,    90,     7,     8,     9,    21,
      36,    53,    90,    94,    95,    96,    97,    14,    15,   103,
       8,     8,   105,   107,    30,    30,    10,    14,    12,    27,
      10,    14,   135,   131,     8,    10,   135,   132,   132,   132,
     132,   132,   132,     8,    90,   127,   128,   133,   133,   133,
     134,   134,   134,   134,   131,   117,   131,   117,    30,    29,
     100,    90,    11,    98,    99,   100,    29,    30,     8,    94,
       9,   109,   109,    85,    86,    85,   131,    27,   131,   131,
      10,    12,    10,    15,    15,    43,   128,    41,    56,    42,
     122,     8,    10,    29,    95,    43,    99,    15,    90,    30,
      59,   100,   110,   111,   112,   113,    15,    30,   114,    30,
     131,   117,   117,   131,   131,   117,    21,    90,    12,    94,
     100,    10,    30,    15,    15,    95,    30,    30,    40,    40,
      90,    48,    30,   111,    95,    95,   117,   117,    94
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 81 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		std::string Program = (yyvsp[(1) - (3)].sValue);
		ipt = new Interpreter();
		ipt->execute((yyvsp[(2) - (3)].NodePtr), inFilename, Program);
		exit(0);
	;}
    break;

  case 3:
#line 90 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.sValue) = new char[strlen((yyvsp[(2) - (3)].sValue))];
		strcpy((yyval.sValue), (yyvsp[(2) - (3)].sValue));
	;}
    break;

  case 4:
#line 98 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		// 因为两个都nullable
		// 所以把所有非空部分拼成一个列表再一次性构造$$，避免了很多的if-else语句
		std::vector<AST::Node*>* Temp = new std::vector<AST::Node*>();
		if ((yyvsp[(1) - (2)].NodePtr) != NULL) Temp->push_back((yyvsp[(1) - (2)].NodePtr));
		if ((yyvsp[(2) - (2)].NodePtr) != NULL) Temp->push_back((yyvsp[(2) - (2)].NodePtr));
		if (Temp->size() > 0) (yyval.NodePtr) = new AST::Node(0, ROUTINE, Temp);
		else (yyval.NodePtr) = nullptr;
	;}
    break;

  case 5:
#line 111 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		// 因为两个都nullable
		// 所以把所有非空部分拼成一个列表再一次性构造$$，避免了很多的if-else语句
		
		std::vector<AST::Node*>* Temp = new std::vector<AST::Node*>();
		if ((yyvsp[(1) - (2)].NodePtr)) Temp->push_back((yyvsp[(1) - (2)].NodePtr));
		if ((yyvsp[(2) - (2)].NodePtr)) Temp->push_back((yyvsp[(2) - (2)].NodePtr));
		if (Temp->size() > 0)
			(yyval.NodePtr) = new AST::Node(0, SUB_ROUTINE, Temp);
		else
			(yyval.NodePtr) = NULL;
	;}
    break;

  case 6:
#line 127 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		// 因为很多部分有nullable
		// 所以把所有非空部分拼成一个列表再一次性构造$$，避免了很多的if-else语句
		
		std::vector<AST::Node*>* Temp = new std::vector<AST::Node*>();
		if ((yyvsp[(2) - (5)].NodePtr) != NULL) Temp->push_back((yyvsp[(2) - (5)].NodePtr));
		if ((yyvsp[(3) - (5)].NodePtr) != NULL) Temp->push_back((yyvsp[(3) - (5)].NodePtr));
		if ((yyvsp[(4) - (5)].NodePtr) != NULL) Temp->push_back((yyvsp[(4) - (5)].NodePtr));
		if ((yyvsp[(5) - (5)].NodePtrList) != NULL) 
		{
			for (auto node : *((yyvsp[(5) - (5)].NodePtrList)))
				Temp->push_back(node);
		}
		if (Temp->size() > 0)
			(yyval.NodePtr) = new AST::Node(0, ROUTINE_HEAD, Temp);
		else
			(yyval.NodePtr) = NULL;
	;}
    break;

  case 8:
#line 153 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (2)]).first_line, CONST_PART, (yyvsp[(2) - (2)].NodePtrList));
	;}
    break;

  case 9:
#line 156 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {(yyval.NodePtr) = NULL;;}
    break;

  case 10:
#line 161 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtrList)->push_back(new AST::Node((yylsp[(3) - (5)]).first_line, EQUAL, 2, new AST::Node((yylsp[(2) - (5)]).first_line, (yyvsp[(2) - (5)].sValue), AST::Attribute::Identifier), (yyvsp[(4) - (5)].NodePtr)));
	;}
    break;

  case 11:
#line 165 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtrList) = new std::vector<AST::Node*>();
		(yyval.NodePtrList)->push_back(new AST::Node((yylsp[(2) - (4)]).first_line, EQUAL, 2, new AST::Node((yylsp[(1) - (4)]).first_line, (yyvsp[(1) - (4)].sValue), AST::Attribute::Identifier), (yyvsp[(3) - (4)].NodePtr)));
	;}
    break;

  case 12:
#line 173 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
        AST::ValConstant temp;
        temp.Type = AST::ConstantType::Integer;
        temp.iValue = (yyvsp[(1) - (1)].iValue);
        (yyval.NodePtr) = new AST::Node((yylsp[(1) - (1)]).first_line, temp);
    ;}
    break;

  case 13:
#line 180 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
        AST::ValConstant temp;
        temp.Type = AST::ConstantType::Real;
        temp.dValue = (yyvsp[(1) - (1)].dValue);
        (yyval.NodePtr) = new AST::Node((yylsp[(1) - (1)]).first_line, temp);
    ;}
    break;

  case 14:
#line 187 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
        AST::ValConstant temp;
        temp.Type = AST::ConstantType::Char;
        temp.cValue = (yyvsp[(1) - (1)].cValue);
        (yyval.NodePtr) = new AST::Node((yylsp[(1) - (1)]).first_line, temp);
    ;}
    break;

  case 15:
#line 194 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		AST::ValConstant temp;
        temp.Type = AST::ConstantType::String;
		// std::cout << $1 << std::endl;
        temp.sValue = (yyvsp[(1) - (1)].sValue);
        (yyval.NodePtr) = new AST::Node((yylsp[(1) - (1)]).first_line, temp);
	;}
    break;

  case 16:
#line 202 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		AST::ValConstant temp;
		temp.Type = AST::ConstantType::Boolean;
		// std::cout << $1 << std::endl;
		temp.bValue = (strcmp((yyvsp[(1) - (1)].sValue), "true") == 0);
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (1)]).first_line, temp);
	;}
    break;

  case 17:
#line 213 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = (yyvsp[(2) - (2)].NodePtr);
	;}
    break;

  case 18:
#line 216 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {(yyval.NodePtr) = NULL;;}
    break;

  case 19:
#line 221 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr)->add((yyvsp[(2) - (2)].NodePtr));
	;}
    break;

  case 20:
#line 225 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node(0, TYPE_PART, 1, (yyvsp[(1) - (1)].NodePtr));
	;}
    break;

  case 21:
#line 232 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(2) - (4)]).first_line, TYPE, 2
					  , new AST::Node((yylsp[(1) - (4)]).first_line, (yyvsp[(1) - (4)].sValue), AST::Attribute::Typename)
					  , (yyvsp[(3) - (4)].NodePtr));
	;}
    break;

  case 22:
#line 241 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);
	;}
    break;

  case 23:
#line 245 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);
	;}
    break;

  case 24:
#line 249 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);
	;}
    break;

  case 25:
#line 256 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (1)]).first_line, (yyvsp[(1) - (1)].sValue), AST::Attribute::Typename);
	;}
    break;

  case 26:
#line 260 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (1)]).first_line, (yyvsp[(1) - (1)].sValue), AST::Attribute::Typename);
	;}
    break;

  case 27:
#line 264 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (3)]).first_line, ENUM, (yyvsp[(2) - (3)].NodePtrList));
	;}
    break;

  case 28:
#line 268 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(2) - (3)]).first_line, DOTDOT, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
	;}
    break;

  case 29:
#line 272 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(3) - (4)]).first_line, DOTDOT, 2,
					  new AST::Node((yylsp[(1) - (4)]).first_line, MINUS, 1, (yyvsp[(2) - (4)].NodePtr)),
					  (yyvsp[(4) - (4)].NodePtr));
	;}
    break;

  case 30:
#line 278 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(3) - (5)]).first_line, DOTDOT, 2,
					  new AST::Node((yylsp[(1) - (5)]).first_line, MINUS, 1, (yyvsp[(2) - (5)].NodePtr)),
					  new AST::Node((yylsp[(1) - (5)]).first_line, MINUS, 1, (yyvsp[(5) - (5)].NodePtr)));
	;}
    break;

  case 31:
#line 284 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(2) - (3)]).first_line, DOTDOT, 2,
					  new AST::Node((yylsp[(1) - (3)]).first_line, (yyvsp[(1) - (3)].sValue), AST::Attribute::Identifier),
					  new AST::Node((yylsp[(1) - (3)]).first_line, (yyvsp[(3) - (3)].sValue), AST::Attribute::Identifier));
	;}
    break;

  case 32:
#line 293 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (6)]).first_line, ARRAY, 1, (yyvsp[(6) - (6)].NodePtr));
		(yyval.NodePtr)->add((yyvsp[(3) - (6)].NodePtr));
	;}
    break;

  case 33:
#line 301 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (3)]).first_line, RECORD, (yyvsp[(2) - (3)].NodePtrList));
	;}
    break;

  case 34:
#line 308 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtrList)->push_back((yyvsp[(2) - (2)].NodePtr));
	;}
    break;

  case 35:
#line 312 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtrList) = new std::vector<AST::Node*>();
		(yyval.NodePtrList)->push_back((yyvsp[(1) - (1)].NodePtr));
	;}
    break;

  case 36:
#line 320 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node(0, FIELD_DECL, 1, (yyvsp[(3) - (4)].NodePtr));
		(yyval.NodePtr)->add((yyvsp[(1) - (4)].NodePtrList));
	;}
    break;

  case 37:
#line 328 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtrList)->push_back(new AST::Node((yylsp[(3) - (3)]).first_line, (yyvsp[(3) - (3)].sValue), AST::Attribute::Identifier));
	;}
    break;

  case 38:
#line 332 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		// std::cout << "line no: " << @1.first_line << std::endl;
		(yyval.NodePtrList) = new std::vector<AST::Node*>();
		(yyval.NodePtrList)->push_back(new AST::Node((yylsp[(1) - (1)]).first_line, (yyvsp[(1) - (1)].sValue), AST::Attribute::Identifier));
	;}
    break;

  case 39:
#line 341 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = (yyvsp[(2) - (2)].NodePtr);
	;}
    break;

  case 40:
#line 344 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {(yyval.NodePtr) = NULL;;}
    break;

  case 41:
#line 349 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr)->add((yyvsp[(2) - (2)].NodePtr));
	;}
    break;

  case 42:
#line 353 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node(0, VAR_PART, 1, (yyvsp[(1) - (1)].NodePtr));
	;}
    break;

  case 43:
#line 360 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(2) - (4)]).first_line, VAR, 1, (yyvsp[(3) - (4)].NodePtr));
		(yyval.NodePtr)->add((yyvsp[(1) - (4)].NodePtrList));
	;}
    break;

  case 44:
#line 368 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtrList)->push_back((yyvsp[(2) - (2)].NodePtr));
	;}
    break;

  case 45:
#line 372 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtrList)->push_back((yyvsp[(2) - (2)].NodePtr));
	;}
    break;

  case 46:
#line 376 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtrList) = new std::vector<AST::Node*>();
		(yyval.NodePtrList)->push_back((yyvsp[(1) - (1)].NodePtr));
	;}
    break;

  case 47:
#line 381 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtrList) = new std::vector<AST::Node*>();
		(yyval.NodePtrList)->push_back((yyvsp[(1) - (1)].NodePtr));
	;}
    break;

  case 48:
#line 385 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {(yyval.NodePtrList) = NULL;;}
    break;

  case 49:
#line 390 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		if ((yyvsp[(3) - (4)].NodePtr))
			(yyval.NodePtr) = new AST::Node((yylsp[(2) - (4)]).first_line, FUNCTION, 2, (yyvsp[(1) - (4)].NodePtr), (yyvsp[(3) - (4)].NodePtr));
		else
			(yyval.NodePtr) = new AST::Node((yylsp[(2) - (4)]).first_line, FUNCTION, 1, (yyvsp[(1) - (4)].NodePtr));
	;}
    break;

  case 50:
#line 399 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		if ((yyvsp[(3) - (5)].NodePtr))
		{
			(yyval.NodePtr) = new AST::Node((yylsp[(1) - (5)]).first_line, FUNCTION_HEAD, 2, (yyvsp[(3) - (5)].NodePtr), (yyvsp[(5) - (5)].NodePtr));
		}
		else
		{
			(yyval.NodePtr) = new AST::Node((yylsp[(1) - (5)]).first_line, FUNCTION_HEAD, 1, (yyvsp[(5) - (5)].NodePtr));
		}
		(yyval.NodePtr)->add(new AST::Node((yylsp[(2) - (5)]).first_line, (yyvsp[(2) - (5)].sValue), AST::Attribute::Identifier));
		/*
			Hacking Trick: 最后一个孩子是类型名称，
			在语法树中，不希望类型和变量为sibling，但是父节点Operation无法记录类型名称，
			所以在数组中保留类型名称，在构造语法树时父节点可以访问，
			但是在数目上假装其不存在，这样按for循环绘制就不会绘制出来
		*/
		(yyval.NodePtr)->m_Operation.NumOperands -= 1;
	;}
    break;

  case 51:
#line 421 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node(0, PROCEDURE, 2, (yyvsp[(1) - (4)].NodePtr), (yyvsp[(3) - (4)].NodePtr));
	;}
    break;

  case 52:
#line 428 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		if ((yyvsp[(3) - (3)].NodePtr))
		{
			(yyval.NodePtr) = new AST::Node((yylsp[(1) - (3)]).first_line, PROCEDURE_HEAD, 1, (yyvsp[(3) - (3)].NodePtr));
			(yyval.NodePtr)->add(new AST::Node((yylsp[(2) - (3)]).first_line, (yyvsp[(2) - (3)].sValue), AST::Attribute::Identifier));
		}
		else
		{
			(yyval.NodePtr) = new AST::Node((yylsp[(2) - (3)]).first_line, (yyvsp[(2) - (3)].sValue), AST::Attribute::Identifier);
		}
		/*
			Hacking Trick: 最后一个孩子是类型名称，
			在语法树中，不希望类型和变量为sibling，但是父节点Operation无法记录类型名称，
			所以在数组中保留类型名称，在构造语法树时父节点可以访问，
			但是在数目上假装其不存在，这样按for循环绘制就不会绘制出来
		*/
		(yyval.NodePtr)->m_Operation.NumOperands -= 1;
	;}
    break;

  case 53:
#line 450 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    { 
		(yyval.NodePtr) = (yyvsp[(2) - (3)].NodePtr);
	;}
    break;

  case 54:
#line 453 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {(yyval.NodePtr) = NULL;;}
    break;

  case 55:
#line 457 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr)->add((yyvsp[(3) - (3)].NodePtr));
	;}
    break;

  case 56:
#line 461 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node(0, PARA_LIST, 1, (yyvsp[(1) - (1)].NodePtr));
	;}
    break;

  case 57:
#line 467 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node(0, VAR_PARAM, 1, (yyvsp[(3) - (3)].NodePtr));
		(yyval.NodePtr)->add((yyvsp[(1) - (3)].NodePtrList));
	;}
    break;

  case 58:
#line 472 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node(0, VAL_PARAM, 1, (yyvsp[(3) - (3)].NodePtr));
		(yyval.NodePtr)->add((yyvsp[(1) - (3)].NodePtrList));
	;}
    break;

  case 59:
#line 479 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtrList) = (yyvsp[(2) - (2)].NodePtrList);
	;}
    break;

  case 60:
#line 485 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtrList) = (yyvsp[(1) - (1)].NodePtrList);
	;}
    break;

  case 61:
#line 492 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		if ((yyvsp[(1) - (1)].NodePtr))
		{
			(yyval.NodePtr) = new AST::Node(0, ROUTINE_BODY, 1, (yyvsp[(1) - (1)].NodePtr));
		}
		else
		{
			(yyval.NodePtr) = NULL;
		}
	;}
    break;

  case 62:
#line 505 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = (yyvsp[(2) - (3)].NodePtr);
	;}
    break;

  case 63:
#line 511 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		if ((yyvsp[(1) - (3)].NodePtr) == NULL)
		{
			(yyval.NodePtr) = (yyvsp[(2) - (3)].NodePtr);
		}
		else
		{
			(yyval.NodePtr) = new AST::Node(0, SEMI, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(2) - (3)].NodePtr));
		}
	;}
    break;

  case 64:
#line 521 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {(yyval.NodePtr) = NULL;;}
    break;

  case 65:
#line 525 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		AST::ValConstant temp;
		temp.Type = AST::ConstantType::Integer;
		temp.iValue = (yyvsp[(1) - (3)].iValue);
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (3)]).first_line, LABEL_STMT, 2, new AST::Node((yylsp[(1) - (3)]).first_line, temp), (yyvsp[(3) - (3)].NodePtr));
	;}
    break;

  case 66:
#line 532 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);
	;}
    break;

  case 67:
#line 537 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);;}
    break;

  case 68:
#line 538 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);;}
    break;

  case 69:
#line 539 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);;}
    break;

  case 70:
#line 540 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);;}
    break;

  case 71:
#line 541 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);;}
    break;

  case 72:
#line 542 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);;}
    break;

  case 73:
#line 543 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);;}
    break;

  case 74:
#line 544 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);;}
    break;

  case 75:
#line 545 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);;}
    break;

  case 76:
#line 550 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(2) - (3)]).first_line, ASSIGN, 2, new AST::Node((yylsp[(1) - (3)]).first_line, (yyvsp[(1) - (3)].sValue), AST::Attribute::Identifier), (yyvsp[(3) - (3)].NodePtr));
	;}
    break;

  case 77:
#line 554 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(5) - (6)]).first_line, ASSIGN, 2, 
					  new AST::Node((yylsp[(2) - (6)]).first_line, BRACKET, 2, new AST::Node((yylsp[(1) - (6)]).first_line, (yyvsp[(1) - (6)].sValue), AST::Attribute::Identifier), (yyvsp[(3) - (6)].NodePtr)),
					  (yyvsp[(6) - (6)].NodePtr));
	;}
    break;

  case 78:
#line 560 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(4) - (5)]).first_line, ASSIGN, 2,
					  new AST::Node((yylsp[(2) - (5)]).first_line, DOT, 2, new AST::Node((yylsp[(1) - (5)]).first_line, (yyvsp[(1) - (5)].sValue), AST::Attribute::Identifier),
					  				   new AST::Node((yylsp[(3) - (5)]).first_line, (yyvsp[(3) - (5)].sValue), AST::Attribute::Identifier))
					  , (yyvsp[(5) - (5)].NodePtr));
	;}
    break;

  case 79:
#line 570 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (1)]).first_line, CALL_PROC, 1, new AST::Node((yylsp[(1) - (1)]).first_line, (yyvsp[(1) - (1)].sValue), AST::Attribute::Identifier));
	;}
    break;

  case 80:
#line 574 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (4)]).first_line, CALL_PROC, 1, new AST::Node((yylsp[(1) - (4)]).first_line, (yyvsp[(1) - (4)].sValue), AST::Attribute::Identifier));
		(yyval.NodePtr)->add((yyvsp[(3) - (4)].NodePtrList));
	;}
    break;

  case 81:
#line 579 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (1)]).first_line, SYS_PROC, 1, new AST::Node((yylsp[(1) - (1)]).first_line, (yyvsp[(1) - (1)].sValue), AST::Attribute::Identifier));
	;}
    break;

  case 82:
#line 583 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (4)]).first_line, SYS_PROC, 1, new AST::Node((yylsp[(1) - (4)]).first_line, (yyvsp[(1) - (4)].sValue), AST::Attribute::Identifier));
		(yyval.NodePtr)->add((yyvsp[(3) - (4)].NodePtrList));
	;}
    break;

  case 83:
#line 591 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		if ((yyvsp[(5) - (5)].NodePtr))
		{
			(yyval.NodePtr) = new AST::Node((yylsp[(1) - (5)]).first_line, IF, 3, (yyvsp[(2) - (5)].NodePtr), (yyvsp[(4) - (5)].NodePtr), (yyvsp[(5) - (5)].NodePtr));
		}
		else 
		{
			(yyval.NodePtr) = new AST::Node((yylsp[(1) - (5)]).first_line, IF, 2, (yyvsp[(2) - (5)].NodePtr), (yyvsp[(4) - (5)].NodePtr));
		}
	;}
    break;

  case 84:
#line 603 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {(yyval.NodePtr) = (yyvsp[(2) - (2)].NodePtr);;}
    break;

  case 85:
#line 604 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {(yyval.NodePtr) = NULL;;}
    break;

  case 86:
#line 608 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {	// $4, $2的顺序是为了和while语句保持一致
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (4)]).first_line, REPEAT, 2, (yyvsp[(4) - (4)].NodePtr), (yyvsp[(2) - (4)].NodePtr));
	;}
    break;

  case 87:
#line 614 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (4)]).first_line, WHILE, 2, (yyvsp[(2) - (4)].NodePtr), (yyvsp[(4) - (4)].NodePtr));
	;}
    break;

  case 88:
#line 621 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (8)]).first_line, TO, 4, new AST::Node((yylsp[(2) - (8)]).first_line, (yyvsp[(2) - (8)].sValue), AST::Attribute::Identifier),
						(yyvsp[(4) - (8)].NodePtr), (yyvsp[(6) - (8)].NodePtr), (yyvsp[(8) - (8)].NodePtr));
	;}
    break;

  case 89:
#line 626 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (8)]).first_line, DOWNTO, 4, new AST::Node((yylsp[(2) - (8)]).first_line, (yyvsp[(2) - (8)].sValue), AST::Attribute::Identifier),
						(yyvsp[(4) - (8)].NodePtr), (yyvsp[(6) - (8)].NodePtr), (yyvsp[(8) - (8)].NodePtr));
	;}
    break;

  case 90:
#line 633 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (5)]).first_line, CASE_STMT, 2, (yyvsp[(2) - (5)].NodePtr), (yyvsp[(4) - (5)].NodePtr));
	;}
    break;

  case 91:
#line 639 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr)->add((yyvsp[(2) - (2)].NodePtr));
	;}
    break;

  case 92:
#line 643 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node(0, CASE_LIST, 1, (yyvsp[(1) - (1)].NodePtr));
	;}
    break;

  case 93:
#line 649 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (4)]).first_line, CASE, 2, (yyvsp[(1) - (4)].NodePtr), (yyvsp[(3) - (4)].NodePtr));
	;}
    break;

  case 94:
#line 653 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (4)]).first_line, CASE, 2
					  , new AST::Node((yylsp[(1) - (4)]).first_line, (yyvsp[(1) - (4)].sValue), AST::Attribute::Identifier)
					  , (yyvsp[(3) - (4)].NodePtr));
	;}
    break;

  case 95:
#line 661 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		AST::ValConstant temp;
		temp.Type = AST::ConstantType::Integer;
        temp.iValue = (yyvsp[(2) - (2)].iValue);
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (2)]).first_line, GOTO, 1, new AST::Node((yylsp[(2) - (2)]).first_line, temp));
	;}
    break;

  case 96:
#line 670 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtrList)->push_back((yyvsp[(3) - (3)].NodePtr));
	;}
    break;

  case 97:
#line 674 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtrList) = new std::vector<AST::Node*>();
		(yyval.NodePtrList)->push_back((yyvsp[(1) - (1)].NodePtr));
	;}
    break;

  case 98:
#line 681 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
        (yyval.NodePtr) = new AST::Node((yylsp[(2) - (3)]).first_line, _GE_, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
    ;}
    break;

  case 99:
#line 685 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
        (yyval.NodePtr) = new AST::Node((yylsp[(2) - (3)]).first_line, _GT_, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
    ;}
    break;

  case 100:
#line 689 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
        (yyval.NodePtr) = new AST::Node((yylsp[(2) - (3)]).first_line, _LE_, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
    ;}
    break;

  case 101:
#line 693 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
        (yyval.NodePtr) = new AST::Node((yylsp[(2) - (3)]).first_line, _LT_, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
    ;}
    break;

  case 102:
#line 697 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
        (yyval.NodePtr) = new AST::Node((yylsp[(2) - (3)]).first_line, EQUAL, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
    ;}
    break;

  case 103:
#line 701 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
        (yyval.NodePtr) = new AST::Node((yylsp[(2) - (3)]).first_line, UNEQUAL, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
    ;}
    break;

  case 104:
#line 705 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
        (yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);
    ;}
    break;

  case 105:
#line 711 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
        (yyval.NodePtr) = new AST::Node((yylsp[(2) - (3)]).first_line, PLUS, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
    ;}
    break;

  case 106:
#line 715 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
        (yyval.NodePtr) = new AST::Node((yylsp[(2) - (3)]).first_line, MINUS, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
    ;}
    break;

  case 107:
#line 719 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(2) - (3)]).first_line, OR, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
	;}
    break;

  case 108:
#line 723 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
        (yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);
    ;}
    break;

  case 109:
#line 729 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
        (yyval.NodePtr) = new AST::Node((yylsp[(2) - (3)]).first_line, MUL, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
    ;}
    break;

  case 110:
#line 733 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
        (yyval.NodePtr) = new AST::Node((yylsp[(2) - (3)]).first_line, DIV, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
    ;}
    break;

  case 111:
#line 737 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
        (yyval.NodePtr) = new AST::Node((yylsp[(2) - (3)]).first_line, MOD, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
    ;}
    break;

  case 112:
#line 741 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(2) - (3)]).first_line, AND, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
	;}
    break;

  case 113:
#line 745 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);
    	;}
    break;

  case 114:
#line 751 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
       		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (1)]).first_line, (yyvsp[(1) - (1)].sValue), AST::Attribute::Identifier);
    	;}
    break;

  case 115:
#line 755 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (4)]).first_line, CALL_FUNCT, 1
					  , new AST::Node((yylsp[(1) - (4)]).first_line, (yyvsp[(1) - (4)].sValue), AST::Attribute::Identifier));
		(yyval.NodePtr)->add((yyvsp[(3) - (4)].NodePtrList));
	;}
    break;

  case 116:
#line 761 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (1)]).first_line, SYS_FUNCT, 1
					  , new AST::Node((yylsp[(1) - (1)]).first_line, (yyvsp[(1) - (1)].sValue), AST::Attribute::Identifier));
	;}
    break;

  case 117:
#line 766 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (4)]).first_line, SYS_FUNCT, 1
					  , new AST::Node((yylsp[(1) - (4)]).first_line, (yyvsp[(1) - (4)].sValue), AST::Attribute::Identifier));
		(yyval.NodePtr)->add((yyvsp[(3) - (4)].NodePtrList));
	;}
    break;

  case 118:
#line 772 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);
	;}
    break;

  case 119:
#line 776 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
        	(yyval.NodePtr) = (yyvsp[(2) - (3)].NodePtr);
    	;}
    break;

  case 120:
#line 780 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (2)]).first_line, NOT, 1, (yyvsp[(2) - (2)].NodePtr));
	;}
    break;

  case 121:
#line 784 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (2)]).first_line, MINUS, 1, (yyvsp[(2) - (2)].NodePtr));
	;}
    break;

  case 122:
#line 788 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(1) - (4)]).first_line, BRACKET, 2
					  , new AST::Node((yylsp[(1) - (4)]).first_line, (yyvsp[(1) - (4)].sValue), AST::Attribute::Identifier)
					  , (yyvsp[(3) - (4)].NodePtr));
	;}
    break;

  case 123:
#line 794 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtr) = new AST::Node((yylsp[(2) - (3)]).first_line, DOT, 2
					  , new AST::Node((yylsp[(1) - (3)]).first_line, (yyvsp[(1) - (3)].sValue), AST::Attribute::Identifier)
					  , new AST::Node((yylsp[(3) - (3)]).first_line, (yyvsp[(3) - (3)].sValue), AST::Attribute::Identifier));
	;}
    break;

  case 124:
#line 802 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtrList)->push_back((yyvsp[(3) - (3)].NodePtr));
	;}
    break;

  case 125:
#line 806 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"
    {
		(yyval.NodePtrList) = new std::vector<AST::Node*>();
		(yyval.NodePtrList)->push_back((yyvsp[(1) - (1)].NodePtr));
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 2781 "/Applications/zju/编译原理/final_proj/Code/source/yacc.tab.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 811 "/Applications/zju/编译原理/final_proj/Code/lex_yacc/yacc.y"

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

