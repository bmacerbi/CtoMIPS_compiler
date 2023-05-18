/* Flex output */
%option outfile="scanner.c"
/* Unused functions */
%option noyywrap
%option nounput
%option noinput
/* Auto increment variable yylineno every time a '\n' is read. */
%option yylineno

%{
    #include <stdio.h>
    #include "parser.h"

    
    void printToken(char *token, char *msg);
    void lexicalError(char *token);
    char* idCopy;   
%}
%%
"//".* {}
"/*"((\*+[^/*])|([^*]))*\**"*/" {}

void                    { return VOID ;}
int                     { return INT ;}
float                   { return FLOAT ;}
char                    { return CHAR ;}
break                   { return BREAK ;}
continue                { return CONTINUE ;}
goto                    { return GOTO ;}
return                  { return RETURN ;}
if                      { return IF ;}
else                    { return ELSE ;}
while                   { return WHILE ;}

"!"                     { return L_NOT ;}
"&&"                    { return L_AND ;}
"||"                    { return L_OR ;}
"=="                    { return EQ;}
"<="                    { return LT_EQ;}
">="                    { return GT_EQ;}
"!="                    { return N_EQ;}
">"                     { return GT;}
"<"                     { return LT;}
"--"                    { return DEC;}
"++"                    { return INC;}
"="                     { return ASGN ;}  
"+="                    { return PL_ASGN ;}
"-="                    { return M_ASGN ;}
"*="                    { return T_ASGN ;}
"/="                    { return O_ASGN ;}
"%="                    { return MOD_ASGN ;}
"+"                     { return PLUS ;}  
"-"                     { return MINUS ;}  
"*"                     { return TIMES ;}  
"/"                     { return OVER ;}  
"%"                     { return PERCENT ;}  
"("                     { return LPAR ;}
")"                     { return RPAR ;}
"{"                     { return LCURLY ;}
"}"                     { return RCURLY ;}
"["                     { return LBRAC ;}
"]"                     { return RBRAC ;}
";"                     { return SEMI ;}
":"                     { return COLON ;}
","                     { return COMMA ;}
"&"                     { return AMPER ;}

[A-Za-z_][A-Za-z0-9_]*  {  idCopy = yytext; return ID;}                   
[0-9]+\.[0-9]+          { return FLOAT_VAL ;}              
[0-9]+                  { return INT_VAL ;}      
\"[^"]*\"               { return STR_VAL ;}
\'[^']*\'                { return CHAR_VAL ;}   

[ \t\n]                 {}

.                       { lexicalError(yytext) ;} 

%%

void lexicalError(char *token){
    printf("LEXICAL ERROR (%d): Unknown symbol %s\n", yylineno, token);
    exit(1);
}