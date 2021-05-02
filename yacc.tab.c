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
#define YYLSP_NEEDED 0



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
     FUNCT = 333
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




/* Copy the first part of user declarations.  */
#line 1 "yacc.y"

    #include <iostream>    
    #include <stdarg.h>
	#include <vector>
    #include "Utils.hpp"
    #include "Interpreter.hpp"
	#include <fstream>

    int yylex(void);
    void yyerror(const char *);


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
#line 13 "yacc.y"
{
    int iValue; // integer value
    double dValue; // double value
    char cValue; // char value
    char* sValue;
    Node* NodePtr; // Node Pointer
	std::vector<Node*>* NodePtrList; // List
}
/* Line 193 of yacc.c.  */
#line 273 "yacc.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 286 "yacc.tab.c"

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
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYLAST   343

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  79
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  122
/* YYNRULES -- Number of states.  */
#define YYNSTATES  251

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   333

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
      75,    76,    77,    78
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    11,    14,    17,    23,    24,    27,
      28,    34,    39,    41,    43,    45,    47,    49,    52,    53,
      56,    58,    63,    65,    67,    69,    71,    75,    79,    84,
      90,    94,   101,   105,   107,   110,   111,   114,   116,   121,
     124,   127,   129,   131,   132,   137,   143,   148,   152,   156,
     157,   161,   163,   167,   171,   174,   176,   178,   182,   186,
     187,   191,   193,   195,   197,   199,   201,   203,   205,   207,
     209,   211,   215,   222,   228,   230,   235,   237,   242,   247,
     253,   256,   257,   262,   267,   276,   278,   280,   286,   289,
     291,   296,   301,   304,   308,   310,   314,   318,   322,   326,
     330,   334,   336,   340,   344,   348,   350,   354,   358,   362,
     366,   368,   370,   375,   377,   382,   384,   388,   391,   394,
     399,   403,   407
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      80,     0,    -1,    81,    82,    13,    -1,    52,     8,    30,
      -1,    84,   109,    -1,    84,   109,    -1,    85,    86,    89,
      96,    99,    -1,    -1,    39,    87,    -1,    -1,    87,     8,
      26,    88,    30,    -1,     8,    26,    88,    30,    -1,     3,
      -1,     4,    -1,     5,    -1,     6,    -1,    34,    -1,    57,
      90,    -1,    -1,    90,    91,    -1,    91,    -1,     8,    26,
      92,    30,    -1,    93,    -1,    94,    -1,     7,    -1,     8,
      -1,     9,    95,    10,    -1,    88,    29,    88,    -1,    21,
      88,    29,    88,    -1,    21,    88,    29,    21,    88,    -1,
       8,    29,     8,    -1,    36,    11,    93,    12,    48,    92,
      -1,    95,    14,     8,    -1,     8,    -1,    59,    97,    -1,
      -1,    97,    98,    -1,    98,    -1,    95,    15,    92,    30,
      -1,    99,   100,    -1,    99,   102,    -1,   100,    -1,   102,
      -1,    -1,   101,    30,    83,    30,    -1,    45,     8,   104,
      15,    93,    -1,   103,    30,    83,    30,    -1,    51,     8,
     104,    -1,     9,   105,    10,    -1,    -1,   105,    30,   106,
      -1,   106,    -1,   107,    15,    93,    -1,   108,    15,    93,
      -1,    59,    95,    -1,    95,    -1,   110,    -1,    37,   111,
      43,    -1,   111,   112,    30,    -1,    -1,     3,    15,   113,
      -1,   113,    -1,   114,    -1,   115,    -1,   110,    -1,   116,
      -1,   118,    -1,   119,    -1,   120,    -1,   122,    -1,   125,
      -1,     8,    27,   127,    -1,     8,    11,   127,    12,    27,
     127,    -1,     8,    13,     8,    27,   127,    -1,     8,    -1,
       8,     9,   131,    10,    -1,    32,    -1,    32,     9,   126,
      10,    -1,    31,     9,   130,    10,    -1,    47,   127,    55,
     112,   117,    -1,    42,   112,    -1,    -1,    54,   111,    58,
     127,    -1,    60,   127,    40,   112,    -1,    44,     8,    27,
     127,   121,   127,    40,   112,    -1,    56,    -1,    41,    -1,
      38,   127,    48,   123,    43,    -1,   123,   124,    -1,   124,
      -1,    88,    15,   112,    30,    -1,     8,    15,   112,    30,
      -1,    46,     3,    -1,   126,    14,   127,    -1,   127,    -1,
     127,    22,   128,    -1,   127,    23,   128,    -1,   127,    24,
     128,    -1,   127,    25,   128,    -1,   127,    26,   128,    -1,
     127,    18,   128,    -1,   128,    -1,   128,    20,   129,    -1,
     128,    21,   129,    -1,   128,    49,   129,    -1,   129,    -1,
     129,    16,   130,    -1,   129,    17,   130,    -1,   129,    28,
     130,    -1,   129,    35,   130,    -1,   130,    -1,     8,    -1,
       8,     9,   131,    10,    -1,    33,    -1,    33,     9,   131,
      10,    -1,    88,    -1,     9,   127,    10,    -1,    19,   130,
      -1,    21,   130,    -1,     8,    11,   127,    12,    -1,     8,
      13,     8,    -1,   131,    14,   127,    -1,   127,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    63,    63,    72,    80,    94,   110,   131,   136,   140,
     144,   148,   156,   163,   170,   178,   186,   197,   201,   205,
     209,   216,   225,   229,   234,   238,   242,   243,   244,   245,
     246,   250,   267,   271,   279,   283,   287,   291,   298,   313,
     317,   321,   326,   331,   335,   344,   369,   376,   398,   402,
     405,   409,   415,   421,   429,   435,   442,   455,   461,   472,
     475,   482,   488,   489,   490,   491,   492,   493,   494,   495,
     496,   500,   504,   510,   520,   524,   529,   533,   538,   542,
     555,   556,   559,   565,   572,   579,   580,   583,   589,   593,
     599,   603,   611,   620,   624,   631,   635,   639,   643,   647,
     651,   655,   661,   665,   669,   673,   679,   683,   687,   691,
     695,   701,   705,   711,   716,   722,   726,   730,   734,   738,
     744,   752,   756
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "REAL", "CHAR", "STRING",
  "SYS_TYPE", "ID", "LP", "RP", "LB", "RB", "DOT", "COMMA", "COLON", "MUL",
  "DIV", "UNEQUAL", "NOT", "PLUS", "MINUS", "GE", "GT", "LE", "LT",
  "EQUAL", "ASSIGN", "MOD", "DOTDOT", "SEMI", "READ", "SYS_PROC",
  "SYS_FUNCT", "SYS_CON", "AND", "ARRAY", "_BEGIN", "CASE", "CONST", "DO",
  "DOWNTO", "ELSE", "END", "FOR", "FUNCTION", "GOTO", "IF", "OF", "OR",
  "PACKED", "PROCEDURE", "PROGRAM", "RECORD", "REPEAT", "THEN", "TO",
  "TYPE", "UNTIL", "VAR", "WHILE", "ROUTINE", "ROUTINE_BODY",
  "ROUTINE_HEAD", "CONST_PART", "VAR_PART", "BRACKET", "CASE_STMT",
  "CASE_LIST", "TYPE_PART", "VAL_PARAM", "VAR_PARAM", "PARA_LIST",
  "FUNCTION_HEAD", "SUB_ROUTINE", "PROCEDURE_HEAD", "PROC", "LABEL_STMT",
  "FUNCT", "$accept", "program", "program_head", "routine", "sub_routine",
  "routine_head", "label_part", "const_part", "const_expr_list",
  "const_value", "type_part", "type_decl_list", "type_definition",
  "type_decl", "simple_type_decl", "array_type_decl", "name_list",
  "var_part", "var_decl_list", "var_decl", "routine_part", "function_decl",
  "function_head", "procedure_decl", "procedure_head", "parameters",
  "para_decl_list", "para_type_list", "var_para_list", "val_para_list",
  "routine_body", "compound_stmt", "stmt_list", "stmt", "non_label_stmt",
  "assign_stmt", "proc_stmt", "if_stmt", "else_clause", "repeat_stmt",
  "while_stmt", "for_stmt", "direction", "case_stmt", "case_expr_list",
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
     325,   326,   327,   328,   329,   330,   331,   332,   333
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    79,    80,    81,    82,    83,    84,    85,    86,    86,
      87,    87,    88,    88,    88,    88,    88,    89,    89,    90,
      90,    91,    92,    92,    93,    93,    93,    93,    93,    93,
      93,    94,    95,    95,    96,    96,    97,    97,    98,    99,
      99,    99,    99,    99,   100,   101,   102,   103,   104,   104,
     105,   105,   106,   106,   107,   108,   109,   110,   111,   111,
     112,   112,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   114,   114,   114,   115,   115,   115,   115,   115,   116,
     117,   117,   118,   119,   120,   121,   121,   122,   123,   123,
     124,   124,   125,   126,   126,   127,   127,   127,   127,   127,
     127,   127,   128,   128,   128,   128,   129,   129,   129,   129,
     129,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   131,   131
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     2,     2,     5,     0,     2,     0,
       5,     4,     1,     1,     1,     1,     1,     2,     0,     2,
       1,     4,     1,     1,     1,     1,     3,     3,     4,     5,
       3,     6,     3,     1,     2,     0,     2,     1,     4,     2,
       2,     1,     1,     0,     4,     5,     4,     3,     3,     0,
       3,     1,     3,     3,     2,     1,     1,     3,     3,     0,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     6,     5,     1,     4,     1,     4,     4,     5,
       2,     0,     4,     4,     8,     1,     1,     5,     2,     1,
       4,     4,     2,     3,     1,     3,     3,     3,     3,     3,
       3,     1,     3,     3,     3,     1,     3,     3,     3,     3,
       1,     1,     4,     1,     4,     1,     3,     2,     2,     4,
       3,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     7,     0,     1,     0,     0,     9,     3,
       2,    59,     4,    56,     0,    18,     0,     0,     8,     0,
      35,     0,    74,     0,    76,     0,    57,     0,     0,     0,
      59,     0,    64,     0,    61,    62,    63,    65,    66,    67,
      68,    69,    70,     0,     0,     0,    17,    20,     0,    43,
       0,     0,     0,     0,     0,     0,     0,    12,    13,    14,
      15,   111,     0,     0,     0,   113,    16,   115,     0,   101,
     105,   110,     0,    92,     0,     0,     0,    58,     0,     0,
       0,    19,    33,     0,    34,    37,     0,     0,     6,    41,
       0,    42,     0,    60,   122,     0,     0,     0,    71,     0,
       0,    94,     0,     0,     0,     0,   117,   118,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    11,     0,    24,
      25,     0,     0,     0,     0,     0,    22,    23,     0,     0,
      36,    49,    49,    39,    40,     7,     7,    75,     0,     0,
       0,    78,    77,     0,     0,     0,   120,   116,     0,   100,
      95,    96,    97,    98,    99,     0,     0,     0,    89,   102,
     103,   104,   106,   107,   108,   109,     0,    81,    82,    83,
      10,     0,     0,     0,     0,     0,    21,    32,     0,     0,
       0,    47,     0,     0,     0,   121,     0,    73,    93,   112,
     119,   114,     0,     0,    87,    88,    86,    85,     0,     0,
      79,    30,    26,     0,     0,    27,    38,     0,    55,     0,
      51,     0,     0,     0,    44,     5,    46,    72,     0,     0,
       0,    80,     0,    28,     0,    54,    48,     0,     0,     0,
      45,    91,    90,     0,    29,     0,    50,    52,    53,    84,
      31
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,   192,   193,     8,    15,    18,    67,
      20,    46,    47,   135,   136,   137,    83,    49,    84,    85,
      88,    89,    90,    91,    92,   190,   219,   220,   221,   222,
      12,    32,    16,    33,    34,    35,    36,    37,   210,    38,
      39,    40,   208,    41,   167,   168,    42,   100,    94,    69,
      70,    71,    95
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -173
static const yytype_int16 yypact[] =
{
     -41,    26,    13,  -173,    29,  -173,    39,    33,    62,  -173,
    -173,  -173,  -173,  -173,   101,    54,    11,    90,   115,   120,
      75,   124,   108,   134,   136,   214,  -173,   140,   149,   214,
    -173,   214,  -173,   121,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,    81,   127,   132,   120,  -173,   155,   -13,
     118,   214,   214,   166,   214,   214,   214,  -173,  -173,  -173,
    -173,   148,   214,   214,   214,   167,  -173,  -173,   247,    20,
      77,  -173,   150,  -173,    -2,    60,   259,  -173,   145,    81,
     207,  -173,  -173,    63,   155,  -173,   171,   173,   -13,  -173,
     152,  -173,   153,  -173,   311,    50,   293,   157,   311,   178,
      69,   311,   214,   214,   190,   278,  -173,  -173,   214,   214,
     214,   214,   214,   214,   214,    22,   214,   214,   214,   214,
     214,   214,   214,   214,   100,   214,   100,  -173,   169,  -173,
     172,   155,    81,   189,   174,   175,  -173,  -173,   196,   207,
    -173,   198,   198,  -173,  -173,  -173,  -173,  -173,   214,   181,
     214,  -173,  -173,   214,    85,   302,  -173,  -173,   119,    20,
      20,    20,    20,    20,    20,   206,   210,   163,  -173,    77,
      77,    77,  -173,  -173,  -173,  -173,   168,   184,   311,  -173,
    -173,   219,   126,   200,   246,    81,  -173,  -173,   201,     2,
     215,  -173,   202,    33,   204,   311,   214,   311,   311,  -173,
    -173,  -173,   100,   100,  -173,  -173,  -173,  -173,   214,   100,
    -173,  -173,  -173,   253,   224,  -173,  -173,   155,   223,     5,
    -173,   225,   227,   246,  -173,  -173,  -173,   311,   208,   209,
     268,  -173,    81,  -173,   197,   223,  -173,     2,   246,   246,
    -173,  -173,  -173,   100,  -173,   207,  -173,  -173,  -173,  -173,
    -173
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -173,  -173,  -173,  -173,    98,   243,  -173,  -173,  -173,   -43,
    -173,  -173,   216,  -132,  -172,  -173,  -127,  -173,  -173,   176,
    -173,   180,  -173,   187,  -173,   122,  -173,    24,  -173,  -173,
      70,    -6,   236,  -121,   226,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,   111,  -173,  -173,   -23,   229,
     -71,   -46,   -58
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      78,    13,    68,   177,   182,   179,    74,   188,    76,    99,
      82,     1,   214,     5,    21,   236,   109,   106,   107,    22,
     110,   111,   112,   113,   114,    57,    58,    59,    60,    96,
     165,    98,    86,   101,     4,   237,   128,   134,    87,   105,
     116,   117,    23,    24,   154,   169,   170,   171,    11,    25,
     158,   240,    10,   124,    26,    27,    66,    28,    29,     9,
     147,   217,   218,    21,   148,    30,   247,   248,    22,   118,
      11,    31,   166,   172,   173,   174,   175,   138,   139,   152,
     155,   228,   229,   153,    57,    58,    59,    60,   231,   183,
     235,    23,    24,   119,   120,   199,   134,    11,    25,   148,
     176,    14,   178,    21,    27,   121,    28,    29,    22,    17,
     218,    19,   122,   250,    30,    66,    43,    51,   125,    52,
      31,    53,   249,    44,   166,   195,    22,   197,    45,   201,
     198,    23,    24,   148,    48,    54,   212,    11,    25,    50,
     138,   134,   215,    55,    27,    56,    28,    29,    72,    23,
      24,    77,    73,    79,    30,    11,    25,   102,    80,   103,
      31,   104,    27,    82,    28,    29,    57,    58,    59,    60,
     233,   165,    30,   227,    97,   127,   108,   123,    31,   141,
     134,   142,   145,   146,   150,   230,   109,    13,   151,   244,
     110,   111,   112,   113,   114,   134,   134,    66,   156,   180,
     184,   181,   134,   185,   187,   186,   204,   189,   196,   206,
      57,    58,    59,    60,   129,   130,   131,    57,    58,    59,
      60,   202,    61,    62,   207,   203,   209,   211,   132,   213,
     223,   216,   224,    63,   226,    64,   234,   138,   241,   242,
     238,    66,   239,   133,   194,   245,     7,    65,    66,    57,
      58,    59,    60,   129,   130,   131,    57,    58,    59,    60,
     140,   246,    81,   225,   191,   109,    75,   132,   143,   110,
     111,   112,   113,   114,   232,   144,    93,   109,   205,     0,
      66,   110,   111,   112,   113,   114,   109,    66,   157,     0,
     110,   111,   112,   113,   114,   115,   109,     0,     0,   126,
     110,   111,   112,   113,   114,   149,     0,     0,   243,     0,
       0,   109,     0,     0,   200,   110,   111,   112,   113,   114,
     109,     0,     0,     0,   110,   111,   112,   113,   114,   109,
       0,     0,     0,   110,   111,   112,   113,   114,   159,   160,
     161,   162,   163,   164
};

static const yytype_int16 yycheck[] =
{
      43,     7,    25,   124,   131,   126,    29,   139,    31,    55,
       8,    52,   184,     0,     3,    10,    18,    63,    64,     8,
      22,    23,    24,    25,    26,     3,     4,     5,     6,    52,
       8,    54,    45,    56,     8,    30,    79,    80,    51,    62,
      20,    21,    31,    32,   102,   116,   117,   118,    37,    38,
     108,   223,    13,    55,    43,    44,    34,    46,    47,    30,
      10,    59,   189,     3,    14,    54,   238,   239,     8,    49,
      37,    60,   115,   119,   120,   121,   122,    14,    15,    10,
     103,   202,   203,    14,     3,     4,     5,     6,   209,   132,
     217,    31,    32,    16,    17,    10,   139,    37,    38,    14,
     123,    39,   125,     3,    44,    28,    46,    47,     8,     8,
     237,    57,    35,   245,    54,    34,    26,     9,    58,    11,
      60,    13,   243,     8,   167,   148,     8,   150,     8,    10,
     153,    31,    32,    14,    59,    27,    10,    37,    38,    15,
      14,   184,   185,     9,    44,     9,    46,    47,     8,    31,
      32,    30,     3,    26,    54,    37,    38,     9,    26,    11,
      60,    13,    44,     8,    46,    47,     3,     4,     5,     6,
     213,     8,    54,   196,     8,    30,     9,    27,    60,     8,
     223,     8,    30,    30,    27,   208,    18,   193,    10,   232,
      22,    23,    24,    25,    26,   238,   239,    34,     8,    30,
      11,    29,   245,    29,     8,    30,    43,     9,    27,    41,
       3,     4,     5,     6,     7,     8,     9,     3,     4,     5,
       6,    15,     8,     9,    56,    15,    42,     8,    21,    29,
      15,    30,    30,    19,    30,    21,    12,    14,    30,    30,
      15,    34,    15,    36,   146,    48,     3,    33,    34,     3,
       4,     5,     6,     7,     8,     9,     3,     4,     5,     6,
      84,   237,    46,   193,   142,    18,    30,    21,    88,    22,
      23,    24,    25,    26,    21,    88,    50,    18,   167,    -1,
      34,    22,    23,    24,    25,    26,    18,    34,    10,    -1,
      22,    23,    24,    25,    26,    48,    18,    -1,    -1,    40,
      22,    23,    24,    25,    26,    12,    -1,    -1,    40,    -1,
      -1,    18,    -1,    -1,    12,    22,    23,    24,    25,    26,
      18,    -1,    -1,    -1,    22,    23,    24,    25,    26,    18,
      -1,    -1,    -1,    22,    23,    24,    25,    26,   109,   110,
     111,   112,   113,   114
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    52,    80,    81,     8,     0,    82,    84,    85,    30,
      13,    37,   109,   110,    39,    86,   111,     8,    87,    57,
      89,     3,     8,    31,    32,    38,    43,    44,    46,    47,
      54,    60,   110,   112,   113,   114,   115,   116,   118,   119,
     120,   122,   125,    26,     8,     8,    90,    91,    59,    96,
      15,     9,    11,    13,    27,     9,     9,     3,     4,     5,
       6,     8,     9,    19,    21,    33,    34,    88,   127,   128,
     129,   130,     8,     3,   127,   111,   127,    30,    88,    26,
      26,    91,     8,    95,    97,    98,    45,    51,    99,   100,
     101,   102,   103,   113,   127,   131,   127,     8,   127,   130,
     126,   127,     9,    11,    13,   127,   130,   130,     9,    18,
      22,    23,    24,    25,    26,    48,    20,    21,    49,    16,
      17,    28,    35,    27,    55,    58,    40,    30,    88,     7,
       8,     9,    21,    36,    88,    92,    93,    94,    14,    15,
      98,     8,     8,   100,   102,    30,    30,    10,    14,    12,
      27,    10,    10,    14,   131,   127,     8,    10,   131,   128,
     128,   128,   128,   128,   128,     8,    88,   123,   124,   129,
     129,   129,   130,   130,   130,   130,   127,   112,   127,   112,
      30,    29,    95,    88,    11,    29,    30,     8,    92,     9,
     104,   104,    83,    84,    83,   127,    27,   127,   127,    10,
      12,    10,    15,    15,    43,   124,    41,    56,   121,    42,
     117,     8,    10,    29,    93,    88,    30,    59,    95,   105,
     106,   107,   108,    15,    30,   109,    30,   127,   112,   112,
     127,   112,    21,    88,    12,    95,    10,    30,    15,    15,
      93,    30,    30,    40,    88,    48,   106,    93,    93,   112,
      92
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
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
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

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



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


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


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

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

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 64 "yacc.y"
    {
		std::ofstream outFile("AST.out");
		outFile << "Program Name: " << (yyvsp[(1) - (3)].sValue) << std::endl;
		Interpreter::execute((yyvsp[(2) - (3)].NodePtr), outFile);
		exit(0);
	;}
    break;

  case 3:
#line 73 "yacc.y"
    {
		(yyval.sValue) = new char[strlen((yyvsp[(2) - (3)].sValue))];
		strcpy((yyval.sValue), (yyvsp[(2) - (3)].sValue));
	;}
    break;

  case 4:
#line 81 "yacc.y"
    {
		// 因为两个都nullable
		// 所以把所有非空部分拼成一个列表再一次性构造$$，避免了很多的if-else语句
		
		std::vector<Node*>* Temp = new std::vector<Node*>();
		if ((yyvsp[(1) - (2)].NodePtr) != NULL) Temp->push_back((yyvsp[(1) - (2)].NodePtr));
		if ((yyvsp[(2) - (2)].NodePtr) != NULL) Temp->push_back((yyvsp[(2) - (2)].NodePtr));
		if (Temp->size() > 0) (yyval.NodePtr) = new Node(ROUTINE, Temp);
		else (yyval.NodePtr) = NULL;
	;}
    break;

  case 5:
#line 95 "yacc.y"
    {
		// 因为两个都nullable
		// 所以把所有非空部分拼成一个列表再一次性构造$$，避免了很多的if-else语句
		
		std::vector<Node*>* Temp = new std::vector<Node*>();
		if ((yyvsp[(1) - (2)].NodePtr)) Temp->push_back((yyvsp[(1) - (2)].NodePtr));
		if ((yyvsp[(2) - (2)].NodePtr)) Temp->push_back((yyvsp[(2) - (2)].NodePtr));
		if (Temp->size() > 0)
			(yyval.NodePtr) = new Node(SUB_ROUTINE, Temp);
		else
			(yyval.NodePtr) = NULL;
	;}
    break;

  case 6:
#line 111 "yacc.y"
    {
		// 因为很多部分有nullable
		// 所以把所有非空部分拼成一个列表再一次性构造$$，避免了很多的if-else语句
		
		std::vector<Node*>* Temp = new std::vector<Node*>();
		if ((yyvsp[(2) - (5)].NodePtr) != NULL) Temp->push_back((yyvsp[(2) - (5)].NodePtr));
		if ((yyvsp[(3) - (5)].NodePtr) != NULL) Temp->push_back((yyvsp[(3) - (5)].NodePtr));
		if ((yyvsp[(4) - (5)].NodePtr) != NULL) Temp->push_back((yyvsp[(4) - (5)].NodePtr));
		if ((yyvsp[(5) - (5)].NodePtrList) != NULL) 
		{
			for (auto node : *((yyvsp[(5) - (5)].NodePtrList)))
				Temp->push_back(node);
		}
		if (Temp->size() > 0)
			(yyval.NodePtr) = new Node(ROUTINE_HEAD, Temp);
		else
			(yyval.NodePtr) = NULL;
	;}
    break;

  case 8:
#line 137 "yacc.y"
    {
		(yyval.NodePtr) = new Node(CONST_PART, (yyvsp[(2) - (2)].NodePtrList));
	;}
    break;

  case 9:
#line 140 "yacc.y"
    {(yyval.NodePtr) = NULL;;}
    break;

  case 10:
#line 145 "yacc.y"
    {
		(yyval.NodePtrList)->push_back(new Node(EQUAL, 2, new Node((yyvsp[(2) - (5)].sValue), NodeType::Identifier), (yyvsp[(4) - (5)].NodePtr)));
	;}
    break;

  case 11:
#line 149 "yacc.y"
    {
		(yyval.NodePtrList) = new std::vector<Node *>();
		(yyval.NodePtrList)->push_back(new Node(EQUAL, 2, new Node((yyvsp[(1) - (4)].sValue), NodeType::Identifier), (yyvsp[(3) - (4)].NodePtr)));
	;}
    break;

  case 12:
#line 157 "yacc.y"
    {
        ValConstant temp;
        temp.Type = ConstantType::Integer;
        temp.iValue = (yyvsp[(1) - (1)].iValue);
        (yyval.NodePtr) = new Node(temp);
    ;}
    break;

  case 13:
#line 164 "yacc.y"
    {
        ValConstant temp;
        temp.Type = ConstantType::Real;
        temp.dValue = (yyvsp[(1) - (1)].dValue);
        (yyval.NodePtr) = new Node(temp);
    ;}
    break;

  case 14:
#line 171 "yacc.y"
    {
        ValConstant temp;
        temp.Type = ConstantType::Char;
		std::cout << (yyvsp[(1) - (1)].cValue) << std::endl;
        temp.cValue = (yyvsp[(1) - (1)].cValue);
        (yyval.NodePtr) = new Node(temp);
    ;}
    break;

  case 15:
#line 179 "yacc.y"
    {
		ValConstant temp;
        temp.Type = ConstantType::String;
		std::cout << (yyvsp[(1) - (1)].sValue) << std::endl;
        temp.sValue = (yyvsp[(1) - (1)].sValue);
        (yyval.NodePtr) = new Node(temp);
	;}
    break;

  case 16:
#line 187 "yacc.y"
    {
		ValConstant temp;
		temp.Type = ConstantType::Boolean;
		std::cout << (yyvsp[(1) - (1)].sValue) << std::endl;
		temp.bValue = (yyvsp[(1) - (1)].sValue);
		(yyval.NodePtr) = new Node(temp);
	;}
    break;

  case 17:
#line 198 "yacc.y"
    {
		(yyval.NodePtr) = (yyvsp[(2) - (2)].NodePtr);
	;}
    break;

  case 18:
#line 201 "yacc.y"
    {(yyval.NodePtr) = NULL;;}
    break;

  case 19:
#line 206 "yacc.y"
    {
		(yyval.NodePtr)->add((yyvsp[(2) - (2)].NodePtr));
	;}
    break;

  case 20:
#line 210 "yacc.y"
    {
		(yyval.NodePtr) = new Node(TYPE_PART, 1, (yyvsp[(1) - (1)].NodePtr));
	;}
    break;

  case 21:
#line 217 "yacc.y"
    {
		(yyval.NodePtr) = new Node(TYPE, 2
					  , new Node((yyvsp[(3) - (4)].sValue), NodeType::Typename)
					  , new Node((yyvsp[(1) - (4)].sValue), NodeType::Identifier));
	;}
    break;

  case 22:
#line 226 "yacc.y"
    {
		(yyval.sValue) = (yyvsp[(1) - (1)].sValue);
	;}
    break;

  case 24:
#line 235 "yacc.y"
    {
		(yyval.sValue) = (yyvsp[(1) - (1)].sValue);
	;}
    break;

  case 25:
#line 239 "yacc.y"
    {
		(yyval.sValue) = (yyvsp[(1) - (1)].sValue);
	;}
    break;

  case 32:
#line 268 "yacc.y"
    {
		(yyval.NodePtrList)->push_back(new Node((yyvsp[(3) - (3)].sValue), NodeType::Identifier));
	;}
    break;

  case 33:
#line 272 "yacc.y"
    {
		(yyval.NodePtrList) = new std::vector<Node *>();
		(yyval.NodePtrList)->push_back(new Node((yyvsp[(1) - (1)].sValue), NodeType::Identifier));
	;}
    break;

  case 34:
#line 280 "yacc.y"
    {
		(yyval.NodePtr) = (yyvsp[(2) - (2)].NodePtr);
	;}
    break;

  case 35:
#line 283 "yacc.y"
    {(yyval.NodePtr) = NULL;;}
    break;

  case 36:
#line 288 "yacc.y"
    {
		(yyval.NodePtr)->add((yyvsp[(2) - (2)].NodePtr));
	;}
    break;

  case 37:
#line 292 "yacc.y"
    {
		(yyval.NodePtr) = new Node(VAR_PART, 1, (yyvsp[(1) - (1)].NodePtr));
	;}
    break;

  case 38:
#line 299 "yacc.y"
    {
		(yyval.NodePtr) = new Node(VAR, (yyvsp[(1) - (4)].NodePtrList));
		(yyval.NodePtr)->add(new Node((yyvsp[(3) - (4)].sValue), NodeType::Typename));
		/*
			Hacking Trick: 最后一个孩子是类型名称，
			在语法树中，不希望类型和变量为sibling，但是父节点Operation无法记录类型名称，
			所以在数组中保留类型名称，在构造语法树时父节点可以访问，
			但是在数目上假装其不存在，这样按for循环绘制就不会绘制出来
		*/
		(yyval.NodePtr)->m_Operation.NumOperands -= 1;
	;}
    break;

  case 39:
#line 314 "yacc.y"
    {
		(yyval.NodePtrList)->push_back((yyvsp[(2) - (2)].NodePtr));
	;}
    break;

  case 40:
#line 318 "yacc.y"
    {
		(yyval.NodePtrList)->push_back((yyvsp[(2) - (2)].NodePtr));
	;}
    break;

  case 41:
#line 322 "yacc.y"
    {
		(yyval.NodePtrList) = new std::vector<Node *>();
		(yyval.NodePtrList)->push_back((yyvsp[(1) - (1)].NodePtr));
	;}
    break;

  case 42:
#line 327 "yacc.y"
    {
		(yyval.NodePtrList) = new std::vector<Node *>();
		(yyval.NodePtrList)->push_back((yyvsp[(1) - (1)].NodePtr));
	;}
    break;

  case 43:
#line 331 "yacc.y"
    {(yyval.NodePtrList) = NULL;;}
    break;

  case 44:
#line 336 "yacc.y"
    {
		if ((yyvsp[(3) - (4)].NodePtr))
			(yyval.NodePtr) = new Node(FUNCTION, 2, (yyvsp[(1) - (4)].NodePtr), (yyvsp[(3) - (4)].NodePtr));
		else
			(yyval.NodePtr) = new Node(FUNCTION, 1, (yyvsp[(1) - (4)].NodePtr));
	;}
    break;

  case 45:
#line 345 "yacc.y"
    {
		if ((yyvsp[(3) - (5)].NodePtr))
		{
			(yyval.NodePtr) = new Node(FUNCTION_HEAD, 2
						  , (yyvsp[(3) - (5)].NodePtr)
						  , new Node((yyvsp[(5) - (5)].sValue), NodeType::Typename));
		}
		else
		{
			(yyval.NodePtr) = new Node(FUNCTION_HEAD, 1
						  , new Node((yyvsp[(5) - (5)].sValue), NodeType::Typename));
		}
		(yyval.NodePtr)->add(new Node((yyvsp[(2) - (5)].sValue), NodeType::Identifier));
		/*
			Hacking Trick: 最后一个孩子是类型名称，
			在语法树中，不希望类型和变量为sibling，但是父节点Operation无法记录类型名称，
			所以在数组中保留类型名称，在构造语法树时父节点可以访问，
			但是在数目上假装其不存在，这样按for循环绘制就不会绘制出来
		*/
		(yyval.NodePtr)->m_Operation.NumOperands -= 1;
	;}
    break;

  case 46:
#line 370 "yacc.y"
    {
		(yyval.NodePtr) = new Node(PROCEDURE, 2, (yyvsp[(1) - (4)].NodePtr), (yyvsp[(3) - (4)].NodePtr));
	;}
    break;

  case 47:
#line 377 "yacc.y"
    {
		if ((yyvsp[(3) - (3)].NodePtr))
		{
			(yyval.NodePtr) = new Node(PROCEDURE_HEAD, 1, (yyvsp[(3) - (3)].NodePtr));
			(yyval.NodePtr)->add(new Node((yyvsp[(2) - (3)].sValue), NodeType::Identifier));
		}
		else
		{
			(yyval.NodePtr) = new Node((yyvsp[(2) - (3)].sValue), NodeType::Identifier);
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

  case 48:
#line 399 "yacc.y"
    { 
		(yyval.NodePtr) = (yyvsp[(2) - (3)].NodePtr);
	;}
    break;

  case 49:
#line 402 "yacc.y"
    {(yyval.NodePtr) = NULL;;}
    break;

  case 50:
#line 406 "yacc.y"
    {
		(yyval.NodePtr)->add((yyvsp[(3) - (3)].NodePtr));
	;}
    break;

  case 51:
#line 410 "yacc.y"
    {
		(yyval.NodePtr) = new Node(PARA_LIST, 1, (yyvsp[(1) - (1)].NodePtr));
	;}
    break;

  case 52:
#line 416 "yacc.y"
    {
		(yyval.NodePtr) = new Node(VAR_PARAM, 1
					  , new Node((yyvsp[(3) - (3)].sValue), NodeType::Typename));
		(yyval.NodePtr)->add((yyvsp[(1) - (3)].NodePtrList));
	;}
    break;

  case 53:
#line 422 "yacc.y"
    {
		(yyval.NodePtr) = new Node(VAL_PARAM, 1
				      , new Node((yyvsp[(3) - (3)].sValue), NodeType::Typename));
		(yyval.NodePtr)->add((yyvsp[(1) - (3)].NodePtrList));
	;}
    break;

  case 54:
#line 430 "yacc.y"
    {
		(yyval.NodePtrList) = (yyvsp[(2) - (2)].NodePtrList);
	;}
    break;

  case 55:
#line 436 "yacc.y"
    {
		(yyval.NodePtrList) = (yyvsp[(1) - (1)].NodePtrList);
	;}
    break;

  case 56:
#line 443 "yacc.y"
    {
		if ((yyvsp[(1) - (1)].NodePtr))
		{
			(yyval.NodePtr) = new Node(ROUTINE_BODY, 1, (yyvsp[(1) - (1)].NodePtr));
		}
		else
		{
			(yyval.NodePtr) = NULL;
		}
	;}
    break;

  case 57:
#line 456 "yacc.y"
    {
		(yyval.NodePtr) = (yyvsp[(2) - (3)].NodePtr);
	;}
    break;

  case 58:
#line 462 "yacc.y"
    {
		if ((yyvsp[(1) - (3)].NodePtr) == NULL)
		{
			(yyval.NodePtr) = (yyvsp[(2) - (3)].NodePtr);
		}
		else
		{
			(yyval.NodePtr) = new Node(SEMI, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(2) - (3)].NodePtr));
		}
	;}
    break;

  case 59:
#line 472 "yacc.y"
    {(yyval.NodePtr) = NULL;;}
    break;

  case 60:
#line 476 "yacc.y"
    {
		ValConstant temp;
		temp.Type = ConstantType::Integer;
		temp.iValue = (yyvsp[(1) - (3)].iValue);
		(yyval.NodePtr) = new Node(LABEL_STMT, 2, new Node(temp), (yyvsp[(3) - (3)].NodePtr));
	;}
    break;

  case 61:
#line 483 "yacc.y"
    {
		(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);
	;}
    break;

  case 62:
#line 488 "yacc.y"
    {(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);;}
    break;

  case 63:
#line 489 "yacc.y"
    {(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);;}
    break;

  case 64:
#line 490 "yacc.y"
    {(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);;}
    break;

  case 65:
#line 491 "yacc.y"
    {(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);;}
    break;

  case 66:
#line 492 "yacc.y"
    {(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);;}
    break;

  case 67:
#line 493 "yacc.y"
    {(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);;}
    break;

  case 68:
#line 494 "yacc.y"
    {(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);;}
    break;

  case 69:
#line 495 "yacc.y"
    {(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);;}
    break;

  case 70:
#line 496 "yacc.y"
    {(yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);;}
    break;

  case 71:
#line 501 "yacc.y"
    {
		(yyval.NodePtr) = new Node(ASSIGN, 2, new Node((yyvsp[(1) - (3)].sValue), NodeType::Identifier), (yyvsp[(3) - (3)].NodePtr));
	;}
    break;

  case 72:
#line 505 "yacc.y"
    {
		(yyval.NodePtr) = new Node(ASSIGN, 2, 
					  new Node(BRACKET, 2, new Node((yyvsp[(1) - (6)].sValue), NodeType::Identifier), (yyvsp[(3) - (6)].NodePtr)),
					  (yyvsp[(6) - (6)].NodePtr));
	;}
    break;

  case 73:
#line 511 "yacc.y"
    {
		(yyval.NodePtr) = new Node(ASSIGN, 2,
					  new Node(DOT, 2, new Node((yyvsp[(1) - (5)].sValue), NodeType::Identifier),
					  				   new Node((yyvsp[(3) - (5)].sValue), NodeType::Identifier))
					  , (yyvsp[(5) - (5)].NodePtr));
	;}
    break;

  case 74:
#line 521 "yacc.y"
    {
		(yyval.NodePtr) = new Node(PROC, 1, new Node((yyvsp[(1) - (1)].sValue), NodeType::Identifier));
	;}
    break;

  case 75:
#line 525 "yacc.y"
    {
		(yyval.NodePtr) = new Node(PROC, 1, new Node((yyvsp[(1) - (4)].sValue), NodeType::Identifier));
		(yyval.NodePtr)->add((yyvsp[(3) - (4)].NodePtrList));
	;}
    break;

  case 76:
#line 530 "yacc.y"
    {
		(yyval.NodePtr) = new Node(SYS_PROC, 1, new Node((yyvsp[(1) - (1)].sValue), NodeType::Identifier));
	;}
    break;

  case 77:
#line 534 "yacc.y"
    {
		(yyval.NodePtr) = new Node(SYS_PROC, 1, new Node((yyvsp[(1) - (4)].sValue), NodeType::Identifier));
		(yyval.NodePtr)->add((yyvsp[(3) - (4)].NodePtrList));
	;}
    break;

  case 79:
#line 543 "yacc.y"
    {
		if ((yyvsp[(5) - (5)].NodePtr))
		{
			(yyval.NodePtr) = new Node(IF, 3, (yyvsp[(2) - (5)].NodePtr), (yyvsp[(4) - (5)].NodePtr), (yyvsp[(5) - (5)].NodePtr));
		}
		else 
		{
			(yyval.NodePtr) = new Node(IF, 2, (yyvsp[(2) - (5)].NodePtr), (yyvsp[(4) - (5)].NodePtr));
		}
	;}
    break;

  case 80:
#line 555 "yacc.y"
    {(yyval.NodePtr) = (yyvsp[(2) - (2)].NodePtr);;}
    break;

  case 81:
#line 556 "yacc.y"
    {(yyval.NodePtr) = NULL;;}
    break;

  case 82:
#line 560 "yacc.y"
    {
		(yyval.NodePtr) = new Node(REPEAT, 2, (yyvsp[(2) - (4)].NodePtr), (yyvsp[(4) - (4)].NodePtr));
	;}
    break;

  case 83:
#line 566 "yacc.y"
    {
		(yyval.NodePtr) = new Node(WHILE, 2, (yyvsp[(2) - (4)].NodePtr), (yyvsp[(4) - (4)].NodePtr));
	;}
    break;

  case 84:
#line 573 "yacc.y"
    {
		(yyval.NodePtr) = new Node((yyvsp[(5) - (8)].iValue), 4, new Node((yyvsp[(2) - (8)].sValue), NodeType::Identifier), 
						(yyvsp[(4) - (8)].NodePtr), (yyvsp[(6) - (8)].NodePtr), (yyvsp[(8) - (8)].NodePtr));
	;}
    break;

  case 85:
#line 579 "yacc.y"
    {(yyval.iValue) = TO;;}
    break;

  case 86:
#line 580 "yacc.y"
    {(yyval.iValue) = DOWNTO;;}
    break;

  case 87:
#line 584 "yacc.y"
    {
		(yyval.NodePtr) = new Node(CASE_STMT, 2, (yyvsp[(2) - (5)].NodePtr), (yyvsp[(4) - (5)].NodePtr));
	;}
    break;

  case 88:
#line 590 "yacc.y"
    {
		(yyval.NodePtr)->add((yyvsp[(2) - (2)].NodePtr));
	;}
    break;

  case 89:
#line 594 "yacc.y"
    {
		(yyval.NodePtr) = new Node(CASE_LIST, 1, (yyvsp[(1) - (1)].NodePtr));
	;}
    break;

  case 90:
#line 600 "yacc.y"
    {
		(yyval.NodePtr) = new Node(CASE, 2, (yyvsp[(1) - (4)].NodePtr), (yyvsp[(3) - (4)].NodePtr));
	;}
    break;

  case 91:
#line 604 "yacc.y"
    {
		(yyval.NodePtr) = new Node(CASE, 2
					  , new Node((yyvsp[(1) - (4)].sValue), NodeType::Identifier)
					  , (yyvsp[(3) - (4)].NodePtr));
	;}
    break;

  case 92:
#line 612 "yacc.y"
    {
		ValConstant temp;
		temp.Type = ConstantType::Integer;
        temp.iValue = (yyvsp[(2) - (2)].iValue);
		(yyval.NodePtr) = new Node(GOTO, 1, new Node(temp));
	;}
    break;

  case 93:
#line 621 "yacc.y"
    {
		(yyval.NodePtrList)->push_back((yyvsp[(3) - (3)].NodePtr));
	;}
    break;

  case 94:
#line 625 "yacc.y"
    {
		(yyval.NodePtrList) = new std::vector<Node*>();
		(yyval.NodePtrList)->push_back((yyvsp[(1) - (1)].NodePtr));
	;}
    break;

  case 95:
#line 632 "yacc.y"
    {
        (yyval.NodePtr) = new Node(GE, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
    ;}
    break;

  case 96:
#line 636 "yacc.y"
    {
        (yyval.NodePtr) = new Node(GT, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
    ;}
    break;

  case 97:
#line 640 "yacc.y"
    {
        (yyval.NodePtr) = new Node(LE, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
    ;}
    break;

  case 98:
#line 644 "yacc.y"
    {
        (yyval.NodePtr) = new Node(LT, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
    ;}
    break;

  case 99:
#line 648 "yacc.y"
    {
        (yyval.NodePtr) = new Node(EQUAL, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
    ;}
    break;

  case 100:
#line 652 "yacc.y"
    {
        (yyval.NodePtr) = new Node(UNEQUAL, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
    ;}
    break;

  case 101:
#line 656 "yacc.y"
    {
        (yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);
    ;}
    break;

  case 102:
#line 662 "yacc.y"
    {
        (yyval.NodePtr) = new Node(PLUS, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
    ;}
    break;

  case 103:
#line 666 "yacc.y"
    {
        (yyval.NodePtr) = new Node(MINUS, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
    ;}
    break;

  case 104:
#line 670 "yacc.y"
    {
		(yyval.NodePtr) = new Node(OR, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
	;}
    break;

  case 105:
#line 674 "yacc.y"
    {
        (yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);
    ;}
    break;

  case 106:
#line 680 "yacc.y"
    {
        (yyval.NodePtr) = new Node(MUL, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
    ;}
    break;

  case 107:
#line 684 "yacc.y"
    {
        (yyval.NodePtr) = new Node(DIV, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
    ;}
    break;

  case 108:
#line 688 "yacc.y"
    {
        (yyval.NodePtr) = new Node(MOD, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
    ;}
    break;

  case 109:
#line 692 "yacc.y"
    {
		(yyval.NodePtr) = new Node(AND, 2, (yyvsp[(1) - (3)].NodePtr), (yyvsp[(3) - (3)].NodePtr));
	;}
    break;

  case 110:
#line 696 "yacc.y"
    {
        (yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);
    ;}
    break;

  case 111:
#line 702 "yacc.y"
    {
        (yyval.NodePtr) = new Node((yyvsp[(1) - (1)].sValue), NodeType::Identifier);
    ;}
    break;

  case 112:
#line 706 "yacc.y"
    {
		(yyval.NodePtr) = new Node(FUNCT, 1
					  , new Node((yyvsp[(1) - (4)].sValue), NodeType::Identifier));
		(yyval.NodePtr)->add((yyvsp[(3) - (4)].NodePtrList));
	;}
    break;

  case 113:
#line 712 "yacc.y"
    {
		(yyval.NodePtr) = new Node(SYS_FUNCT, 1
					  , new Node((yyvsp[(1) - (1)].sValue), NodeType::Identifier));
	;}
    break;

  case 114:
#line 717 "yacc.y"
    {
		(yyval.NodePtr) = new Node(SYS_FUNCT, 1
					  , new Node((yyvsp[(1) - (4)].sValue), NodeType::Identifier));
		(yyval.NodePtr)->add((yyvsp[(3) - (4)].NodePtrList));
	;}
    break;

  case 115:
#line 723 "yacc.y"
    {
        (yyval.NodePtr) = (yyvsp[(1) - (1)].NodePtr);
    ;}
    break;

  case 116:
#line 727 "yacc.y"
    {
        (yyval.NodePtr) = (yyvsp[(2) - (3)].NodePtr);
    ;}
    break;

  case 117:
#line 731 "yacc.y"
    {
		(yyval.NodePtr) = new Node(NOT, 1, (yyvsp[(2) - (2)].NodePtr));
	;}
    break;

  case 118:
#line 735 "yacc.y"
    {
		(yyval.NodePtr) = new Node(MINUS, 1, (yyvsp[(2) - (2)].NodePtr));
	;}
    break;

  case 119:
#line 739 "yacc.y"
    {
		(yyval.NodePtr) = new Node(BRACKET, 2
					  , new Node((yyvsp[(1) - (4)].sValue), NodeType::Identifier)
					  , (yyvsp[(3) - (4)].NodePtr));
	;}
    break;

  case 120:
#line 745 "yacc.y"
    {
		(yyval.NodePtr) = new Node(DOT, 2
					  , new Node((yyvsp[(1) - (3)].sValue), NodeType::Identifier)
					  , new Node((yyvsp[(3) - (3)].sValue), NodeType::Identifier));
	;}
    break;

  case 121:
#line 753 "yacc.y"
    {
		(yyval.NodePtrList)->push_back((yyvsp[(3) - (3)].NodePtr));
	;}
    break;

  case 122:
#line 757 "yacc.y"
    {
		(yyval.NodePtrList) = new std::vector<Node *>();
		(yyval.NodePtrList)->push_back((yyvsp[(1) - (1)].NodePtr));
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 2643 "yacc.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


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
		      yytoken, &yylval);
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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


#line 762 "yacc.y"

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
