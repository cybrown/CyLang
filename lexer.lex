%{
#include "Class.hpp"
#include <string.h>
#include "AllNodes.hpp"
#include <set>
extern "C" {
    int yylex(void);
}

#pragma GCC diagnostic ignored "-Wunused-function"

struct s_class_attr {
    char* name;
    Type* type;
};

#include "parser.hpp"

int current_char = 0;
int current_line = 0;
char str_buffer[1024] = {'\0'};
FILE *out_debug;

// Set containing type identifers, filled by the parser
std::set<std::string> type_identifiers;

// return true if str is a type identifier
bool is_type_id(char *str)
{
	return type_identifiers.find(str) != type_identifiers.end();
}

int is_keyword(char *str)
{
	/* STATEMENTS */
	if (!strcmp(str, "if"))
		return TOK_IF;
	else if (!strcmp(str, "else"))
		return TOK_ELSE;
	else if (!strcmp(str, "for"))
		return TOK_FOR;
	else if (!strcmp(str, "while"))
		return TOK_WHILE;
	else if (!strcmp(str, "do"))
		return TOK_DO;
	else if (!strcmp(str, "switch"))
		return TOK_SWITCH;
	else if (!strcmp(str, "case"))
		return TOK_CASE;
	else if (!strcmp(str, "break"))
		return TOK_BREAK;
	else if (!strcmp(str, "continue"))
		return TOK_CONTINUE;
	else if (!strcmp(str, "return"))
		return TOK_RETURN;
	else if (!strcmp(str, "default"))
		return TOK_DEFAULT;
	else if (!strcmp(str, "import"))
		return TOK_IMPORT;
	else if (!strcmp(str, "extern"))
		return TOK_EXTERN;
	else if (!strcmp(str, "static"))
		return TOK_STATIC;
	else if (!strcmp(str, "override"))
		return TOK_OVERRIDE;
	else if (!strcmp(str, "virtual"))
		return TOK_VIRTUAL;
	else if (!strcmp(str, "extends"))
		return TOK_EXTENDS;
	else if (!strcmp(str, "implements"))
		return TOK_IMPLEMENTS;
	/* TYPES */
	else if (!strcmp(str, "interface"))
		return TOK_INTERFACE;
	else if (!strcmp(str, "class"))
		return TOK_CLASS;
	else if (!strcmp(str, "var"))
		return TOK_VAR;
	else if (!strcmp(str, "boolean"))
		return TOK_BOOL;
	else if (!strcmp(str, "bool"))
		return TOK_BOOL;
	else if (!strcmp(str, "byte"))
		return TOK_BYTE;
	else if (!strcmp(str, "short"))
		return TOK_SHORT;
	else if (!strcmp(str, "int"))
		return TOK_INT;
	else if (!strcmp(str, "long"))
		return TOK_LONG;
	else if (!strcmp(str, "float"))
		return TOK_FLOAT;
	else if (!strcmp(str, "double"))
		return TOK_DOUBLE;
	else if (!strcmp(str, "void"))
		return TOK_VOID;
	/* CONSTANTS */
	else if (!strcmp(str, "true"))
		return TOK_TRUE;
	else if (!strcmp(str, "false"))
		return TOK_FALSE;
	return 0;
}

%}

digit [0-9]
octdigit [0-7]
hexdigit [0-9a-fA-F]
alpha [a-zA-Z]
blank [\t]|" "

alnum {alpha}|{digit}

%s STRING
%s STRING_ESC
%s COMMENT
%s COMMENT_ONELINE

%%

<INITIAL>0{octdigit}+    {fprintf(out_debug, "Octal integer: %s\n",       yytext); current_char += yyleng; yylval.str = strdup(yytext); return LITERAL_INTEGER;}
<INITIAL>0               {fprintf(out_debug, "Decimal integer: %s\n",     yytext); current_char += yyleng; yylval.str = strdup(yytext); return LITERAL_INTEGER;}
<INITIAL>0b              {fprintf(out_debug, "Decimal integer: %s\n",     yytext); current_char += yyleng; yylval.str = strdup(yytext); return LITERAL_BYTE;}
<INITIAL>0s              {fprintf(out_debug, "Decimal integer: %s\n",     yytext); current_char += yyleng; yylval.str = strdup(yytext); return LITERAL_SHORT;}
<INITIAL>0i              {fprintf(out_debug, "Decimal integer: %s\n",     yytext); current_char += yyleng; yylval.str = strdup(yytext); return LITERAL_INTEGER;}
<INITIAL>0l              {fprintf(out_debug, "Decimal integer: %s\n",     yytext); current_char += yyleng; yylval.str = strdup(yytext); return LITERAL_LONG;}
<INITIAL>[1-9]{digit}*b  {fprintf(out_debug, "Decimal byte: %s\n",        yytext); current_char += yyleng; yylval.str = strdup(yytext); return LITERAL_BYTE;}
<INITIAL>"'"."'"         {fprintf(out_debug, "Character: %s\n",           yytext); current_char += yyleng; yylval.str = strdup(yytext); return LITERAL_CHAR;}
<INITIAL>"'"\\n"'"       {fprintf(out_debug, "Character: %s\n",           yytext); current_char += yyleng; yylval.str = strdup("'\n'"); return LITERAL_CHAR;}
<INITIAL>"'"\\r"'"       {fprintf(out_debug, "Character: %s\n",           yytext); current_char += yyleng; yylval.str = strdup("'\r'"); return LITERAL_CHAR;}
<INITIAL>[1-9]{digit}*s  {fprintf(out_debug, "Decimal short: %s\n",       yytext); current_char += yyleng; yylval.str = strdup(yytext); return LITERAL_SHORT;}
<INITIAL>[1-9]{digit}*   {fprintf(out_debug, "Decimal integer: %s\n",     yytext); current_char += yyleng; yylval.str = strdup(yytext); return LITERAL_INTEGER;}
<INITIAL>[1-9]{digit}*i  {fprintf(out_debug, "Decimal integer: %s\n",     yytext); current_char += yyleng; yylval.str = strdup(yytext); return LITERAL_INTEGER;}
<INITIAL>[1-9]{digit}*l  {fprintf(out_debug, "Decimal long: %s\n",        yytext); current_char += yyleng; yylval.str = strdup(yytext); return LITERAL_LONG;}
<INITIAL>0x{hexdigit}*   {fprintf(out_debug, "Hexadecimal integer: %s\n", yytext); current_char += yyleng; yylval.str = strdup(yytext); return LITERAL_INTEGER;}

<INITIAL>{digit}+"."{digit}*  {fprintf(out_debug, "Double: %s\n", yytext); current_char += yyleng; yylval.str = strdup(yytext); return LITERAL_DOUBLE;}
<INITIAL>{digit}*"."{digit}+  {fprintf(out_debug, "Double: %s\n", yytext); current_char += yyleng; yylval.str = strdup(yytext); return LITERAL_DOUBLE;}
<INITIAL>{digit}+"."{digit}*d {fprintf(out_debug, "Double: %s\n", yytext); current_char += yyleng; yylval.str = strdup(yytext); return LITERAL_DOUBLE;}
<INITIAL>{digit}*"."{digit}+d {fprintf(out_debug, "Double: %s\n", yytext); current_char += yyleng; yylval.str = strdup(yytext); return LITERAL_DOUBLE;}
<INITIAL>{digit}+"."{digit}*f {fprintf(out_debug, "Float: %s\n",  yytext); current_char += yyleng; yylval.str = strdup(yytext); return LITERAL_FLOAT;}
<INITIAL>{digit}*"."{digit}+f {fprintf(out_debug, "Float: %s\n",  yytext); current_char += yyleng; yylval.str = strdup(yytext); return LITERAL_FLOAT;}

<INITIAL>\"				{current_char += yyleng; fprintf(out_debug, "\""); current_char += yyleng; BEGIN STRING;}

<INITIAL>"="            {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_ASSIGN;}
<INITIAL>"+="           {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_ADD_ASSIGN;}
<INITIAL>"-="           {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_SUB_ASSIGN;}
<INITIAL>"*="           {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_MUL_ASSIGN;}
<INITIAL>"/="           {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_DIV_ASSIGN;}
<INITIAL>"%="           {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_MOD_ASSIGN;}
<INITIAL>"&="           {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_B_AND_ASSIGN;}
<INITIAL>"|="           {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_B_OR_ASSIGN;}
<INITIAL>"^="           {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_B_XOR_ASSIGN;}
<INITIAL>"<<="          {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_SHL_ASSIGN;}
<INITIAL>">>="          {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_SHR_ASSIGN;}
<INITIAL>">>>="         {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_ASHR_ASSIGN;}


<INITIAL>"++"           {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_INC;}
<INITIAL>"--"           {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_DEC;}

<INITIAL>"+"            {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return '+';}
<INITIAL>"-"            {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return '-';}
<INITIAL>"*"            {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return '*';}
<INITIAL>"/"            {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return '/';}
<INITIAL>"%"            {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return '%';}

<INITIAL>"<<"           {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_SHL;}
<INITIAL>">>"           {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_SHR;}
<INITIAL>">>>"          {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_ASHR;}

<INITIAL>"=="           {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_EQ;}
<INITIAL>"!="           {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_NEQ;}
<INITIAL>"<"            {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_LT;}
<INITIAL>"<="           {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_LTE;}
<INITIAL>">"            {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_GT;}
<INITIAL>">="           {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_GTE;}

<INITIAL>"&&"           {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_AND;}
<INITIAL>"||"           {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return TOK_OR;}
<INITIAL>"!"            {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return '!';}

<INITIAL>"&"            {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return '&';}
<INITIAL>"|"            {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return '|';}
<INITIAL>"^"            {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return '^';}
<INITIAL>"~"            {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return '~';}

<INITIAL>"("			{fprintf(out_debug, "Par open\n"); current_char += yyleng; return '(';}
<INITIAL>")"      		{fprintf(out_debug, "Par close\n"); current_char += yyleng; return ')';}
<INITIAL>"{"			{fprintf(out_debug, "Bloc open\n"); current_char += yyleng; return '{';}
<INITIAL>"}"      		{fprintf(out_debug, "Bloc close\n"); current_char += yyleng; return '}';}
<INITIAL>"["			{fprintf(out_debug, "Array open\n"); current_char += yyleng; return '[';}
<INITIAL>"]"      		{fprintf(out_debug, "Array close\n"); current_char += yyleng; return ']';}

<INITIAL>"?"			{fprintf(out_debug, "Question mark\n"); current_char += yyleng; return '?';}
<INITIAL>":"      		{fprintf(out_debug, "Colon\n"); current_char += yyleng; return ':';}

<INITIAL>","      		{fprintf(out_debug, "Comma\n"); current_char += yyleng; return ',';}
<INITIAL>"."            {fprintf(out_debug, "Operator %s\n", yytext); current_char += yyleng; return '.';}
<INITIAL>";"            {fprintf(out_debug, "Semi colon\n"); current_char += yyleng; return ';';}

<INITIAL>({alpha}|[_$])({alnum}|_)* {
		if (is_keyword(yytext))
		{
			fprintf(out_debug, "Keyword %d %s\n", is_keyword(yytext), yytext);
			current_char += yyleng;
			yylval.str = strdup(yytext);
			return is_keyword(yytext);
		}
		else if (is_type_id(yytext))
		{
			fprintf(out_debug, "Typeid %d %s\n", is_type_id(yytext), yytext);
			current_char += yyleng;
			yylval.str = strdup(yytext);
			return TOK_TYPE_IDENTIFIER;
		}
		else
		{
			current_char += yyleng;
			fprintf(out_debug, "Identifier: %s\n", yytext);
			yylval.str = strdup(yytext);
			return TOK_IDENTIFIER;
		}
	}

<INITIAL>"/*"           {fprintf(out_debug, "Begin comment\n"); current_char += yyleng; BEGIN COMMENT;}
<INITIAL>"//"           {fprintf(out_debug, "Begin comment\n"); current_char += yyleng; BEGIN COMMENT_ONELINE;}

<INITIAL>" "|blank      {current_char++;}
<INITIAL>\r?\n          {current_line++; current_char = 0;}
<INITIAL>.              {current_char++; fprintf(out_debug, "Unknown char \"%s\"\n", yytext);}

<STRING>\\\"		    {current_char += yyleng;}
<STRING>\"              {current_char += yyleng; fprintf(out_debug, "\"\n"); yylval.str = strdup(str_buffer); str_buffer[0] = '\0'; BEGIN INITIAL; fprintf(out_debug, "String %s>\n", yylval.str); return LITERAL_STRING;}
<STRING>\r?\n           {strcat(str_buffer, yytext); current_char = 0; current_line++;}
<STRING>\\				{current_char += yyleng; BEGIN STRING_ESC;}
<STRING>.               {strcat(str_buffer, yytext); current_char += yyleng;}

<STRING_ESC>n 			{current_char += yyleng; strcat(str_buffer, "\n"); BEGIN STRING;}
<STRING_ESC>r 			{current_char += yyleng; strcat(str_buffer, "\r"); BEGIN STRING;}
<STRING_ESC>. 			{current_char += yyleng; BEGIN STRING;}

<COMMENT>"*/"           {fprintf(out_debug, "End comment\n"); current_char += yyleng; BEGIN INITIAL;}
<COMMENT>.              {current_char += yyleng;}
<COMMENT>\r?\n          {current_char = 0; current_line++;}

<COMMENT_ONELINE>.		{current_char++;}
<COMMENT_ONELINE>\n 	{current_line++; current_char = 0; BEGIN INITIAL;}
<<EOF>>					{yypop_buffer_state(); if (YY_CURRENT_BUFFER) yy_switch_to_buffer(YY_CURRENT_BUFFER); else yyterminate();}
%%
