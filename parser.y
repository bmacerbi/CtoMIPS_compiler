%output "parser.c"
%defines "parser.h"
%define parse.error verbose
%define parse.lac full

%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "tables.h"

StrTable* strTable;
VarTable* varTable;
FunctionTable* funcTable;
Type type;
int scopeCount = 0;
int isFunction = 1;

int yylex(void);
int yylex_destroy(void);
void yyerror(char const *s);
void newVar(char* str, int line);
void verifyToken(char *str, int line);
void newId(char* str, int line);
void newFunc(char* str, int line);

extern char *yytext;
extern int yylineno;
%}

%token INC DEC LT_EQ GT_EQ LT GT EQ N_EQ L_NOT
%token L_AND L_OR ASGN T_ASGN O_ASGN MOD_ASGN PL_ASGN M_ASGN
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE VOID
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN
%token ID FLOAT_VAL INT_VAL STR_VAL CHAR_VAL SIZEOF
%token PLUS MINUS TIMES OVER PERCENT LPAR RPAR 
%token LCURLY RCURLY LBRAC RBRAC SEMI COMMA AMPER COLON

%left COMMA
%right ASGN PL_ASGN M_ASGN T_ASGN O_ASGN MOD_ASGN
%left L_OR
%left L_AND
%left EQ N_EQ
%left LT GT LT_EQ GT_EQ
%left PLUS MINUS
%right INC DEC L_NOT AMPER SIZEOF
%left TIMES OVER PERCENT
%left LBRAC RBRAC LPAR RPAR 
%precedence UMINUS

%start translation_unit
%%

expression
	: ID
	| FLOAT_VAL
	| INT_VAL
	| STR_VAL {add_string(strTable, yytext);}
	| CHAR_VAL
	| LPAR expression RPAR
	| expression LBRAC expression RBRAC
	| expression LPAR RPAR
	| expression LPAR argument_expression_list RPAR
	| expression INC 
	| expression DEC 
	| INC expression 
	| DEC expression 
	| unary_operator expression %prec UMINUS
	| SIZEOF expression
	| SIZEOF LPAR type_name RPAR
	| LPAR type_name RPAR expression
	| expression TIMES expression
	| expression OVER expression
	| expression PERCENT expression
	| expression PLUS expression
	| expression MINUS expression
	| expression LT expression
	| expression GT expression
	| expression LT_EQ expression
	| expression GT_EQ expression
	| expression EQ expression
	| expression N_EQ expression
	| expression L_AND expression
	| expression L_OR expression
	| expression ASGN expression
	| expression T_ASGN expression 
	| expression O_ASGN expression 
	| expression MOD_ASGN expression 
	| expression PL_ASGN expression
	| expression M_ASGN expression
	;


argument_expression_list
	: expression
	| argument_expression_list COMMA expression
	;

unary_operator
	: AMPER
	| PLUS
	| MINUS
	| L_NOT
	;

declaration
	: declaration_specifiers SEMI
	| declaration_specifiers init_declarator_list SEMI
	;

declaration_specifiers
	: type_specifier
	| type_specifier declaration_specifiers
	;

init_declarator_list
	: init_declarator
	| init_declarator_list COMMA init_declarator
	;

init_declarator
	: declarator
	| declarator ASGN initializer
	;

type_specifier
	: VOID  { type = VOID_TYPE; }
	| CHAR  { type = CHAR_TYPE; }
	| INT   { type = INT_TYPE;  }
	| FLOAT { type = FLOAT_TYPE;  }
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	;

declarator
	: ID { newVar(yytext, yylineno); }
	| LPAR declarator RPAR
	| declarator LBRAC expression RBRAC
	| declarator LBRAC RBRAC
	| declarator LPAR parameter_list RPAR
	| declarator LPAR identifier_list RPAR
	| declarator LPAR RPAR
	;

function_declarator
	: ID { newFunc(yytext, yylineno); }
	| LPAR function_declarator RPAR
	| function_declarator LBRAC expression RBRAC
	| function_declarator LBRAC RBRAC
	| function_declarator LPAR parameter_list RPAR
	| function_declarator LPAR identifier_list RPAR
	| function_declarator LPAR RPAR
	;

parameter_list
	: parameter_declaration
	| parameter_list COMMA parameter_declaration
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list
	: ID
	| identifier_list COMMA ID
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: LPAR abstract_declarator RPAR
	| LBRAC RBRAC
	| LBRAC expression RBRAC
	| abstract_declarator LBRAC RBRAC
	| abstract_declarator LBRAC expression RBRAC
	| LPAR RPAR
	| LPAR parameter_list RPAR
	| abstract_declarator LPAR RPAR
	| abstract_declarator LPAR parameter_list RPAR
	;

initializer
	: expression
	| LCURLY initializer_list RCURLY
	| LCURLY initializer_list COMMA RCURLY
	;

initializer_list
	: initializer
	| initializer_list COMMA initializer
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: ID COLON statement
	| CASE expression COLON statement
	| DEFAULT COLON statement
	;

compound_statement
	: LCURLY RCURLY
	| LCURLY statement_list RCURLY
	| LCURLY declaration_list RCURLY
	| LCURLY declaration_list statement_list RCURLY
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

statement_list
	: statement
	| statement_list statement
	;

expression_statement
	: SEMI
	| expression SEMI
	;

selection_statement
	: IF LPAR expression RPAR compound_statement
	| IF LPAR expression RPAR compound_statement ELSE compound_statement
	;

iteration_statement
	: WHILE LPAR expression RPAR statement
	;

jump_statement
	: GOTO ID SEMI
	| CONTINUE SEMI
	| BREAK SEMI
	| RETURN SEMI
	| RETURN expression SEMI
	;

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition { scopeCount++;}
	;

function_definition
	: declaration_specifiers function_declarator compound_statement
	;

%%

// Primitive error handling.
void yyerror (char const *s) {
    printf("SYNTAX ERROR (%d): %s\n", yylineno, s);
    exit(EXIT_FAILURE);
}

int main() {
	strTable = create_str_table();
	funcTable = create_func_table();

    yyparse();
    printf("PARSE SUCCESSFUL!\n");
	print_str_table(strTable);
	print_func_table(funcTable);

    yylex_destroy();    // To avoid memory leaks within flex...
	free_str_table(strTable);
	free_func_table(funcTable);
    return 0;
}


void newVar(char* str, int line){
	
    int index = lookup_var(get_var_table_func(funcTable,scopeCount), str);

    if ( index == -1 ) {
        add_func_var(funcTable, str, line, type, scopeCount);
    } 
	else {
        printf("SEMANTIC ERROR (%d): variable ’%s’ already declared at line %d.\n", line, str, get_line(get_var_table_func(funcTable,scopeCount), index));
		exit(EXIT_FAILURE);
    }
	
}

void newFunc(char* str, int line){
    int index = lookup_func(funcTable, str);
    if ( index == -1 ) {
        add_func(funcTable, str, line, 2, type);
    } else {
        printf("SEMANTIC ERROR (%d): function ’%s’ already declared at line %d.\n", line, str, get_line_func(funcTable, index));
		exit(EXIT_FAILURE);
    }
}

void verifyToken(char *str, int line){
	int index = lookup_var(varTable, str);
    if ( index == -1 ) {
    	printf("SEMANTIC ERROR (%d): token ’%s’ was not declared at line %d.\n", line, str, line);
		exit(EXIT_FAILURE);
    }
}