/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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

/* Line 2068 of yacc.c  */
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



/* Line 2068 of yacc.c  */
#line 141 "parser.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


