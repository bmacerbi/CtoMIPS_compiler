
%option yylineno
%{
    

%}
%%

auto                { printf("%s\n", yytext) ;}
double              { printf("%s\n", yytext) ;}
int                 { printf("%s\n", yytext) ;}
struct              { printf("%s\n", yytext) ;}
break               { printf("%s\n", yytext) ;}
else                { printf("%s\n", yytext) ;}
long                { printf("%s\n", yytext) ;}
switch              { printf("%s\n", yytext) ;}
case                { printf("%s\n", yytext) ;}
enum                { printf("%s\n", yytext) ;}
register            { printf("%s\n", yytext) ;}
typedef             { printf("%s\n", yytext) ;}
char                { printf("%s\n", yytext) ;}
extern              { printf("%s\n", yytext) ;}
return              { printf("%s\n", yytext) ;}
union               { printf("%s\n", yytext) ;}
const               { printf("%s\n", yytext) ;}
float               { printf("%s\n", yytext) ;}
short               { printf("%s\n", yytext) ;}
unsigned            { printf("%s\n", yytext) ;}
continue            { printf("%s\n", yytext) ;}
for                 { printf("%s\n", yytext) ;}
signed              { printf("%s\n", yytext) ;}
void                { printf("%s\n", yytext) ;}
default             { printf("%s\n", yytext) ;}
goto                { printf("%s\n", yytext) ;}
sizeof              { printf("%s\n", yytext) ;}
volatile            { printf("%s\n", yytext) ;}
do                  { printf("%s\n", yytext) ;}
if                  { printf("%s\n", yytext) ;}
static              { printf("%s\n", yytext) ;}
while               { printf("%s\n", yytext) ;}
_Bool               { printf("%s\n", yytext) ;}
_Imaginary          { printf("%s\n", yytext) ;}
restrict            { printf("%s\n", yytext) ;}
_Complex            { printf("%s\n", yytext) ;}
inline              { printf("%s\n", yytext) ;}

[!]                 { printf("%s\n", yytext) ;}
[&][&]              { printf("%s\n", yytext) ;}
[|]                 { printf("%s\n", yytext) ;}

[-][-]              { printf("%s\n", yytext) ;}  
[+][+]              { printf("%s\n", yytext) ;} 

[=]                 { printf("%s\n", yytext) ;}  
[+][=]              { printf("%s\n", yytext) ;}  
[-][=]              { printf("%s\n", yytext) ;}  
[*][=]              { printf("%s\n", yytext) ;}  
[/][=]              { printf("%s\n", yytext) ;}  

[+]                 { printf("%s\n", yytext) ;}
[-]                 { printf("%s\n", yytext) ;}
[*]                 { printf("%s\n", yytext) ;}
[/]                 { printf("%s\n", yytext) ;}
[%]                 { printf("%s\n", yytext) ;}

[;]                 { printf("%s\n", yytext) ;}

[A-Za-z_][A-Za-z0-9_]* { printf("%s\n", yytext) ;}                   
[0-9]+\.[0-9]+         { printf("%s\n", yytext) ;}              
[0-9]+                 { printf("%s\n", yytext) ;}      
\"[^\"\"]*\"           { printf("%s\n", yytext) ;}              
[ \t\n]                { printf("%s\n", yytext) ;}

.                   { printf("UNKNOWN\n") ;} 
%%