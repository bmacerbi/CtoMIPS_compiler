
%output "parser.c"
%defines "parser.h"
%define parse.error verbose
%define parse.lac full

%{
#include <stdio.h>

int yylex(void);
void yyerror(char const *s);
%}

%token AUTO DOUBLE INT STRUCT BREAK ELSE LONG SWITCH CASE ENUM REGISTER TYPEDEF CHAR EXTERN RETURN UNION CONST FLOAT SHORT UNSIGNED CONTINUE FOR SIGNED VOID DEFAULT GOTO SIZEOF VOLATILE DO IF STATIC WHILE _BOOL _IMAGINARY RESTRICT _COMPLEX INLINE
%left LT GT EQ 
%left PLUS MINUS
%left TIMES OVER


%%
program : PROGRAM ID SEMI vars-sect stmt-sect ;
vars-sect : VAR opt-var-decl ;
opt-var-decl : %empty | var-decl-list ;
var-decl-list : var-decl-list var-decl | var-decl ;
var-decl : type-spec ID SEMI ;
type-spec : BOOL | INT | REAL | STRING ;
stmt-sect : T_BEGIN stmt-list END ;
stmt-list : stmt-list stmt | stmt ;
stmt : if-stmt | repeat-stmt | assign-stmt | read-stmt | write-stmt ;
if-stmt : IF expr THEN stmt-list END 
| IF expr THEN stmt-list ELSE stmt-list END ;

repeat-stmt : REPEAT stmt-list UNTIL expr ;
assign-stmt : ID ASSIGN expr SEMI ;
read-stmt : READ ID SEMI ;
write-stmt : WRITE expr SEMI ;
expr : expr LT expr 
    | expr EQ expr
    | expr PLUS expr
    | expr MINUS expr
    | expr TIMES expr
    | expr OVER expr
    | LPAR expr RPAR
    | TRUE
    | FALSE
    | INT_VAL
    | REAL_VAL
    | STR_VAL
    | ID ;
%%

int main(void) {
    if (yyparse() == 0) printf("PARSE SUCCESSFUL!\n");
    else                printf("PARSE FAILED!\n");
    return 0;
}
