/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "parser.ypp"

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <typeinfo>

#include <fstream>

#include <set>

#include "AllNodes.hpp"
#include "AllTypes.hpp"
#include "VisitorNodeDisplay.hpp"
#include "VisitorNodeSimplify.hpp"
#include "VisitorNodeTyper.hpp"
#include "VisitorNodeLlvm.hpp"
#include "Symtab.hpp"
#include "Argument.hpp"

#include "Class.hpp"
#include "Interface.hpp"

#include "runtime.hpp"

#include <llvm/Support/raw_os_ostream.h>

extern std::set<std::string> type_identifiers;

#pragma GCC diagnostic ignored "-Wwrite-strings"
extern "C" {
    int yylex(void);
}
extern int current_line;
extern int current_char;
extern FILE *out_debug;
void yyerror(char *s, ...)
{
    fprintf(stderr, "Parse ERROR line %d (%d): %s\n", current_line, current_char, s);
}
VisitorNodeDisplay* display_visitor;
VisitorNodeTyper* typer_visitor;
VisitorNodeSimplify* simplify_visitor;
VisitorNodeLlvm* llvm_visitor;

StmBlock* main_block;
StmDecl* main_func;

Class* last_class = 0;
Interface* last_interface = 0;

void process_stm(Stm* stm) {
    main_block->addStatement(stm);
}

// Class
std::map<std::string, Class*> class_container;
std::map<std::string, Interface*> interface_container;

/* Size of default input buffer. */
#ifndef YY_BUF_SIZE
#ifdef __ia64__
/* On IA-64, the buffer size is 16k, not 8k.
 * Moreover, YY_BUF_SIZE is 2*YY_READ_BUF_SIZE in the general case.
 * Ditto for the __ia64__ case accordingly.
 */
#define YY_BUF_SIZE 32768
#else
#define YY_BUF_SIZE 16384
#endif /* __ia64__ */
#endif
typedef struct yy_buffer_state *YY_BUFFER_STATE;

YY_BUFFER_STATE yy_create_buffer (FILE *file,int size  );
void yy_switch_to_buffer (YY_BUFFER_STATE new_buffer  );
void yypush_buffer_state (YY_BUFFER_STATE new_buffer  );

std::vector<std::string>* include_path;
std::set<std::string>*    included;

FILE* open_from_path(std::string file_name, std::vector<std::string>* path) {
    std::vector<std::string>::iterator it;
    FILE* fp = 0;
    for (it = path->begin(); it != path->end(); it++)
    {
        fp = fopen(((*it) + file_name).c_str(), "r");
        // Get realpath of file, if already included, return null;
        if (fp)
        {
            if (included->find(realpath(((*it) + file_name).c_str(), 0)) != included->end())
            {
                return 0;
            }
            included->insert(realpath(((*it) + file_name).c_str(), 0));
            break;
        }
    }
    return fp;
}

FILE* file_to_parse;
void set_file_to_parse(FILE* file) {
    // TODO Write somewhere in which file we are for error messages
    YY_BUFFER_STATE new_buf = yy_create_buffer(file, YY_BUF_SIZE);
    yypush_buffer_state(new_buf);
    yy_switch_to_buffer(new_buf);
}

struct s_class_attr {
    char* name;
    Type* type;
    std::vector<Argument*>* args;
    Stm* body;
    int method_state;       // 0: normal, 1: static, 2: virtual
};



/* Line 268 of yacc.c  */
#line 191 "parser.cpp"

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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     LITERAL_CHAR = 258,
     LITERAL_BYTE = 259,
     LITERAL_SHORT = 260,
     LITERAL_INTEGER = 261,
     LITERAL_LONG = 262,
     LITERAL_FLOAT = 263,
     LITERAL_DOUBLE = 264,
     LITERAL_STRING = 265,
     LITERAL_ASSEMBLY = 266,
     TOK_IDENTIFIER = 267,
     TOK_TYPE_IDENTIFIER = 268,
     TOK_IF = 269,
     TOK_ELSE = 270,
     TOK_SWITCH = 271,
     TOK_CASE = 272,
     TOK_WHILE = 273,
     TOK_DO = 274,
     TOK_FOR = 275,
     TOK_BREAK = 276,
     TOK_CONTINUE = 277,
     TOK_DEFAULT = 278,
     TOK_IMPORT = 279,
     TOK_EXTERN = 280,
     TOK_VIRTUAL = 281,
     TOK_OVERRIDE = 282,
     TOK_STATIC = 283,
     TOK_EXTENDS = 284,
     TOK_IMPLEMENTS = 285,
     TOK_VAR = 286,
     TOK_CLASS = 287,
     TOK_INTERFACE = 288,
     TOK_BOOL = 289,
     TOK_CHAR = 290,
     TOK_BYTE = 291,
     TOK_SHORT = 292,
     TOK_INT = 293,
     TOK_LONG = 294,
     TOK_FLOAT = 295,
     TOK_DOUBLE = 296,
     TOK_STRING = 297,
     TOK_VOID = 298,
     TOK_TRUE = 299,
     TOK_FALSE = 300,
     TOK_RETURN = 301,
     TOK_ASSIGN = 302,
     TOK_ADD_ASSIGN = 303,
     TOK_SUB_ASSIGN = 304,
     TOK_MUL_ASSIGN = 305,
     TOK_DIV_ASSIGN = 306,
     TOK_MOD_ASSIGN = 307,
     TOK_B_AND_ASSIGN = 308,
     TOK_B_OR_ASSIGN = 309,
     TOK_B_XOR_ASSIGN = 310,
     TOK_SHL_ASSIGN = 311,
     TOK_SHR_ASSIGN = 312,
     TOK_ASHR_ASSIGN = 313,
     TOK_INC = 314,
     TOK_DEC = 315,
     TOK_EQ = 316,
     TOK_NEQ = 317,
     TOK_LT = 318,
     TOK_LTE = 319,
     TOK_GT = 320,
     TOK_GTE = 321,
     TOK_AND = 322,
     TOK_OR = 323,
     TOK_SHL = 324,
     TOK_SHR = 325,
     TOK_ASHR = 326,
     IFX = 327
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 205 "parser.ypp"

    int                      num;
    char*                    str;
    Expr*                    expr;
    Stm*                     stm;
    StmBlock*                block;
    std::vector<Argument*>*  argdeflst;
    Type*                    type;
    StmDecl*                 decl;
    StmSwitch*               stm_switch;
    ExprCall*                arglst;
    ExprArray*               array;
    Class*                   class_obj;
    Interface*               interface_obj;
    s_class_attr             class_attr;



/* Line 293 of yacc.c  */
#line 318 "parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 330 "parser.cpp"

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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
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
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  110
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   905

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  176
/* YYNRULES -- Number of states.  */
#define YYNSTATES  378

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   327

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    87,     2,     2,     2,    89,    90,     2,
      73,    74,    82,    84,    79,    85,    83,    88,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    78,    75,
       2,     2,     2,    93,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    80,     2,    81,    91,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    76,    92,    77,    86,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     8,    14,    22,    28,    36,    46,
      50,    53,    55,    58,    60,    63,    71,    76,    81,    86,
      91,    95,   101,   107,   113,   119,   124,   128,   131,   134,
     137,   141,   143,   145,   147,   149,   151,   153,   155,   157,
     159,   161,   163,   165,   171,   177,   181,   187,   194,   201,
     207,   214,   221,   228,   236,   244,   246,   248,   254,   256,
     258,   261,   267,   274,   280,   282,   286,   290,   292,   295,
     299,   305,   312,   319,   326,   334,   342,   349,   357,   365,
     372,   380,   388,   391,   396,   398,   400,   404,   409,   411,
     413,   415,   417,   419,   421,   423,   425,   427,   429,   431,
     433,   435,   437,   439,   441,   443,   445,   447,   449,   451,
     455,   459,   465,   469,   471,   475,   477,   481,   483,   488,
     493,   497,   501,   505,   508,   511,   513,   516,   519,   522,
     525,   528,   531,   533,   537,   541,   545,   547,   551,   555,
     557,   561,   565,   569,   571,   575,   579,   583,   587,   589,
     593,   597,   599,   603,   605,   609,   611,   615,   617,   621,
     623,   627,   629,   635,   637,   641,   645,   649,   653,   657,
     661,   665,   669,   673,   677,   681,   685
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      95,     0,    -1,    95,   109,    -1,   109,    -1,    14,    73,
     141,    74,   109,    -1,    14,    73,   141,    74,   109,    15,
     109,    -1,    18,    73,   141,    74,   109,    -1,    19,   109,
      18,    73,   141,    74,    75,    -1,    20,    73,   141,    75,
     141,    75,   141,    74,   109,    -1,    76,   101,    77,    -1,
      76,    77,    -1,   109,    -1,   101,   109,    -1,    75,    -1,
     141,    75,    -1,    16,    73,   141,    74,    76,   104,    77,
      -1,    17,     4,    78,   101,    -1,    17,     5,    78,   101,
      -1,    17,     6,    78,   101,    -1,    17,     7,    78,   101,
      -1,    23,    78,   101,    -1,   104,    17,     4,    78,   101,
      -1,   104,    17,     5,    78,   101,    -1,   104,    17,     6,
      78,   101,    -1,   104,    17,     7,    78,   101,    -1,   104,
      23,    78,   101,    -1,    46,   141,    75,    -1,    46,    75,
      -1,    21,    75,    -1,    22,    75,    -1,    24,    12,    75,
      -1,   102,    -1,   108,    -1,   100,    -1,    96,    -1,    98,
      -1,    99,    -1,    97,    -1,   103,    -1,   105,    -1,   106,
      -1,   107,    -1,   110,    -1,   120,    12,    47,   141,    75,
      -1,    31,    12,    47,   141,    75,    -1,   120,    12,    75,
      -1,   120,    12,    73,    74,   100,    -1,   120,    12,    73,
      43,    74,   100,    -1,   120,    12,    73,   119,    74,   100,
      -1,   120,    12,    73,    74,    75,    -1,   120,    12,    73,
      43,    74,    75,    -1,   120,    12,    73,   119,    74,    75,
      -1,   120,    25,    12,    73,    74,    75,    -1,   120,    25,
      12,    73,    43,    74,    75,    -1,   120,    25,    12,    73,
     119,    74,    75,    -1,   115,    -1,   111,    -1,    33,   112,
      76,   113,    77,    -1,    12,    -1,   114,    -1,   113,   114,
      -1,   120,    12,    73,    74,    75,    -1,   120,    12,    73,
     119,    74,    75,    -1,    32,   116,    76,   117,    77,    -1,
      12,    -1,    12,    29,    13,    -1,    12,    30,    13,    -1,
     118,    -1,   117,   118,    -1,   120,    12,    75,    -1,   120,
      12,    73,    74,   100,    -1,   120,    12,    73,    43,    74,
     100,    -1,   120,    12,    73,   119,    74,   100,    -1,    26,
     120,    12,    73,    74,   100,    -1,    26,   120,    12,    73,
      43,    74,   100,    -1,    26,   120,    12,    73,   119,    74,
     100,    -1,    27,   120,    12,    73,    74,   100,    -1,    27,
     120,    12,    73,    43,    74,   100,    -1,    27,   120,    12,
      73,   119,    74,   100,    -1,    28,   120,    12,    73,    74,
     100,    -1,    28,   120,    12,    73,    43,    74,   100,    -1,
      28,   120,    12,    73,   119,    74,   100,    -1,   120,    12,
      -1,   119,    79,   120,    12,    -1,   121,    -1,    13,    -1,
     120,    80,    81,    -1,   120,    80,     6,    81,    -1,    43,
      -1,    34,    -1,    36,    -1,    37,    -1,    38,    -1,    39,
      -1,    40,    -1,    41,    -1,    44,    -1,    45,    -1,   123,
      -1,   124,    -1,     3,    -1,     4,    -1,     5,    -1,     6,
      -1,     7,    -1,     8,    -1,     9,    -1,    10,    -1,    12,
      -1,    13,    73,    74,    -1,    73,   141,    74,    -1,    76,
     120,    82,   141,    77,    -1,    76,   125,    77,    -1,   141,
      -1,   125,    79,   141,    -1,   141,    -1,   126,    79,   141,
      -1,   122,    -1,   127,    80,   141,    81,    -1,   127,    73,
     126,    74,    -1,   127,    73,    74,    -1,   127,    83,    12,
      -1,    13,    83,    12,    -1,   127,    59,    -1,   127,    60,
      -1,   127,    -1,    59,   128,    -1,    60,   128,    -1,    84,
     128,    -1,    85,   128,    -1,    86,   128,    -1,    87,   128,
      -1,   128,    -1,   129,    82,   128,    -1,   129,    88,   128,
      -1,   129,    89,   128,    -1,   129,    -1,   130,    84,   129,
      -1,   130,    85,   129,    -1,   130,    -1,   131,    69,   130,
      -1,   131,    70,   130,    -1,   131,    71,   130,    -1,   131,
      -1,   132,    63,   131,    -1,   132,    64,   131,    -1,   132,
      65,   131,    -1,   132,    66,   131,    -1,   132,    -1,   133,
      61,   132,    -1,   133,    62,   132,    -1,   133,    -1,   134,
      90,   133,    -1,   134,    -1,   135,    91,   134,    -1,   135,
      -1,   136,    92,   135,    -1,   136,    -1,   137,    67,   136,
      -1,   137,    -1,   138,    68,   137,    -1,   138,    -1,   138,
      93,   141,    78,   139,    -1,   139,    -1,   128,    47,   140,
      -1,   128,    48,   140,    -1,   128,    49,   140,    -1,   128,
      50,   140,    -1,   128,    51,   140,    -1,   128,    52,   140,
      -1,   128,    53,   140,    -1,   128,    54,   140,    -1,   128,
      55,   140,    -1,   128,    56,   140,    -1,   128,    57,   140,
      -1,   128,    58,   140,    -1,   140,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   280,   280,   281,   285,   286,   289,   293,   297,   301,
     302,   306,   307,   311,   312,   316,   320,   321,   322,   323,
     325,   327,   328,   329,   330,   332,   336,   337,   341,   345,
     349,   362,   363,   364,   365,   366,   367,   368,   369,   370,
     371,   372,   373,   377,   378,   379,   380,   381,   382,   383,
     384,   385,   386,   387,   388,   389,   390,   394,   398,   407,
     408,   412,   413,   418,   422,   428,   435,   445,   446,   450,
     451,   452,   453,   454,   455,   456,   457,   458,   459,   460,
     461,   462,   466,   467,   471,   472,   473,   474,   475,   479,
     480,   481,   482,   483,   484,   485,   489,   490,   491,   492,
     493,   494,   495,   496,   497,   498,   499,   500,   501,   502,
     503,   507,   511,   515,   516,   520,   521,   525,   526,   527,
     528,   529,   530,   531,   532,   536,   537,   538,   539,   540,
     541,   542,   546,   547,   548,   549,   553,   554,   555,   559,
     560,   561,   562,   566,   567,   568,   569,   570,   574,   575,
     576,   580,   581,   585,   586,   590,   591,   595,   596,   600,
     601,   605,   606,   610,   611,   612,   613,   614,   615,   616,
     617,   618,   619,   620,   621,   622,   626
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LITERAL_CHAR", "LITERAL_BYTE",
  "LITERAL_SHORT", "LITERAL_INTEGER", "LITERAL_LONG", "LITERAL_FLOAT",
  "LITERAL_DOUBLE", "LITERAL_STRING", "LITERAL_ASSEMBLY", "TOK_IDENTIFIER",
  "TOK_TYPE_IDENTIFIER", "TOK_IF", "TOK_ELSE", "TOK_SWITCH", "TOK_CASE",
  "TOK_WHILE", "TOK_DO", "TOK_FOR", "TOK_BREAK", "TOK_CONTINUE",
  "TOK_DEFAULT", "TOK_IMPORT", "TOK_EXTERN", "TOK_VIRTUAL", "TOK_OVERRIDE",
  "TOK_STATIC", "TOK_EXTENDS", "TOK_IMPLEMENTS", "TOK_VAR", "TOK_CLASS",
  "TOK_INTERFACE", "TOK_BOOL", "TOK_CHAR", "TOK_BYTE", "TOK_SHORT",
  "TOK_INT", "TOK_LONG", "TOK_FLOAT", "TOK_DOUBLE", "TOK_STRING",
  "TOK_VOID", "TOK_TRUE", "TOK_FALSE", "TOK_RETURN", "TOK_ASSIGN",
  "TOK_ADD_ASSIGN", "TOK_SUB_ASSIGN", "TOK_MUL_ASSIGN", "TOK_DIV_ASSIGN",
  "TOK_MOD_ASSIGN", "TOK_B_AND_ASSIGN", "TOK_B_OR_ASSIGN",
  "TOK_B_XOR_ASSIGN", "TOK_SHL_ASSIGN", "TOK_SHR_ASSIGN",
  "TOK_ASHR_ASSIGN", "TOK_INC", "TOK_DEC", "TOK_EQ", "TOK_NEQ", "TOK_LT",
  "TOK_LTE", "TOK_GT", "TOK_GTE", "TOK_AND", "TOK_OR", "TOK_SHL",
  "TOK_SHR", "TOK_ASHR", "IFX", "'('", "')'", "';'", "'{'", "'}'", "':'",
  "','", "'['", "']'", "'*'", "'.'", "'+'", "'-'", "'~'", "'!'", "'/'",
  "'%'", "'&'", "'^'", "'|'", "'?'", "$accept", "program", "stm_if",
  "stm_while", "stm_do", "stm_for", "stm_block", "stm_list", "stm_expr",
  "stm_switch", "list_cases", "stm_return", "stm_break", "stm_continue",
  "stm_import", "statement", "declaration", "interface_declaration",
  "interface_identifier", "interface_element_list", "interface_element",
  "class_declaration", "class_identifier", "class_element_list",
  "class_element", "argument_definition_list", "type_specifier",
  "type_primary", "expr_primary", "allocate_array", "literal_array",
  "array_list", "argument_list", "expr_postfix", "expr_unary", "expr_mul",
  "expr_add", "expr_shift", "expr_comparison", "expr_equal",
  "expr_bitwise_and", "expr_bitwise_xor", "expr_bitwise_or",
  "expr_logical_and", "expr_logical_or", "expr_conditional", "expr_assign",
  "expression", 0
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
     325,   326,   327,    40,    41,    59,   123,   125,    58,    44,
      91,    93,    42,    46,    43,    45,   126,    33,    47,    37,
      38,    94,   124,    63
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    94,    95,    95,    96,    96,    97,    98,    99,   100,
     100,   101,   101,   102,   102,   103,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   105,   105,   106,   107,
     108,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   111,   112,   113,
     113,   114,   114,   115,   116,   116,   116,   117,   117,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   119,   119,   120,   120,   120,   120,   120,   121,
     121,   121,   121,   121,   121,   121,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   123,   124,   125,   125,   126,   126,   127,   127,   127,
     127,   127,   127,   127,   127,   128,   128,   128,   128,   128,
     128,   128,   129,   129,   129,   129,   130,   130,   130,   131,
     131,   131,   131,   132,   132,   132,   132,   132,   133,   133,
     133,   134,   134,   135,   135,   136,   136,   137,   137,   138,
     138,   139,   139,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   141
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     5,     7,     5,     7,     9,     3,
       2,     1,     2,     1,     2,     7,     4,     4,     4,     4,
       3,     5,     5,     5,     5,     4,     3,     2,     2,     2,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     5,     3,     5,     6,     6,     5,
       6,     6,     6,     7,     7,     1,     1,     5,     1,     1,
       2,     5,     6,     5,     1,     3,     3,     1,     2,     3,
       5,     6,     6,     6,     7,     7,     6,     7,     7,     6,
       7,     7,     2,     4,     1,     1,     3,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     5,     3,     1,     3,     1,     3,     1,     4,     4,
       3,     3,     3,     2,     2,     1,     2,     2,     2,     2,
       2,     2,     1,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     5,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   100,   101,   102,   103,   104,   105,   106,   107,   108,
      85,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,    90,    91,    92,    93,    94,    95,    88,
      96,    97,     0,     0,     0,     0,    13,     0,     0,     0,
       0,     0,     0,    34,    37,    35,    36,    33,    31,    38,
      39,    40,    41,    32,     3,    42,    56,    55,     0,    84,
     117,    98,    99,   125,   132,   136,   139,   143,   148,   151,
     153,   155,   157,   159,   161,   163,   176,     0,     0,     0,
       0,     0,     0,     0,     0,    28,    29,     0,     0,    64,
       0,    58,     0,     0,    27,     0,     0,   126,   127,     0,
      10,     0,    11,     0,     0,   113,   128,   129,   130,   131,
       1,     2,     0,     0,     0,   123,   124,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    14,   109,   122,     0,     0,     0,     0,     0,
      30,     0,     0,     0,     0,     0,     0,   113,    26,   110,
       9,    12,     0,   112,     0,     0,     0,    45,     0,     0,
      86,   120,     0,   115,     0,   121,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   133,   134,
     135,   132,   137,   138,   140,   141,   142,   144,   145,   146,
     147,   149,   150,   152,   154,   156,   158,   160,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    85,     0,     0,
       0,     0,    67,     0,     0,    59,     0,     0,   114,     0,
      88,     0,     0,     0,     0,    87,   119,     0,   118,     0,
       4,     0,     6,     0,     0,    44,     0,     0,     0,    63,
      68,     0,    57,    60,     0,   111,    43,     0,    49,     0,
      46,     0,     0,    82,    88,     0,     0,   116,   162,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    69,
       0,    50,    47,    51,    48,     0,     0,    52,     0,     5,
       0,     0,     0,     0,     0,     0,     0,    15,     7,     0,
       0,     0,     0,    88,     0,     0,     0,     0,    83,    53,
      54,     0,     0,     0,     0,    20,     0,     0,     0,     0,
       0,     0,    88,     0,     0,    88,     0,     0,    88,     0,
       0,     0,    70,     0,    61,     0,    16,    17,    18,    19,
       0,     0,     0,     0,    25,     8,     0,    73,     0,     0,
      76,     0,     0,    79,     0,    71,    72,    62,    21,    22,
      23,    24,    74,    75,    77,    78,    80,    81
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    42,    43,    44,    45,    46,    47,   101,    48,    49,
     282,    50,    51,    52,    53,   102,    55,    56,    92,   234,
     235,    57,    90,   231,   232,   242,    58,    59,    60,    61,
      62,   104,   182,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -238
static const yytype_int16 yypact[] =
{
     627,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
     -45,   -63,   -52,   -33,   627,    19,    38,    45,    25,    98,
     114,   118,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,   671,   759,   759,   759,  -238,   457,   759,   759,
     759,   759,   372,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,    -1,  -238,
    -238,  -238,  -238,   262,   471,   -80,   104,   -15,    52,   129,
      49,    51,   109,   137,   -61,  -238,  -238,   131,   141,   206,
     759,   759,   759,   202,   759,  -238,  -238,   159,   190,   167,
     163,  -238,   170,   -45,  -238,   253,   176,  -238,  -238,   179,
    -238,   542,  -238,    -6,     3,   131,  -238,  -238,  -238,  -238,
    -238,  -238,   -42,   243,    -3,  -238,  -238,   715,   759,   257,
     759,   759,   759,   759,   759,   759,   759,   759,   759,   759,
     759,   759,   759,   759,   759,   759,   759,   759,   759,   759,
     759,   759,   759,   759,   759,   759,   759,   759,   759,   759,
     759,   759,  -238,  -238,  -238,   196,   197,   198,   200,   207,
    -238,   759,   264,   270,   401,   192,     5,  -238,  -238,  -238,
    -238,  -238,   759,  -238,   759,   759,     9,  -238,   211,   205,
    -238,  -238,   -38,  -238,   214,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,   -80,   -80,   104,   104,   104,   -15,   -15,   -15,
     -15,    52,    52,   129,    49,    51,   109,   137,   210,   627,
     209,   627,   759,   759,   224,  -238,  -238,  -238,   192,   192,
     192,   110,  -238,     1,   173,  -238,     4,   223,  -238,   227,
     235,   124,   -35,     6,   204,  -238,  -238,   759,  -238,   759,
     296,    12,  -238,   240,   241,  -238,     8,    13,    14,  -238,
    -238,    70,  -238,  -238,   242,  -238,  -238,   147,  -238,   457,
    -238,   149,   192,  -238,   244,   245,   -21,  -238,  -238,   627,
     128,   239,    34,   248,   759,   246,   251,   254,   267,  -238,
     321,  -238,  -238,  -238,  -238,    15,   255,  -238,   258,  -238,
     250,   265,   266,   272,   627,   152,   273,  -238,  -238,   278,
     773,   814,   824,   279,   256,   -11,   261,    26,  -238,  -238,
    -238,   627,   627,   627,   627,   627,   285,   287,   288,   289,
     627,   627,   282,   256,    29,   299,   256,    33,   300,   256,
      35,   256,  -238,   256,  -238,   308,   627,   627,   627,   627,
     627,   627,   627,   627,   627,  -238,   256,  -238,   256,   256,
    -238,   256,   256,  -238,   256,  -238,  -238,  -238,   627,   627,
     627,   627,  -238,  -238,  -238,  -238,  -238,  -238
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -238,  -238,  -238,  -238,  -238,  -238,  -237,   552,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,     0,  -238,  -238,  -238,  -238,
     153,  -238,  -238,  -238,   158,  -221,   -36,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,    32,   113,    46,    20,   123,   252,
     260,   249,   271,   269,  -238,   150,   384,   -20
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      54,   103,   132,   179,   270,   175,   112,   150,   133,   134,
      80,   112,    96,   261,    83,    99,   264,   105,   273,   113,
     285,    81,   227,   276,   113,   286,   287,   318,    78,   280,
     292,   176,   151,   177,   294,   281,   246,    87,    79,   271,
      82,   247,   111,    22,   272,    23,    24,    25,    26,    27,
      28,   305,   240,   298,   137,   138,   139,   306,   272,   166,
     155,   156,   157,   343,   159,    97,    98,   315,   272,   317,
     106,   107,   108,   109,   114,   167,   172,   342,   180,   114,
     173,   114,   174,   241,   114,   114,   114,   172,   114,   334,
     337,   340,    84,   114,   114,   114,   357,   183,   184,   360,
     345,   171,   363,   358,   365,   272,   366,   361,   272,   364,
      88,   307,   272,    85,   272,   140,   141,   142,   143,   372,
      86,   373,   374,   227,   375,   376,    89,   377,   233,   236,
      91,   218,   300,   301,   302,   303,   228,   229,   230,   146,
     243,   224,   147,   288,    22,   289,    23,    24,    25,    26,
      27,    28,   237,    29,   238,   239,   326,   327,   328,   329,
     207,   208,   209,   210,   198,   199,   200,   201,   201,   201,
     201,   201,   201,   201,   201,   201,   201,   201,   201,   201,
     201,   201,   201,   204,   205,   206,   227,   259,   135,   136,
     144,   145,   256,   257,   258,   233,   162,   163,   236,   268,
     269,   148,   253,   254,   149,   227,   152,    22,   243,    23,
      24,    25,    26,    27,    28,   153,    29,   227,   154,   250,
     158,   252,   291,   269,   293,   269,    22,   277,    23,    24,
      25,    26,    27,    28,   160,    29,   295,   161,    22,   164,
      23,    24,    25,    26,    27,    28,   165,   274,   202,   203,
     262,   168,   243,   169,   243,   178,     1,     2,     3,     4,
       5,     6,     7,     8,   309,     9,    10,   211,   212,   185,
     219,   220,   221,   222,   243,   243,   243,   225,   275,   299,
     227,   201,   223,   226,   244,   251,   245,    22,   249,    23,
      24,    25,    26,    27,    28,   248,    29,    30,    31,   255,
     265,    22,   266,    23,    24,    25,    26,    27,    28,   267,
     313,   279,    33,    34,   283,   290,   284,   304,   296,   310,
     297,   115,   116,   308,   311,   171,    35,   312,   321,    95,
     319,   355,   269,   320,   227,   117,   344,    38,    39,    40,
      41,   314,   118,   322,   323,   119,   171,   171,   171,   171,
     324,   330,   331,   341,   171,    22,   356,    23,    24,    25,
      26,    27,    28,   350,    29,   351,   352,   353,   171,   171,
     171,   171,   110,   359,   362,     1,     2,     3,     4,     5,
       6,     7,     8,   367,     9,    10,    11,   263,    12,   260,
      13,    14,    15,    16,    17,   316,    18,   215,   213,   278,
       0,     0,     0,    19,    20,    21,    22,   214,    23,    24,
      25,    26,    27,    28,   227,    29,    30,    31,    32,   217,
     216,     0,     0,     0,     0,     0,     0,   228,   229,   230,
       0,    33,    34,     0,     0,    22,     0,    23,    24,    25,
      26,    27,    28,     0,    29,    35,     0,    36,    37,     0,
       0,     0,     0,     0,     0,     0,    38,    39,    40,    41,
       1,     2,     3,     4,     5,     6,     7,     8,     0,     9,
      10,    11,     0,    12,     0,    13,    14,    15,    16,    17,
       0,    18,     0,     0,     0,     0,     0,     0,    19,    20,
      21,    22,     0,    23,    24,    25,    26,    27,    28,     0,
      29,    30,    31,    32,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,    33,    34,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
      35,     0,    36,    37,   100,     0,     0,     0,     0,     0,
       0,    38,    39,    40,    41,     1,     2,     3,     4,     5,
       6,     7,     8,     0,     9,    10,    11,     0,    12,     0,
      13,    14,    15,    16,    17,     0,    18,     0,     0,     0,
       0,     0,     0,    19,    20,    21,    22,     0,    23,    24,
      25,    26,    27,    28,     0,    29,    30,    31,    32,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    33,    34,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    35,     0,    36,    37,   170,
       0,     0,     0,     0,     0,     0,    38,    39,    40,    41,
       1,     2,     3,     4,     5,     6,     7,     8,     0,     9,
      10,    11,     0,    12,     0,    13,    14,    15,    16,    17,
       0,    18,     0,     0,     0,     0,     0,     0,    19,    20,
      21,    22,     0,    23,    24,    25,    26,    27,    28,     0,
      29,    30,    31,    32,     1,     2,     3,     4,     5,     6,
       7,     8,     0,     9,    93,     0,    33,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      35,     0,    36,    37,     0,     0,     0,     0,     0,     0,
       0,    38,    39,    40,    41,    30,    31,     0,     1,     2,
       3,     4,     5,     6,     7,     8,     0,     9,    93,     0,
      33,    34,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    35,     0,    94,    95,     0,     0,
       0,     0,     0,     0,     0,    38,    39,    40,    41,    30,
      31,     0,     1,     2,     3,     4,     5,     6,     7,     8,
       0,     9,    93,     0,    33,    34,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   227,     0,    35,   181,
       0,    95,     0,     0,     0,     0,     0,     0,     0,    38,
      39,    40,    41,    30,    31,     0,     0,    22,     0,    23,
      24,    25,    26,    27,    28,     0,   332,     0,    33,    34,
       0,     0,     0,     0,     0,     0,     0,   227,     0,     0,
       0,     0,    35,     0,     0,    95,     0,   227,     0,     0,
       0,     0,     0,    38,    39,    40,    41,   333,    22,     0,
      23,    24,    25,    26,    27,    28,   325,   335,    22,     0,
      23,    24,    25,    26,    27,    28,     0,   338,     0,     0,
       0,     0,     0,   346,   347,   348,   349,     0,     0,     0,
       0,     0,   354,     0,     0,     0,     0,     0,   336,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   339,     0,
       0,     0,   368,   369,   370,   371
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-238))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       0,    37,    82,     6,   241,    47,    12,    68,    88,    89,
      73,    12,    32,    12,    14,    35,    12,    37,    12,    25,
      12,    73,    13,   244,    25,    12,    12,    12,    73,    17,
     267,    73,    93,    75,   271,    23,    74,    12,    83,    74,
      73,    79,    42,    34,    79,    36,    37,    38,    39,    40,
      41,    17,    43,    74,    69,    70,    71,    23,    79,    95,
      80,    81,    82,    74,    84,    33,    34,   288,    79,   290,
      38,    39,    40,    41,    80,    95,    82,   314,    81,    80,
      77,    80,    79,    74,    80,    80,    80,    82,    80,   310,
     311,   312,    73,    80,    80,    80,   333,   117,   118,   336,
      74,   101,   339,    74,   341,    79,   343,    74,    79,    74,
      12,    77,    79,    75,    79,    63,    64,    65,    66,   356,
      75,   358,   359,    13,   361,   362,    12,   364,   164,   165,
      12,   151,     4,     5,     6,     7,    26,    27,    28,    90,
     176,   161,    91,    73,    34,    75,    36,    37,    38,    39,
      40,    41,   172,    43,   174,   175,     4,     5,     6,     7,
     140,   141,   142,   143,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   137,   138,   139,    13,    77,    84,    85,
      61,    62,   228,   229,   230,   231,    29,    30,   234,    75,
      76,    92,   222,   223,    67,    13,    75,    34,   244,    36,
      37,    38,    39,    40,    41,    74,    43,    13,    12,   219,
      18,   221,    75,    76,    75,    76,    34,   247,    36,    37,
      38,    39,    40,    41,    75,    43,   272,    47,    34,    76,
      36,    37,    38,    39,    40,    41,    76,    43,   135,   136,
      77,    75,   288,    74,   290,    12,     3,     4,     5,     6,
       7,     8,     9,    10,   284,    12,    13,   144,   145,    12,
      74,    74,    74,    73,   310,   311,   312,    13,    74,   279,
      13,   249,    75,    13,    73,    76,    81,    34,    78,    36,
      37,    38,    39,    40,    41,    81,    43,    44,    45,    75,
      77,    34,    75,    36,    37,    38,    39,    40,    41,    74,
      43,    15,    59,    60,    74,    73,    75,    78,    74,    73,
      75,    59,    60,    75,    73,   325,    73,    73,    78,    76,
      75,   331,    76,    75,    13,    73,    75,    84,    85,    86,
      87,    74,    80,    78,    78,    83,   346,   347,   348,   349,
      78,    78,    74,    74,   354,    34,    74,    36,    37,    38,
      39,    40,    41,    78,    43,    78,    78,    78,   368,   369,
     370,   371,     0,    74,    74,     3,     4,     5,     6,     7,
       8,     9,    10,    75,    12,    13,    14,   234,    16,   231,
      18,    19,    20,    21,    22,    74,    24,   148,   146,   249,
      -1,    -1,    -1,    31,    32,    33,    34,   147,    36,    37,
      38,    39,    40,    41,    13,    43,    44,    45,    46,   150,
     149,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,
      -1,    59,    60,    -1,    -1,    34,    -1,    36,    37,    38,
      39,    40,    41,    -1,    43,    73,    -1,    75,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    86,    87,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    12,
      13,    14,    -1,    16,    -1,    18,    19,    20,    21,    22,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,
      33,    34,    -1,    36,    37,    38,    39,    40,    41,    -1,
      43,    44,    45,    46,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,    59,    60,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      73,    -1,    75,    76,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    85,    86,    87,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    12,    13,    14,    -1,    16,    -1,
      18,    19,    20,    21,    22,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    32,    33,    34,    -1,    36,    37,
      38,    39,    40,    41,    -1,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    -1,    75,    76,    77,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    86,    87,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    12,
      13,    14,    -1,    16,    -1,    18,    19,    20,    21,    22,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,
      33,    34,    -1,    36,    37,    38,    39,    40,    41,    -1,
      43,    44,    45,    46,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    12,    13,    -1,    59,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    -1,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    85,    86,    87,    44,    45,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    12,    13,    -1,
      59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    -1,    75,    76,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    85,    86,    87,    44,
      45,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    12,    13,    -1,    59,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    13,    -1,    73,    74,
      -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      85,    86,    87,    44,    45,    -1,    -1,    34,    -1,    36,
      37,    38,    39,    40,    41,    -1,    43,    -1,    59,    60,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    13,    -1,    -1,
      -1,    -1,    73,    -1,    -1,    76,    -1,    13,    -1,    -1,
      -1,    -1,    -1,    84,    85,    86,    87,    74,    34,    -1,
      36,    37,    38,    39,    40,    41,   304,    43,    34,    -1,
      36,    37,    38,    39,    40,    41,    -1,    43,    -1,    -1,
      -1,    -1,    -1,   321,   322,   323,   324,    -1,    -1,    -1,
      -1,    -1,   330,    -1,    -1,    -1,    -1,    -1,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,
      -1,    -1,   350,   351,   352,   353
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    12,
      13,    14,    16,    18,    19,    20,    21,    22,    24,    31,
      32,    33,    34,    36,    37,    38,    39,    40,    41,    43,
      44,    45,    46,    59,    60,    73,    75,    76,    84,    85,
      86,    87,    95,    96,    97,    98,    99,   100,   102,   103,
     105,   106,   107,   108,   109,   110,   111,   115,   120,   121,
     122,   123,   124,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,    73,    83,
      73,    73,    73,   109,    73,    75,    75,    12,    12,    12,
     116,    12,   112,    13,    75,    76,   141,   128,   128,   141,
      77,   101,   109,   120,   125,   141,   128,   128,   128,   128,
       0,   109,    12,    25,    80,    59,    60,    73,    80,    83,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    82,    88,    89,    84,    85,    69,    70,    71,
      63,    64,    65,    66,    61,    62,    90,    91,    92,    67,
      68,    93,    75,    74,    12,   141,   141,   141,    18,   141,
      75,    47,    29,    30,    76,    76,   120,   141,    75,    74,
      77,   109,    82,    77,    79,    47,    73,    75,    12,     6,
      81,    74,   126,   141,   141,    12,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   128,   128,
     128,   128,   129,   129,   130,   130,   130,   131,   131,   131,
     131,   132,   132,   133,   134,   135,   136,   137,   141,    74,
      74,    74,    73,    75,   141,    13,    13,    13,    26,    27,
      28,   117,   118,   120,   113,   114,   120,   141,   141,   141,
      43,    74,   119,   120,    73,    81,    74,    79,    81,    78,
     109,    76,   109,   141,   141,    75,   120,   120,   120,    77,
     118,    12,    77,   114,    12,    77,    75,    74,    75,    76,
     100,    74,    79,    12,    43,    74,   119,   141,   139,    15,
      17,    23,   104,    74,    75,    12,    12,    12,    73,    75,
      73,    75,   100,    75,   100,   120,    74,    75,    74,   109,
       4,     5,     6,     7,    78,    17,    23,    77,    75,   141,
      73,    73,    73,    43,    74,   119,    74,   119,    12,    75,
      75,    78,    78,    78,    78,   101,     4,     5,     6,     7,
      78,    74,    43,    74,   119,    43,    74,   119,    43,    74,
     119,    74,   100,    74,    75,    74,   101,   101,   101,   101,
      78,    78,    78,    78,   101,   109,    74,   100,    74,    74,
     100,    74,    74,   100,    74,   100,   100,    75,   101,   101,
     101,   101,   100,   100,   100,   100,   100,   100
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
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


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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

/* Line 1806 of yacc.c  */
#line 280 "parser.ypp"
    {process_stm((yyvsp[(2) - (2)].stm));}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 281 "parser.ypp"
    {process_stm((yyvsp[(1) - (1)].stm));}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 285 "parser.ypp"
    {(yyval.stm) = new StmIf((yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].stm), 0);}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 286 "parser.ypp"
    {(yyval.stm) = new StmIf((yyvsp[(3) - (7)].expr), (yyvsp[(5) - (7)].stm), (yyvsp[(7) - (7)].stm));}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 289 "parser.ypp"
    {(yyval.stm) = new StmWhile((yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].stm));}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 293 "parser.ypp"
    {(yyval.stm) = new StmDo((yyvsp[(5) - (7)].expr), (yyvsp[(2) - (7)].stm));}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 297 "parser.ypp"
    {(yyval.stm) = new StmFor((yyvsp[(3) - (9)].expr), (yyvsp[(5) - (9)].expr), (yyvsp[(7) - (9)].expr), (yyvsp[(9) - (9)].stm));}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 301 "parser.ypp"
    {(yyval.stm) = (yyvsp[(2) - (3)].block);}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 302 "parser.ypp"
    {(yyval.stm) = new StmBlock();}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 306 "parser.ypp"
    {(yyval.block) = new StmBlock((yyvsp[(1) - (1)].stm));}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 307 "parser.ypp"
    {(yyvsp[(1) - (2)].block)->addStatement((yyvsp[(2) - (2)].stm));}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 311 "parser.ypp"
    {(yyval.stm) = new StmNop();}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 312 "parser.ypp"
    {(yyval.stm) = new StmExpr((yyvsp[(1) - (2)].expr));}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 316 "parser.ypp"
    {(yyvsp[(6) - (7)].stm_switch)->setCondition((yyvsp[(3) - (7)].expr));; (yyval.stm) = (yyvsp[(6) - (7)].stm_switch);}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 320 "parser.ypp"
    {(yyval.stm_switch) = new StmSwitch(); (yyval.stm_switch)->addCase(atol((yyvsp[(2) - (4)].str)), (yyvsp[(4) - (4)].block));}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 321 "parser.ypp"
    {(yyval.stm_switch) = new StmSwitch(); (yyval.stm_switch)->addCase(atol((yyvsp[(2) - (4)].str)), (yyvsp[(4) - (4)].block));}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 322 "parser.ypp"
    {(yyval.stm_switch) = new StmSwitch(); (yyval.stm_switch)->addCase(atol((yyvsp[(2) - (4)].str)), (yyvsp[(4) - (4)].block));}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 323 "parser.ypp"
    {(yyval.stm_switch) = new StmSwitch(); (yyval.stm_switch)->addCase(atol((yyvsp[(2) - (4)].str)), (yyvsp[(4) - (4)].block));}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 325 "parser.ypp"
    {(yyval.stm_switch) = new StmSwitch(); (yyval.stm_switch)->setDefault((yyvsp[(3) - (3)].block));}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 327 "parser.ypp"
    {(yyvsp[(1) - (5)].stm_switch)->addCase(atol((yyvsp[(3) - (5)].str)), (yyvsp[(5) - (5)].block)); (yyval.stm_switch) = (yyvsp[(1) - (5)].stm_switch);}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 328 "parser.ypp"
    {(yyvsp[(1) - (5)].stm_switch)->addCase(atol((yyvsp[(3) - (5)].str)), (yyvsp[(5) - (5)].block)); (yyval.stm_switch) = (yyvsp[(1) - (5)].stm_switch);}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 329 "parser.ypp"
    {(yyvsp[(1) - (5)].stm_switch)->addCase(atol((yyvsp[(3) - (5)].str)), (yyvsp[(5) - (5)].block)); (yyval.stm_switch) = (yyvsp[(1) - (5)].stm_switch);}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 330 "parser.ypp"
    {(yyvsp[(1) - (5)].stm_switch)->addCase(atol((yyvsp[(3) - (5)].str)), (yyvsp[(5) - (5)].block)); (yyval.stm_switch) = (yyvsp[(1) - (5)].stm_switch);}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 332 "parser.ypp"
    {(yyvsp[(1) - (4)].stm_switch)->setDefault((yyvsp[(4) - (4)].block)); (yyval.stm_switch) = (yyvsp[(1) - (4)].stm_switch);}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 336 "parser.ypp"
    {(yyval.stm) = new StmReturn((yyvsp[(2) - (3)].expr));}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 337 "parser.ypp"
    {(yyval.stm) = new StmReturn(0);}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 341 "parser.ypp"
    {(yyval.stm) = new StmBreak();}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 345 "parser.ypp"
    {(yyval.stm) = new StmContinue();}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 349 "parser.ypp"
    {
                                                std::string file_name = (yyvsp[(2) - (3)].str);
                                                file_name += ".cy";
                                                (yyval.stm) = new StmNop(); // Give parser a dummy node
                                                FILE* fp = open_from_path(file_name, include_path);
                                                if (fp)
                                                {
                                                    set_file_to_parse(fp);
                                                }
                                            }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 377 "parser.ypp"
    {(yyval.stm) = new StmDecl((yyvsp[(1) - (5)].type), (yyvsp[(2) - (5)].str), (yyvsp[(4) - (5)].expr));}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 378 "parser.ypp"
    {(yyval.stm) = new StmDecl(0, (yyvsp[(2) - (5)].str), (yyvsp[(4) - (5)].expr));}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 379 "parser.ypp"
    {(yyval.stm) = new StmDecl((yyvsp[(1) - (3)].type), (yyvsp[(2) - (3)].str), 0);}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 380 "parser.ypp"
    {(yyval.stm) = new StmDecl((yyvsp[(1) - (5)].type), (yyvsp[(2) - (5)].str), 0, (yyvsp[(5) - (5)].stm));}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 381 "parser.ypp"
    {(yyval.stm) = new StmDecl((yyvsp[(1) - (6)].type), (yyvsp[(2) - (6)].str), 0, (yyvsp[(6) - (6)].stm));}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 382 "parser.ypp"
    {(yyval.stm) = new StmDecl((yyvsp[(1) - (6)].type), (yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].argdeflst), (yyvsp[(6) - (6)].stm));}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 383 "parser.ypp"
    {(yyval.stm) = new StmDecl((yyvsp[(1) - (5)].type), (yyvsp[(2) - (5)].str), 0, 0);}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 384 "parser.ypp"
    {(yyval.stm) = new StmDecl((yyvsp[(1) - (6)].type), (yyvsp[(2) - (6)].str), 0, 0);}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 385 "parser.ypp"
    {(yyval.stm) = new StmDecl((yyvsp[(1) - (6)].type), (yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].argdeflst), 0);}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 386 "parser.ypp"
    {(yyval.stm) = new StmDecl((yyvsp[(1) - (6)].type), (yyvsp[(3) - (6)].str), 0, 0, true);}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 387 "parser.ypp"
    {(yyval.stm) = new StmDecl((yyvsp[(1) - (7)].type), (yyvsp[(3) - (7)].str), 0, 0, true);}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 388 "parser.ypp"
    {(yyval.stm) = new StmDecl((yyvsp[(1) - (7)].type), (yyvsp[(3) - (7)].str), (yyvsp[(5) - (7)].argdeflst), 0, true);}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 394 "parser.ypp"
    {(yyval.stm) = new StmInterface(last_interface); last_interface = 0;}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 398 "parser.ypp"
    {
                                    type_identifiers.insert((yyvsp[(1) - (1)].str));
                                    last_interface = new Interface();
                                    last_interface->setName((yyvsp[(1) - (1)].str));
                                    interface_container[(yyvsp[(1) - (1)].str)] = last_interface;
                                }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 407 "parser.ypp"
    {(yyval.interface_obj) = last_interface; (yyval.interface_obj)->addMethod((yyvsp[(1) - (1)].class_attr).name, (yyvsp[(1) - (1)].class_attr).type, (yyvsp[(1) - (1)].class_attr).args);}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 408 "parser.ypp"
    {(yyval.interface_obj)->addMethod((yyvsp[(2) - (2)].class_attr).name, (yyvsp[(2) - (2)].class_attr).type, (yyvsp[(2) - (2)].class_attr).args);}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 412 "parser.ypp"
    {(yyval.class_attr).type = (yyvsp[(1) - (5)].type); (yyval.class_attr).name = (yyvsp[(2) - (5)].str); (yyval.class_attr).args = 0; (yyval.class_attr).body = 0; (yyval.class_attr).method_state = 0;}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 413 "parser.ypp"
    {(yyval.class_attr).type = (yyvsp[(1) - (6)].type); (yyval.class_attr).name = (yyvsp[(2) - (6)].str); (yyval.class_attr).args = (yyvsp[(4) - (6)].argdeflst); (yyval.class_attr).body = 0; (yyval.class_attr).method_state = 0;}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 418 "parser.ypp"
    {(yyval.stm) = new StmClass(last_class); last_class = 0;}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 422 "parser.ypp"
    {
                            type_identifiers.insert((yyvsp[(1) - (1)].str));
                            last_class = new Class();
                            last_class->setName((yyvsp[(1) - (1)].str));
                            class_container[(yyvsp[(1) - (1)].str)] = last_class;
                        }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 428 "parser.ypp"
    {
                                                            type_identifiers.insert((yyvsp[(1) - (3)].str));
                                                            last_class = new Class();
                                                            last_class->setName((yyvsp[(1) - (3)].str));
                                                            class_container[(yyvsp[(1) - (3)].str)] = last_class;
                                                            last_class->extends(class_container[(yyvsp[(3) - (3)].str)]);
                                                        }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 435 "parser.ypp"
    {
                                                            type_identifiers.insert((yyvsp[(1) - (3)].str));
                                                            last_class = new Class();
                                                            last_class->setName((yyvsp[(1) - (3)].str));
                                                            class_container[(yyvsp[(1) - (3)].str)] = last_class;
                                                            last_class->implements(interface_container[(yyvsp[(3) - (3)].str)]);
                                                        }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 445 "parser.ypp"
    {(yyval.class_obj) = last_class; (yyval.class_obj)->addMember((yyvsp[(1) - (1)].class_attr).name, (yyvsp[(1) - (1)].class_attr).type, (yyvsp[(1) - (1)].class_attr).args, (yyvsp[(1) - (1)].class_attr).body, (yyvsp[(1) - (1)].class_attr).method_state);}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 446 "parser.ypp"
    {(yyval.class_obj)->addMember((yyvsp[(2) - (2)].class_attr).name, (yyvsp[(2) - (2)].class_attr).type, (yyvsp[(2) - (2)].class_attr).args, (yyvsp[(2) - (2)].class_attr).body, (yyvsp[(2) - (2)].class_attr).method_state);}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 450 "parser.ypp"
    {(yyval.class_attr).type = (yyvsp[(1) - (3)].type); (yyval.class_attr).name = (yyvsp[(2) - (3)].str); (yyval.class_attr).args = 0; (yyval.class_attr).body = 0; (yyval.class_attr).method_state = 0;}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 451 "parser.ypp"
    {(yyval.class_attr).type = (yyvsp[(1) - (5)].type); (yyval.class_attr).name = (yyvsp[(2) - (5)].str); (yyval.class_attr).args = 0; (yyval.class_attr).body = (yyvsp[(5) - (5)].stm); (yyval.class_attr).method_state = 0;}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 452 "parser.ypp"
    {(yyval.class_attr).type = (yyvsp[(1) - (6)].type); (yyval.class_attr).name = (yyvsp[(2) - (6)].str); (yyval.class_attr).args = 0; (yyval.class_attr).body = (yyvsp[(6) - (6)].stm); (yyval.class_attr).method_state = 0;}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 453 "parser.ypp"
    {(yyval.class_attr).type = (yyvsp[(1) - (6)].type); (yyval.class_attr).name = (yyvsp[(2) - (6)].str); (yyval.class_attr).args = (yyvsp[(4) - (6)].argdeflst); (yyval.class_attr).body = (yyvsp[(6) - (6)].stm); (yyval.class_attr).method_state = 0;}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 454 "parser.ypp"
    {(yyval.class_attr).type = (yyvsp[(2) - (6)].type); (yyval.class_attr).name = (yyvsp[(3) - (6)].str); (yyval.class_attr).args = 0; (yyval.class_attr).body = (yyvsp[(6) - (6)].stm); (yyval.class_attr).method_state = 2;}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 455 "parser.ypp"
    {(yyval.class_attr).type = (yyvsp[(2) - (7)].type); (yyval.class_attr).name = (yyvsp[(3) - (7)].str); (yyval.class_attr).args = 0; (yyval.class_attr).body = (yyvsp[(7) - (7)].stm); (yyval.class_attr).method_state = 2;}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 456 "parser.ypp"
    {(yyval.class_attr).type = (yyvsp[(2) - (7)].type); (yyval.class_attr).name = (yyvsp[(3) - (7)].str); (yyval.class_attr).args = (yyvsp[(5) - (7)].argdeflst); (yyval.class_attr).body = (yyvsp[(7) - (7)].stm); (yyval.class_attr).method_state = 2;}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 457 "parser.ypp"
    {(yyval.class_attr).type = (yyvsp[(2) - (6)].type); (yyval.class_attr).name = (yyvsp[(3) - (6)].str); (yyval.class_attr).args = 0; (yyval.class_attr).body = (yyvsp[(6) - (6)].stm); (yyval.class_attr).method_state = 3;}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 458 "parser.ypp"
    {(yyval.class_attr).type = (yyvsp[(2) - (7)].type); (yyval.class_attr).name = (yyvsp[(3) - (7)].str); (yyval.class_attr).args = 0; (yyval.class_attr).body = (yyvsp[(7) - (7)].stm); (yyval.class_attr).method_state = 3;}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 459 "parser.ypp"
    {(yyval.class_attr).type = (yyvsp[(2) - (7)].type); (yyval.class_attr).name = (yyvsp[(3) - (7)].str); (yyval.class_attr).args = (yyvsp[(5) - (7)].argdeflst); (yyval.class_attr).body = (yyvsp[(7) - (7)].stm); (yyval.class_attr).method_state = 3;}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 460 "parser.ypp"
    {(yyval.class_attr).type = (yyvsp[(2) - (6)].type); (yyval.class_attr).name = (yyvsp[(3) - (6)].str); (yyval.class_attr).args = 0; (yyval.class_attr).body = (yyvsp[(6) - (6)].stm); (yyval.class_attr).method_state = 1;}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 461 "parser.ypp"
    {(yyval.class_attr).type = (yyvsp[(2) - (7)].type); (yyval.class_attr).name = (yyvsp[(3) - (7)].str); (yyval.class_attr).args = 0; (yyval.class_attr).body = (yyvsp[(7) - (7)].stm); (yyval.class_attr).method_state = 1;}
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 462 "parser.ypp"
    {(yyval.class_attr).type = (yyvsp[(2) - (7)].type); (yyval.class_attr).name = (yyvsp[(3) - (7)].str); (yyval.class_attr).args = (yyvsp[(5) - (7)].argdeflst); (yyval.class_attr).body = (yyvsp[(7) - (7)].stm); (yyval.class_attr).method_state = 1;}
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 466 "parser.ypp"
    {(yyval.argdeflst) = new std::vector<Argument*>(); (yyval.argdeflst)->push_back(new Argument((yyvsp[(1) - (2)].type), (yyvsp[(2) - (2)].str)));}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 467 "parser.ypp"
    {(yyvsp[(1) - (4)].argdeflst)->push_back(new Argument((yyvsp[(3) - (4)].type), (yyvsp[(4) - (4)].str))); (yyval.argdeflst) = (yyvsp[(1) - (4)].argdeflst);}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 472 "parser.ypp"
    {(yyval.type) = new TypeClass(class_container[(yyvsp[(1) - (1)].str)]);}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 473 "parser.ypp"
    {(yyval.type) = new TypeArray((yyvsp[(1) - (3)].type));}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 474 "parser.ypp"
    {(yyval.type) = new TypeArray((yyvsp[(1) - (4)].type), atoi((yyvsp[(3) - (4)].str)));}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 475 "parser.ypp"
    {(yyval.type) = TypePrimary::getVoid();}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 479 "parser.ypp"
    {(yyval.type) = TypePrimary::getBool();}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 480 "parser.ypp"
    {(yyval.type) = TypePrimary::getByte();}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 481 "parser.ypp"
    {(yyval.type) = TypePrimary::getShort();}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 482 "parser.ypp"
    {(yyval.type) = TypePrimary::getInt();}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 483 "parser.ypp"
    {(yyval.type) = TypePrimary::getLong();}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 484 "parser.ypp"
    {(yyval.type) = TypePrimary::getFloat();}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 485 "parser.ypp"
    {(yyval.type) = TypePrimary::getDouble();}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 489 "parser.ypp"
    {(yyval.expr) = new ExprLiteral((bool)true);}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 490 "parser.ypp"
    {(yyval.expr) = new ExprLiteral((bool)false);}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 491 "parser.ypp"
    {(yyval.expr) = (yyvsp[(1) - (1)].array);}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 492 "parser.ypp"
    {(yyval.expr) = (yyvsp[(1) - (1)].array);}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 493 "parser.ypp"
    {(yyval.expr) = new ExprLiteral((char)(yyvsp[(1) - (1)].str)[1]);}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 494 "parser.ypp"
    {(yyval.expr) = new ExprLiteral((char)atoi((yyvsp[(1) - (1)].str)));}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 495 "parser.ypp"
    {(yyval.expr) = new ExprLiteral((short)atoi((yyvsp[(1) - (1)].str)));}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 496 "parser.ypp"
    {(yyval.expr) = new ExprLiteral((int)atoi((yyvsp[(1) - (1)].str)));}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 497 "parser.ypp"
    {(yyval.expr) = new ExprLiteral((long)atoi((yyvsp[(1) - (1)].str)));}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 498 "parser.ypp"
    {(yyval.expr) = new ExprLiteral((float)atof((yyvsp[(1) - (1)].str)));}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 499 "parser.ypp"
    {(yyval.expr) = new ExprLiteral(atof((yyvsp[(1) - (1)].str)));}
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 500 "parser.ypp"
    {(yyval.expr) = new ExprArray((yyvsp[(1) - (1)].str));}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 501 "parser.ypp"
    {(yyval.expr) = new ExprSymbol((yyvsp[(1) - (1)].str));}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 502 "parser.ypp"
    {(yyval.expr) = new ExprObject(new TypeClass(class_container[(yyvsp[(1) - (3)].str)]));}
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 503 "parser.ypp"
    {(yyval.expr) = (yyvsp[(2) - (3)].expr);}
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 507 "parser.ypp"
    {(yyval.array) = new ExprArray((yyvsp[(2) - (5)].type), (yyvsp[(4) - (5)].expr));}
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 511 "parser.ypp"
    {(yyval.array) = (yyvsp[(2) - (3)].array);}
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 515 "parser.ypp"
    {(yyval.array) = new ExprArray(); (yyval.array)->addExpr((yyvsp[(1) - (1)].expr));}
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 516 "parser.ypp"
    {(yyvsp[(1) - (3)].array)->addExpr((yyvsp[(3) - (3)].expr)); (yyval.array) = (yyvsp[(1) - (3)].array);}
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 520 "parser.ypp"
    {(yyval.arglst) = new ExprCall(); (yyval.arglst)->addArg((yyvsp[(1) - (1)].expr));}
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 521 "parser.ypp"
    {(yyval.arglst)->addArg((yyvsp[(3) - (3)].expr));}
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 526 "parser.ypp"
    {(yyval.expr) = new ExprOP2(ExprOP2::ARRAY, (yyvsp[(1) - (4)].expr), (yyvsp[(3) - (4)].expr));}
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 527 "parser.ypp"
    {(yyvsp[(3) - (4)].arglst)->setCallee((yyvsp[(1) - (4)].expr)); (yyval.expr) = (yyvsp[(3) - (4)].arglst);}
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 528 "parser.ypp"
    {ExprCall* n = new ExprCall(); n->setCallee((yyvsp[(1) - (3)].expr)); (yyval.expr) = n;}
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 529 "parser.ypp"
    {(yyval.expr) = new ExprOP2(ExprOP2::DOT, (yyvsp[(1) - (3)].expr), new ExprSymbol((yyvsp[(3) - (3)].str)));}
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 530 "parser.ypp"
    {(yyval.expr) = new ExprOP2(ExprOP2::DOT, new ExprClass(class_container[(yyvsp[(1) - (3)].str)]), new ExprSymbol((yyvsp[(3) - (3)].str)));}
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 531 "parser.ypp"
    {(yyval.expr) = new ExprAssign((yyvsp[(1) - (2)].expr), true, false);}
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 532 "parser.ypp"
    {(yyval.expr) = new ExprAssign((yyvsp[(1) - (2)].expr), true, true);}
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 537 "parser.ypp"
    {(yyval.expr) = new ExprAssign((yyvsp[(2) - (2)].expr), false, false);}
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 538 "parser.ypp"
    {(yyval.expr) = new ExprAssign((yyvsp[(2) - (2)].expr), false, true);}
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 539 "parser.ypp"
    {(yyval.expr) = new ExprOP1(ExprOP1::POS, (yyvsp[(2) - (2)].expr));}
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 540 "parser.ypp"
    {(yyval.expr) = new ExprOP1(ExprOP1::NEG, (yyvsp[(2) - (2)].expr));}
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 541 "parser.ypp"
    {(yyval.expr) = new ExprOP1(ExprOP1::B_NOT, (yyvsp[(2) - (2)].expr));}
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 542 "parser.ypp"
    {(yyval.expr) = new ExprOP1(ExprOP1::NOT, (yyvsp[(2) - (2)].expr));}
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 547 "parser.ypp"
    {(yyval.expr) = new ExprOP2(ExprOP2::MUL, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 548 "parser.ypp"
    {(yyval.expr) = new ExprOP2(ExprOP2::DIV, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 549 "parser.ypp"
    {(yyval.expr) = new ExprOP2(ExprOP2::MOD, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 554 "parser.ypp"
    {(yyval.expr) = new ExprOP2(ExprOP2::ADD, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 555 "parser.ypp"
    {(yyval.expr) = new ExprOP2(ExprOP2::SUB, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 560 "parser.ypp"
    {(yyval.expr) = new ExprOP2(ExprOP2::SHL, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 561 "parser.ypp"
    {(yyval.expr) = new ExprOP2(ExprOP2::SHR, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 562 "parser.ypp"
    {(yyval.expr) = new ExprOP2(ExprOP2::ASHR, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 567 "parser.ypp"
    {(yyval.expr) = new ExprOP2(ExprOP2::LT, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 568 "parser.ypp"
    {(yyval.expr) = new ExprOP2(ExprOP2::LTE, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 569 "parser.ypp"
    {(yyval.expr) = new ExprOP2(ExprOP2::GT, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 570 "parser.ypp"
    {(yyval.expr) = new ExprOP2(ExprOP2::GTE, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 575 "parser.ypp"
    {(yyval.expr) = new ExprOP2(ExprOP2::EQ, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 576 "parser.ypp"
    {(yyval.expr) = new ExprOP2(ExprOP2::NEQ, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 581 "parser.ypp"
    {(yyval.expr) = new ExprOP2(ExprOP2::B_AND, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 586 "parser.ypp"
    {(yyval.expr) = new ExprOP2(ExprOP2::B_XOR, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 591 "parser.ypp"
    {(yyval.expr) = new ExprOP2(ExprOP2::B_OR, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 596 "parser.ypp"
    {(yyval.expr) = new ExprOP2(ExprOP2::AND, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 601 "parser.ypp"
    {(yyval.expr) = new ExprOP2(ExprOP2::OR, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 606 "parser.ypp"
    {(yyval.expr) = new ExprCondition((yyvsp[(1) - (5)].expr), (yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].expr));}
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 611 "parser.ypp"
    {(yyval.expr) = new ExprAssign((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 612 "parser.ypp"
    {(yyval.expr) = new ExprAssign(ExprOP2::ADD , (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 613 "parser.ypp"
    {(yyval.expr) = new ExprAssign(ExprOP2::SUB , (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 614 "parser.ypp"
    {(yyval.expr) = new ExprAssign(ExprOP2::MUL , (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 615 "parser.ypp"
    {(yyval.expr) = new ExprAssign(ExprOP2::DIV , (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 616 "parser.ypp"
    {(yyval.expr) = new ExprAssign(ExprOP2::MOD , (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 617 "parser.ypp"
    {(yyval.expr) = new ExprAssign(ExprOP2::B_AND , (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 618 "parser.ypp"
    {(yyval.expr) = new ExprAssign(ExprOP2::B_OR , (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 619 "parser.ypp"
    {(yyval.expr) = new ExprAssign(ExprOP2::B_XOR , (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 620 "parser.ypp"
    {(yyval.expr) = new ExprAssign(ExprOP2::SHL , (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 621 "parser.ypp"
    {(yyval.expr) = new ExprAssign(ExprOP2::SHR , (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 622 "parser.ypp"
    {(yyval.expr) = new ExprAssign(ExprOP2::ASHR , (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));}
    break;



/* Line 1806 of yacc.c  */
#line 3064 "parser.cpp"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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
      if (!yypact_value_is_default (yyn))
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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



/* Line 2067 of yacc.c  */
#line 629 "parser.ypp"

#include "gc.h"

void* cy_malloc2(size_t len) {
    void* l;
    l = GC_malloc(len);
    //l = malloc(len);
    std::cout << "Allocate: " << len << " @ " << l;
    std::cout << " (";
    for (size_t i = 0; i < len && i < 20; i++)
    {
        std::cout << ((char*)l)[len+i];
    }
    std::cout << ")" << std::endl;

    return l;
}

void* cy_malloc(size_t len) {
    void* l;
    l = GC_malloc(len);
    return l;
}

int main(int argc, char** argv)
{
    // Initialize include path
    include_path = new std::vector<std::string>();
    //include_path->push_back("./");
    include_path->push_back("./cylib/");

    included = new std::set<std::string>();

    // Initialize GC
    GC_INIT();

    // Initialise option flags
    bool only_file_name = false;

    bool verify = false;
    bool execute = false;
    bool print_ast = false;
    bool show_assembly = false;
    bool dump_to_file = false;
    bool optimize = false;
    bool dump_classes = false;
    file_to_parse = stdin;


    for (int i = 1; i < argc; i++)
    {
        if (only_file_name || argv[i][0] != '-')
        {
            file_to_parse = fopen(argv[i], "r");
        }
        else
        {
            if (!strcmp(argv[i], "--"))
            {
                only_file_name = true;
            }
            else
            {
                for (size_t l = 1; l < strlen(argv[i]); l++)
                {
                    switch (argv[i][l])
                    {
                        case 'v':
                            verify = true;
                            break;
                        case 'e':
                            execute = true;
                            break;
                        case 't':
                            print_ast = true;
                            break;
                        case 'a':
                            show_assembly = true;
                            break;
                        case 'o':
                            dump_to_file = true;
                            break;
                        case 'O':
                            optimize = true;
                            break;
                        case 'c':
                            dump_classes = true;
                            break;
                        default:
                            printf("Unknown simple option: %c\n", argv[i][l]);
                    }
                }
            }
        }
    }

    // Define the file to parse
    set_file_to_parse(file_to_parse);

    // Initialize main blocks
    main_block = new StmBlock();
    main_func = new StmDecl(TypePrimary::getVoid(), "__main__", 0, main_block);

    // Initialize visitors
    display_visitor = new VisitorNodeDisplay();
    typer_visitor = new VisitorNodeTyper();
    llvm_visitor = new VisitorNodeLlvm();
    simplify_visitor = new VisitorNodeSimplify();
    llvm_visitor->verify = verify;

    // Initialize symbol table
    Symtab* symt = new Symtab();
    display_visitor->setSymtab(symt);
    typer_visitor->setSymtab(symt);

    // Initialize logger
    out_debug = fopen("/dev/null", "rw");
    //out_debug = stderr;

    // Parser
    try
    {
        yyparse();
    }
    catch (std::string s)
    {
        std::cout << s << std::endl;
    }
    catch (const char* s)
    {
        std::cout << s << std::endl;
    }

    // Add terminal instruction to main function
    main_block->addStatement(new StmReturn(0));

    try
    {
        main_func->accept(*typer_visitor);
        if (print_ast)
            main_func->accept(*display_visitor);
        main_func->accept(*simplify_visitor);
        main_func->accept(*llvm_visitor);
    }
    catch (std::string s)
    {
        std::cout << s << std::endl;
        exit(1);
    }
    catch (const char* s)
    {
        std::cout << s << std::endl;
        exit(1);
    }

    // Dump llvm assembly
    if (show_assembly)
        llvm_visitor->getModule()->dump();

    // Dump llvm assembly to file
    if (dump_to_file)
    {
        std::ofstream fp;
        fp.open("out.ss");
        llvm::raw_os_ostream ros(fp);
        llvm_visitor->getModule()->print(ros, 0);
    }

    if (verify)
    {
        llvm::verifyFunction(*llvm_visitor->module->getFunction("__main__"));
    }

    // Execute __main__ function
    if (execute)
    {
        // Initialize LLVM JIT
        llvm::InitializeNativeTarget();

        // Create LLVM Execution Engine
        std::string ErrStr;
        llvm_visitor->exec = llvm::EngineBuilder(llvm_visitor->module).setErrorStr(&ErrStr).create();
        // FIXME
        if (!llvm_visitor->exec) {
            fprintf(stderr, "Could not create ExecutionEngine: %s\n", ErrStr.c_str());
            exit(1);
        }

        if (optimize) {
            llvm_visitor->optimize();
        }

        // bind runtime functions
        llvm_visitor->exec->addGlobalMapping(llvm_visitor->module->getFunction("cy_malloc"), (void*)cy_malloc);
        llvm_visitor->exec->addGlobalMapping(llvm_visitor->module->getFunction("cy_malloc2"), (void*)cy_malloc2);

        llvm_visitor->exec->addGlobalMapping(llvm_visitor->module->getFunction("putbyte"),   (void*)putbyte);
        llvm_visitor->exec->addGlobalMapping(llvm_visitor->module->getFunction("putshort"),  (void*)putshort);
        llvm_visitor->exec->addGlobalMapping(llvm_visitor->module->getFunction("putint"),    (void*)putint);
        llvm_visitor->exec->addGlobalMapping(llvm_visitor->module->getFunction("putlong"),   (void*)putlong);
        llvm_visitor->exec->addGlobalMapping(llvm_visitor->module->getFunction("putfloat"),  (void*)putfloat);
        llvm_visitor->exec->addGlobalMapping(llvm_visitor->module->getFunction("putdouble"), (void*)putdouble);

        llvm_visitor->exec->addGlobalMapping(llvm_visitor->module->getFunction("btos"), (void*)btos);
        llvm_visitor->exec->addGlobalMapping(llvm_visitor->module->getFunction("btoi"), (void*)btoi);
        llvm_visitor->exec->addGlobalMapping(llvm_visitor->module->getFunction("btol"), (void*)btol);
        llvm_visitor->exec->addGlobalMapping(llvm_visitor->module->getFunction("stob"), (void*)stob);
        llvm_visitor->exec->addGlobalMapping(llvm_visitor->module->getFunction("stoi"), (void*)stoi);
        llvm_visitor->exec->addGlobalMapping(llvm_visitor->module->getFunction("stol"), (void*)stol);
        llvm_visitor->exec->addGlobalMapping(llvm_visitor->module->getFunction("itob"), (void*)itob);
        llvm_visitor->exec->addGlobalMapping(llvm_visitor->module->getFunction("itos"), (void*)itos);
        llvm_visitor->exec->addGlobalMapping(llvm_visitor->module->getFunction("itol"), (void*)itol);
        llvm_visitor->exec->addGlobalMapping(llvm_visitor->module->getFunction("ltob"), (void*)ltob);
        llvm_visitor->exec->addGlobalMapping(llvm_visitor->module->getFunction("ltos"), (void*)ltos);
        llvm_visitor->exec->addGlobalMapping(llvm_visitor->module->getFunction("ltoi"), (void*)ltoi);

        // Get pointer to main function
        void (*main_func)() = (void (*)())(intptr_t)llvm_visitor->exec->getPointerToFunction(llvm_visitor->module->getFunction("__main__"));;

        // Execute main func
        main_func();
    }

    // Show classes
    if (dump_classes)
    {
        std::map<std::string, Class*>::iterator it;
        for (it = class_container.begin(); it != class_container.end(); it++)
        {
            std::cout << it->first << ": " << it->second->getName() << std::endl;
        }
    }
    return 0;
}

