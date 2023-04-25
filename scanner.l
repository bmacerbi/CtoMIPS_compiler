%option yylineno
%{
    #include <stdio.h>

    void printToken(char *token, char *msg);
    void lexicalError(char *token);
%}
%%
"//".* {}
"/*"((\*+[^/*])|([^*]))*\**"*/" {}

auto                    { return AUTO ;}
double                  { return DOUBLE ;}
int                     { return INT ;}
struct                  { return STRUCT ;}
break                   { return BREAK ;}
else                    { return ELSE ;}
long                    { return LONG ;}
switch                  { return SWITCH ;}
case                    { return CASE ;}
enum                    { return ENUM ;}
register                { return REGISTER ;}
typedef                 { return TYPEDEF ;}
char                    { return CHAR ;}
extern                  { return EXTERN ;}
return                  { return RETURN ;}
union                   { return UNION ;}
const                   { return CONST ;}
float                   { return FLOAT ;}
short                   { return SHORT ;}
unsigned                { return UNSIGNED ;}
continue                { return CONTINUE ;}
for                     { return FOR ;}
signed                  { return SIGNED ;}
void                    { return VOID ;}
default                 { return DEFAULT ;}
goto                    { return GOTO ;}
sizeof                  { return SIZEOF ;}
volatile                { return VOLATILE ;}
do                      { return DO ;}
if                      { return IF ;}
static                  { return STATIC ;}
while                   { return WHILE ;}
_Bool                   { return _BOOL ;}
_Imaginary              { return _IMAGINARY ;}
restrict                { return RESTRICT ;}
_Complex                { return _COMPLEX ;}
inline                  { return INLINE ;}

"!"                     { return L_NOT ;}
"&&"                    { return L_AND ;}
"||"                    { return L_OR ;}
"=="                    { return EQ;}
"<="                    { return LT_EQ;}
">="                    { return MT_EQ;}
"!="                    { return N_EQ;}
">"                     { return MT;}
"<"                     { return LT;}
"--"                    { return DEC;}
"++"                    { return INC;}
"="                     { return ASGN ;}  
"+="                    { return PL_ASGN ;}
"-="                    { return M_ASGN ;}
"*="                    { return T_ASGN ;}
"/="                    { return O_ASGN ;}
"%="                    { return PC_ASGN ;}
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
","                     { return COMMA ;}
"&"                     { return AMPER ;}

[A-Za-z_][A-Za-z0-9_]*  { return ID ;}                   
[0-9]+\.[0-9]+          { return FLOAT_VAL ;}              
[0-9]+                  { return INT_VAL ;}      
\"[^"]*\"               { return STR_VAL ;}
\'[^']\'                { return CHAR_VAL ;}   

[ \t\n]                 {}

.                       { lexicalError(yytext) ;} 

%%

void lexicalError(char *token){
    printf("LEXICAL ERROR (%d): Unknown symbol %s\n", yylineno, token);
    exit(1);
}