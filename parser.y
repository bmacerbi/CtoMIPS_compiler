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
int argsCount =  0;

int yylex(void);
int yylex_destroy(void);
void yyerror(char const *s);
void newVar(char* str, int line);
void checkVar(char* str, int line);
void newFunc(char* str, int line);

extern char *yytext;
extern int yylineno;
extern char *idCopy;
%}

%token INC DEC LT_EQ GT_EQ LT GT EQ N_EQ L_NOT
%token L_AND L_OR ASGN T_ASGN O_ASGN MOD_ASGN PL_ASGN M_ASGN
%token CHAR INT FLOAT VOID
%token IF ELSE WHILE GOTO CONTINUE BREAK RETURN
%token ID FLOAT_VAL INT_VAL STR_VAL CHAR_VAL 
%token PLUS MINUS TIMES OVER PERCENT LPAR RPAR 
%token LCURLY RCURLY LBRAC RBRAC SEMI COMMA AMPER COLON

%left COMMA
%right ASGN PL_ASGN M_ASGN T_ASGN O_ASGN MOD_ASGN
%left L_OR
%left L_AND
%left EQ N_EQ
%left LT GT LT_EQ GT_EQ
%left PLUS MINUS
%right INC DEC L_NOT AMPER
%left TIMES OVER PERCENT
%left LBRAC RBRAC LPAR RPAR 
%precedence UMINUS

%start translation_unit
%%

expression
	: ID { checkVar(idCopy, yylineno); }
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
	: type_specifier SEMI
	| type_specifier init_declarator_list SEMI
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

declarator
	: ID { newVar(yytext, yylineno); }
	| LPAR declarator RPAR
	| declarator LBRAC expression RBRAC
	| declarator LBRAC RBRAC
	| declarator LPAR parameter_list RPAR
	| declarator LPAR RPAR
	;

function_declarator
	: ID { newFunc(yytext, yylineno); }
	| LPAR function_declarator RPAR
	| function_declarator LBRAC expression RBRAC
	| function_declarator LBRAC RBRAC
	| function_declarator LPAR parameter_list RPAR
	| function_declarator LPAR RPAR
	;

parameter_list
	: parameter_declaration {argsCount++;}	
	| parameter_list COMMA parameter_declaration {argsCount++;}
	;

parameter_declaration
	: type_specifier declarator
	| type_specifier abstract_declarator
	| type_specifier
	;

type_name
	: type_specifier
	| type_specifier abstract_declarator
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
	: compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
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
	: CONTINUE SEMI
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
	: type_specifier function_declarator compound_statement { set_args_count_func(funcTable, scopeCount, argsCount); argsCount = 0;}
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
	VarTable* vt = get_var_table_func(funcTable,scopeCount);
    int index = lookup_var(vt, str);

    if ( index == -1 ) {
        add_func_var(funcTable, str, line, type, scopeCount);
    } 
	else {
        printf("SEMANTIC ERROR (%d): variable ’%s’ already declared at line %d.\n", line, str, get_line(vt, index));
		exit(EXIT_FAILURE);
    }
	
}

void checkVar(char* str, int line){
	VarTable* vt = get_var_table_func(funcTable,scopeCount);
    int indexVar = lookup_var(vt, str);
	int indexFunc = lookup_func(funcTable, str);

	if ( indexVar == -1 && indexFunc == -1) {
        printf("SEMANTIC ERROR (%d): variable ’%s’ was never declared.\n", line, str);
		exit(EXIT_FAILURE);
    }
}

void newFunc(char* str, int line){
    int index = lookup_func(funcTable, str);
    if ( index == -1 ) {
        add_func(funcTable, str, line, argsCount, type);
    } else {
        printf("SEMANTIC ERROR (%d): function ’%s’ already declared at line %d.\n", line, str, get_line_func(funcTable, index));
		exit(EXIT_FAILURE);
    }
}