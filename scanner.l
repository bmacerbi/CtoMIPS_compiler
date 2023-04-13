%option yylineno
%{
    #include <stdio.h>

    void printToken(char *token, char *msg);
    void lexicalError(char *token);
%}
%%
"//".* {}
"/*"((\*+[^/*])|([^*]))*\**"*/" {}

auto                    { printToken(yytext, "AUTO") ;}
double                  { printToken(yytext, "DOUBLE") ;}
int                     { printToken(yytext, "INT") ;}
struct                  { printToken(yytext, "STRUCT") ;}
break                   { printToken(yytext, "BREAK") ;}
else                    { printToken(yytext, "ELSE") ;}
long                    { printToken(yytext, "LONG") ;}
switch                  { printToken(yytext, "SWITCH") ;}
case                    { printToken(yytext, "CASE") ;}
enum                    { printToken(yytext, "ENUM") ;}
register                { printToken(yytext, "REGISTER") ;}
typedef                 { printToken(yytext, "TYPEDEF") ;}
char                    { printToken(yytext, "CHAR") ;}
extern                  { printToken(yytext, "EXTERN") ;}
return                  { printToken(yytext, "RETURN") ;}
union                   { printToken(yytext, "UNION") ;}
const                   { printToken(yytext, "CONST") ;}
float                   { printToken(yytext, "FLOAT") ;}
short                   { printToken(yytext, "SHORT") ;}
unsigned                { printToken(yytext, "UNSIGNED") ;}
continue                { printToken(yytext, "CONTINUE") ;}
for                     { printToken(yytext, "FOR") ;}
signed                  { printToken(yytext, "SIGNED") ;}
void                    { printToken(yytext, "VOID") ;}
default                 { printToken(yytext, "DEFAULT") ;}
goto                    { printToken(yytext, "GOTO") ;}
sizeof                  { printToken(yytext, "SIZEOF") ;}
volatile                { printToken(yytext, "VOLATILE") ;}
do                      { printToken(yytext, "DO") ;}
if                      { printToken(yytext, "IF") ;}
static                  { printToken(yytext, "STATIC") ;}
while                   { printToken(yytext, "WHILE") ;}
_Bool                   { printToken(yytext, "_BOOL") ;}
_Imaginary              { printToken(yytext, "_IMAGINARY") ;}
restrict                { printToken(yytext, "RESTRICT") ;}
_Complex                { printToken(yytext, "_COMPLEX") ;}
inline                  { printToken(yytext, "INLINE") ;}

"!"                     { printToken(yytext,"L_NOT") ;}
"&&"                    { printToken(yytext,"L_AND") ;}
"||"                    { printToken(yytext,"L_OR") ;}

"=="                    { printToken(yytext, "EQ");}
"<="                    { printToken(yytext, "LT_EQ");}
">="                    { printToken(yytext, "MT_EQ");}
"!="                    { printToken(yytext, "N_EQ");}
">"                     { printToken(yytext, "MT");}
"<"                     { printToken(yytext, "LT");}

"--"                    { printToken(yytext, "INC");}
"++"                    { printToken(yytext, "D");}

"="                     { printToken(yytext, "ASGN") ;}  
"+="                    { printToken(yytext, "PL_ASGN") ;}
"-="                    { printToken(yytext, "M_ASGN") ;}
"*="                    { printToken(yytext, "T_ASGN") ;}
"/="                    { printToken(yytext, "O_ASGN") ;}
"%="                    { printToken(yytext, "PC_ASGN") ;}

"+"                     { printToken(yytext, "PLUS") ;}  
"-"                     { printToken(yytext, "MINUS") ;}  
"*"                     { printToken(yytext, "TIMES") ;}  
"/"                     { printToken(yytext, "OVER") ;}  
"%"                     { printToken(yytext, "PERCENT") ;}  

"("                     { printToken(yytext, "LPAR") ;}
")"                     { printToken(yytext, "RPAR") ;}
"{"                     { printToken(yytext, "LCURLY") ;}
"}"                     { printToken(yytext, "RCURLY") ;}
"["                     { printToken(yytext, "LBRAC") ;}
"]"                     { printToken(yytext, "RBRAC") ;}
";"                     { printToken(yytext, "SEMI") ;}
","                     { printToken(yytext, "COMMA") ;}
"&"                     { printToken(yytext, "AMPER") ;}

[A-Za-z_][A-Za-z0-9_]*  { printToken(yytext, "ID") ;}                   
[0-9]+\.[0-9]+          { printToken(yytext, "FLOAT_VAL") ;}              
[0-9]+                  { printToken(yytext, "INT_VAL") ;}      
\"[^"]*\"              { printToken(yytext, "STR_VAL") ;}
\'[^']\'               { printToken(yytext, "CHAR_VAL") ;}   

[ \t\n]                 {}

.                       { lexicalError(yytext) ;} 

%%
void printToken(char *token, char *msg){
    printf("%d: %s -> %s\n",yylineno, token, msg);
}

void lexicalError(char *token){
    printf("LEXICAL ERROR (%d): Unknown symbol %s\n", yylineno, token);
    exit(1);
}