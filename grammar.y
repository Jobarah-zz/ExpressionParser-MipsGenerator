%code requires {
  #include<iostream>
  #include<stdlib.h>
  #include<string>
  #include <list>

  #include "AST.h"

  using namespace std;
}

%{
  #include<stdio.h>
  extern int yylineno;
  int yylex();
  void yyerror(const char* msg) {
    printf("Line %d: %s\n",yylineno,msg);
  }

  AST * tree;
%}

%union {
  char* id_t;
  int num_t;
  Expr *expr_t;
  AST * ast_t;
}

%token<id_t> ID LIT_INT
%token TK_EOF TK_ERROR
%token OP_ADD "+"
%token OP_TIMES "*"
%token OP_MINUS "-"
%token TK_LEFT_PAR "("
%token TK_RIGHT_PAR ")"
%type<expr_t> E T F
%type<ast_t> ExprList

%%

input: ExprList { tree = $1; }
;

ExprList: ExprList E { $$ = $1; $$->insertExpression($2); }
  | E { $$ = new AST(); $$->insertExpression($1); }
;

E: E "+" T { $$ = new AddExpr($1, $3); }
  | E "-" T { $$ = new SubExpr($1, $3); }
  | T { $$ = $1; }
;

T: T "*" F { $$ = new MultExpr($1, $3); }
  | F { $$ = $1; }
;

F: LIT_INT { $$ = new NumExpr($1); }
  | ID {
    string str = $1;
    free($1); 
    $$ = new IdExpr(str);
  }
  | "(" E ")" { $$ = $2; }
;