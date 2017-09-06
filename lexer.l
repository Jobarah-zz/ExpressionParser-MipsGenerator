%option noyywrap
%option yylineno

%{
  /*Includes area*/
#include "tokens.h"
#include <iostream>
using namespace std;

%}

%%
[0-9]+ { yylval.id_t = strdup(yytext); return LIT_INT; }
[A-Za-z]+ {  yylval.id_t = strdup(yytext); return ID; }
[ \t\n] { /*Do nothing*/ }
"+" { return OP_ADD; }
"*" { return OP_TIMES; }
"-" { return OP_MINUS; }
"(" { return TK_LEFT_PAR; }
")" { return TK_RIGHT_PAR; }
.   { return TK_ERROR; }

%%
