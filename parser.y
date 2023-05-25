%output "parser.c"
%defines "parser.h"
%define parse.error verbose
%define parse.lac full

%{
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
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
Type checkVar(char* str, int line);
void newFunc(char* str, int line);
Type check_number(Type t);
Type check_assign(Type l, Type r);
Type check_int(Type l, Type r);

Type unify_bin_op(Type l, Type r, const char* op, Type (*unify)(Type,Type));
void type_error(const char* op, Type t1, Type t2);

extern char *yytext;
extern int yylineno;
extern char *idCopy;
%}
%define api.value.type {Type}

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
	: ID { $$ = checkVar(idCopy, yylineno); }
	| FLOAT_VAL { $$ = FLOAT_TYPE; }
	| INT_VAL { $$ = INT_TYPE; }
	| STR_VAL { add_string(strTable, yytext); $$ = CHAR_TYPE; }
	| CHAR_VAL { $$ = CHAR_TYPE; }
	| LPAR expression RPAR { $$ = $2; }
	| expression LBRAC expression RBRAC { $$ = $1; }
	| expression LPAR RPAR { $$ = $1; }
	| expression LPAR argument_expression_list RPAR { $$ = $1; }
	| expression INC { $$ = check_number($1); }
	| expression DEC { $$ = check_number($1); }
	| INC expression { $$ = check_number($2); }
	| DEC expression { $$ = check_number($2); }
	| unary_operator expression %prec UMINUS { $$ = check_number($2); }
	| expression TIMES expression 		{ $$ = unify_bin_op($1, $3, "*", unify_arith); }
	| expression OVER expression 		{ $$ = unify_bin_op($1, $3, "/", unify_arith); }
	| expression PERCENT expression		{ $$ = unify_bin_op($1, $3, "%%", unify_arith); } 
	| expression PLUS expression 		{ $$ = unify_bin_op($1, $3, "+", unify_arith); }
	| expression MINUS expression		{ $$ = unify_bin_op($1, $3, "-", unify_arith); }
	| expression LT expression 			{ $$ = unify_bin_op($1, $3, "<", unify_comp); }
	| expression GT expression 			{ $$ = unify_bin_op($1, $3, ">", unify_comp); }	
	| expression LT_EQ expression 		{ $$ = unify_bin_op($1, $3, "<=", unify_comp); }			
	| expression GT_EQ expression 		{ $$ = unify_bin_op($1, $3, ">=", unify_comp); }	
	| expression EQ expression			{ $$ = unify_bin_op($1, $3, "==", unify_comp); }		
	| expression N_EQ expression 		{ $$ = unify_bin_op($1, $3, "!=", unify_comp); }			
	| expression L_AND expression 		{ $$ = check_int($1, $3); }
	| expression L_OR expression 		{ $$ = check_int($1, $3); }
	| expression ASGN expression        { $$ = check_assign($1, $3); }
	| expression T_ASGN expression 		{ $$ = unify_bin_op($1, $3, "*", unify_arith); }
	| expression O_ASGN expression 		{ $$ = unify_bin_op($1, $3, "/", unify_arith); }
	| expression MOD_ASGN expression 	{ $$ = unify_bin_op($1, $3, "%%", unify_arith); } 
	| expression PL_ASGN expression		{ $$ = unify_bin_op($1, $3, "+", unify_arith); }
	| expression M_ASGN expression 		{ $$ = unify_bin_op($1, $3, "-", unify_arith); }
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

Type checkVar(char* str, int line){
	VarTable* vt = get_var_table_func(funcTable,scopeCount);
    int indexVar = lookup_var(vt, str);
	int indexFunc = lookup_func(funcTable, str);

	if ( indexVar == -1 && indexFunc == -1) {
        printf("SEMANTIC ERROR (%d): variable ’%s’ was never declared.\n", line, str);
		exit(EXIT_FAILURE);
    }

	if(indexFunc != -1){
		return get_type_func(funcTable, indexFunc);
	} else {
		return get_type(vt,indexVar);
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

// ----------------------------------------------------------------------------

// Type checking and inference.

void type_error(const char* op, Type t1, Type t2) {
    printf("SEMANTIC ERROR (%d): incompatible types for operator '%s', LHS is '%s' and RHS is '%s'.\n",
           yylineno, op, get_text(t1), get_text(t2));
    exit(EXIT_FAILURE);
}

Type unify_bin_op(Type l, Type r,
                  const char* op, Type (*unify)(Type,Type)) {
    Type unif = unify(l, r);
    if (unif == NO_TYPE) {
        type_error(op, l, r);
    }
    return unif;
}

Type check_number(Type t){
	if(t != INT_TYPE && t != FLOAT_TYPE){
		printf("SEMANTIC ERROR (%d): not a number.\n", yylineno);
    	exit(EXIT_FAILURE);
	}

	return t;
}

Type check_assign(Type l, Type r) {
    if (l == VOID_TYPE  || r == VOID_TYPE)  type_error("=", l, r);
    if (l == CHAR_TYPE  && r != CHAR_TYPE)  type_error("=", l, r);
    if (l == INT_TYPE  && r != INT_TYPE)  type_error("=", l, r);
    if (l == FLOAT_TYPE && !(r == INT_TYPE || r == FLOAT_TYPE)) type_error("=", l, r);
	return l;
}

Type check_int(Type l, Type r) {
	if (l != INT_TYPE  || r != INT_TYPE) type_error("not int", l, r);
	return INT_TYPE;
}