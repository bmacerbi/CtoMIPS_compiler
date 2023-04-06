
%option yylineno
%{
    

%}
%%
/* keywords */
auto                { printf("%s\n", yytext) ;}
doub                { printf("%s\n", yytext) ;}
int                 { printf("%s\n", yytext) ;}
stru                { printf("%s\n", yytext) ;}
brea                { printf("%s\n", yytext) ;}
else                { printf("%s\n", yytext) ;}
long                { printf("%s\n", yytext) ;}
swit                { printf("%s\n", yytext) ;}
case                { printf("%s\n", yytext) ;}
enum                { printf("%s\n", yytext) ;}
regi                { printf("%s\n", yytext) ;}
type                { printf("%s\n", yytext) ;}
char                { printf("%s\n", yytext) ;}
exte                { printf("%s\n", yytext) ;}
retu                { printf("%s\n", yytext) ;}
unio                { printf("%s\n", yytext) ;}
cons                { printf("%s\n", yytext) ;}
floa                { printf("%s\n", yytext) ;}
shor                { printf("%s\n", yytext) ;}
unsi                { printf("%s\n", yytext) ;}
cont                { printf("%s\n", yytext) ;}
for                 { printf("%s\n", yytext) ;}
sign                { printf("%s\n", yytext) ;}
void                { printf("%s\n", yytext) ;}
defa                { printf("%s\n", yytext) ;}
goto                { printf("%s\n", yytext) ;}
size                { printf("%s\n", yytext) ;}
vola                { printf("%s\n", yytext) ;}
do                  { printf("%s\n", yytext) ;}
if                  { printf("%s\n", yytext) ;}
stat                { printf("%s\n", yytext) ;}
whil                { printf("%s\n", yytext) ;}
_Bool               { printf("%s\n", yytext) ;}
_Imaginary          { printf("%s\n", yytext) ;}
restrict            { printf("%s\n", yytext) ;}
_Complex            { printf("%s\n", yytext) ;}
inline              { printf("%s\n", yytext) ;}
/* Logical operators */
[!]                 { printf("%s\n", yytext) ;}
[&][&]              { printf("%s\n", yytext) ;}
[|]                 { printf("%s\n", yytext) ;}
/* Increment/decrement operators */
[-][-]              { printf("%s\n", yytext) ;}  
[+][+]              { printf("%s\n", yytext) ;} 
/* Assignment operators */
[=]                 { printf("%s\n", yytext) ;}  
[+][=]              { printf("%s\n", yytext) ;}  
[-][=]              { printf("%s\n", yytext) ;}  
[*][=]              { printf("%s\n", yytext) ;}  
[/][=]              { printf("%s\n", yytext) ;}  
/* Arithmetic operators */
[+]                 { printf("%s\n", yytext) ;}
[-]                 { printf("%s\n", yytext) ;}
[+]                 { printf("%s\n", yytext) ;}
[-]                 { printf("%s\n", yytext) ;}
[*]                 { printf("%s\n", yytext) ;}
[/]                 { printf("%s\n", yytext) ;}
[%]                 { printf("%s\n", yytext) ;}
/* Var and Strings */
[A-Za-z_][A-Za-z0-9_]*           { printf("%s\n", yytext) ;}                   
[0-9]+\.[0-9]+      { printf("%s\n", yytext) ;}              
[0-9]+              { printf("%s\n", yytext) ;}      
\"[^\"\"]*\"        { printf("%s\n", yytext) ;}              
[ \t\n]             { printf("%s\n", yytext) ;}
/* UNKOWN */
.                   { printf("UNKOWN\n") ;} 
%%