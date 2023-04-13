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

"!"                     { printToken(yytext,"LOGICAL NOT") ;}
"&&"                    { printToken(yytext,"LOGICAL AND") ;}
"||"                    { printToken(yytext,"LOGICAL OR") ;}

"=="                    { printToken(yytext, "EQUALS");}
"<="                    { printToken(yytext, "LESS THAN/EQUALS");}
">="                    { printToken(yytext, "MORE THAN/EQUALS");}
"!="                    { printToken(yytext, "NOT EQUALS");}
">"                     { printToken(yytext, "MORE THAN");}
"<"                     { printToken(yytext, "LESS THAN");}

"--"                    { printToken(yytext, "INCREMENT");}
"++"                    { printToken(yytext, "DECREMENT");}

"="                     { printToken(yytext, "ASSIGN") ;}  
"+="                    { printToken(yytext, "PLUS ASSIGN") ;}
"-="                    { printToken(yytext, "MINUS ASSIGN") ;}
"*="                    { printToken(yytext, "TIMES ASSIGN") ;}
"/="                    { printToken(yytext, "OVER ASSIGN") ;}
"%="                    { printToken(yytext, "PERCENT ASSIGN") ;}

"+"                     { printToken(yytext, "PLUS") ;}  
"-"                     { printToken(yytext, "MINUS") ;}  
"*"                     { printToken(yytext, "TIMES") ;}  
"/"                     { printToken(yytext, "OVER") ;}  
"%"                     { printToken(yytext, "PERCENT") ;}  

"("                     { printToken(yytext, "LPAR") ;}
")"                     { printToken(yytext, "RPAR") ;}
"{"                     { printToken(yytext, "LCURLYBRACES") ;}
"}"                     { printToken(yytext, "RCURLYBRACES") ;}
"["                     { printToken(yytext, "LBRACKET") ;}
"]"                     { printToken(yytext, "RBRACKET") ;}
";"                     { printToken(yytext, "SEMI") ;}
","                     { printToken(yytext, "COMMA") ;}
"&"                     { printToken(yytext, "AMPERSAND") ;}

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