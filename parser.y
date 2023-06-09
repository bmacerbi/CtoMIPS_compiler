%output "parser.c"
%defines "parser.h"
%define parse.error verbose
%define parse.lac full

%{
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "tables.h"
#include "ast.h"
#include "parser.h"
#include "interpreter.h"

StrTable* strTable;
VarTable* varTable;
FunctionTable* funcTable;
Type type;
int scopeCount = 0;
int isFunction = 1;
int argsCount =  0;
AST *root;

int yylex(void);
int yylex_destroy(void);
void yyerror(char const *s);
AST* newVar(char* str);
AST* checkVar(char* str);
void newArrayVar();
void newFunc(char* str, int line);
AST* check_number(AST* node);
AST* check_assign(AST* nodeL, AST* nodeR);
AST* check_declarator_assign(AST* nodeL, AST* nodeR);
AST* check_int(AST* nodeL, AST* nodeR, NodeKind kind);
AST* toPrimitive(AST* node);
AST* toArray(AST* node);
AST* check_if_then(AST *e, AST *b);
AST* check_if_then_else(AST *e, AST *b1, AST *b2);
void check_bool_expr(const char* cmd, Type t);
AST* check_while(AST *e, AST *b);

AST* unify_bin_op(AST* nodeL, AST* nodeR, NodeKind kind, const char* op, Type (*unify)(Type,Type));
void type_error(const char* op, Type t1, Type t2);

extern char *yytext;
extern int yylineno;
extern char *idCopy;
%}

%define api.value.type {AST*}

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
	: ID { $$ = checkVar(idCopy); }
	| FLOAT_VAL	{ $$ = $1; }
	| INT_VAL	{ $$ = $1; }
	| STR_VAL 	{ $$ = $1; }
	| CHAR_VAL	{ $$ = $1; }
	| LPAR expression RPAR { $$ = $2; }
	| expression LBRAC expression RBRAC { $$ = toPrimitive($1);}
	| expression LPAR RPAR { $$ = $1; }
	| expression LPAR argument_expression_list RPAR { add_child($1, $3); $$ = $1; }
	| expression INC { $$ = check_number($1); }
	| expression DEC { $$ = check_number($1); }
	| INC expression { $$ = check_number($2); }
	| DEC expression { $$ = check_number($2); }
	| unary_operator expression %prec UMINUS { $$ = check_number($2); }
	| expression TIMES expression 		{ $$ = unify_bin_op($1, $3, TIMES_NODE, "*", unify_arith); }
	| expression OVER expression 		{ $$ = unify_bin_op($1, $3, OVER_NODE, "/", unify_arith); }
	| expression PERCENT expression		{ $$ = unify_bin_op($1, $3, PERCENT_NODE, "%%", unify_arith); } 
	| expression PLUS expression 		{ $$ = unify_bin_op($1, $3, PLUS_NODE, "+", unify_arith); }
	| expression MINUS expression		{ $$ = unify_bin_op($1, $3, MINUS_NODE, "-", unify_arith); }
	| expression LT expression 			{ $$ = unify_bin_op($1, $3, LT_NODE, "<", unify_comp); }
	| expression GT expression 			{ $$ = unify_bin_op($1, $3, GT_NODE, ">", unify_comp); }	
	| expression LT_EQ expression 		{ $$ = unify_bin_op($1, $3, LT_EQ_NODE, "<=", unify_comp); }			
	| expression GT_EQ expression 		{ $$ = unify_bin_op($1, $3, GT_EQ_NODE, ">=", unify_comp); }	
	| expression EQ expression			{ $$ = unify_bin_op($1, $3, EQ_NODE, "==", unify_comp); }		
	| expression N_EQ expression 		{ $$ = unify_bin_op($1, $3, N_EQ_NODE, "!=", unify_comp); }			
	| expression L_AND expression 		{ $$ = check_int($1, $3, L_AND_NODE); }
	| expression L_OR expression 		{ $$ = check_int($1, $3, L_OR_NODE); }
	| expression ASGN expression        { $$ = check_assign($1, $3); }
	| expression T_ASGN expression 		{ $$ = unify_bin_op($1, $3, T_ASGN_NODE, "*", unify_arith); }
	| expression O_ASGN expression 		{ $$ = unify_bin_op($1, $3, O_ASGN_NODE, "/", unify_arith); }
	| expression MOD_ASGN expression 	{ $$ = unify_bin_op($1, $3, MOD_ASGN_NODE, "%%", unify_arith); } 
	| expression PL_ASGN expression		{ $$ = unify_bin_op($1, $3, PL_ASGN_NODE, "+", unify_arith); }
	| expression M_ASGN expression 		{ $$ = unify_bin_op($1, $3, M_ASGN_NODE, "-", unify_arith); }
	;


argument_expression_list
	: expression 								{ $$ = new_subtree(ARG_LIST_NODE, NO_TYPE, 1, $1); }
	| argument_expression_list COMMA expression { add_child($1, $3); $$ = $1; }
	;

unary_operator
	: AMPER
	| PLUS
	| MINUS
	| L_NOT
	;

declaration
	: type_specifier init_declarator SEMI { $$ = $2; }
	;

init_declarator
	: declarator { $$ = $1; }
	| declarator ASGN initializer { $$ = check_declarator_assign($1, $3); }
	;

type_specifier
	: VOID  { type = VOID_TYPE;  }
	| CHAR  { type = CHAR_TYPE;  }
	| INT   { type = INT_TYPE;   }
	| FLOAT { type = FLOAT_TYPE; }
	;

declarator
	: ID { $$ = newVar(yytext); }
	| declarator LBRAC expression RBRAC { newArrayVar(); $$ = toArray($1);}
	| declarator LBRAC RBRAC { newArrayVar(); $$ = toArray($1);}
	;

function_declarator
	: ID { newFunc(yytext, yylineno); $$ = new_node(PARAM_LIST_NODE, 0, NO_TYPE); }
	| function_declarator LPAR parameter_list RPAR { $$ = $3; }
	| function_declarator LPAR RPAR { $$ = new_node(PARAM_LIST_NODE, 0, NO_TYPE); }
	;

parameter_list
	: parameter_declaration {argsCount++; $$ = new_subtree(PARAM_LIST_NODE, NO_TYPE, 1, $1); }
	| parameter_list COMMA parameter_declaration {argsCount++; add_child($1, $3); $$ = $1; }
	;

parameter_declaration
	: type_specifier declarator { $$ = $2; }
	| type_specifier 
	;

initializer
	: expression { $$ = $1; }
	| LCURLY initializer_list RCURLY  { $$ = toArray($2); }
	| LCURLY initializer_list COMMA RCURLY  { $$ = toArray($2); }
	;

initializer_list
	: initializer { $$ = $1; }
	| initializer_list COMMA initializer { $$ = $1; }
	;

statement
	: compound_statement 	{ $$ = $1; }
	| expression_statement 	{ $$ = $1; }
	| selection_statement 	{ $$ = $1; }
	| iteration_statement 	{ $$ = $1; }
	| jump_statement 		{ $$ = $1; }
	;

compound_statement
	: LCURLY RCURLY 
	| LCURLY statement_list RCURLY { $$ = new_subtree(COMPOUND_NODE, NO_TYPE, 1, $2); }
	| LCURLY declaration_list RCURLY { $$ = new_subtree(COMPOUND_NODE, NO_TYPE, 1, $2); }
	| LCURLY declaration_list statement_list RCURLY { $$ = new_subtree(COMPOUND_NODE, NO_TYPE, 2, $2, $3); }
	;

declaration_list
	: declaration					{ $$ = new_subtree(VAR_LIST_NODE, NO_TYPE, 1, $1); }
	| declaration_list declaration	{ add_child($1, $2); $$ = $1; }
	;

statement_list
	: statement                     { $$ = new_subtree(STMT_LIST_NODE, NO_TYPE, 1, $1); }
	| statement_list statement      { add_child($1, $2); $$ = $1; }
	;

expression_statement
	: SEMI
	| expression SEMI { $$ = $1; }
	;

selection_statement
	: IF LPAR expression RPAR compound_statement { $$ = check_if_then($3, $5); }
	| IF LPAR expression RPAR compound_statement ELSE compound_statement { $$ = check_if_then_else($3, $5, $7); }
	;

iteration_statement
	: WHILE LPAR expression RPAR statement { $$ = check_while($3, $5); }
	;

jump_statement
	: CONTINUE SEMI 			{ $$ = new_subtree(CONTINUE_NODE, NO_TYPE, 0); }
	| BREAK SEMI 				{ $$ = new_subtree(BREAK_NODE, NO_TYPE, 0); }
	| RETURN SEMI 				{ $$ = new_subtree(RETURN_NODE, NO_TYPE, 0); }
	| RETURN expression SEMI 	{ $$ = new_subtree(RETURN_NODE, NO_TYPE, 1, $2);} 
	;

translation_unit
	: external_declaration { root = new_subtree(PROGRAM_NODE, NO_TYPE, 1, $1); add_child(root, new_node(FUNCTION_NODE, 0, NO_TYPE)); add_child(root, new_node(FUNCTION_NODE, 1, NO_TYPE));}
	| translation_unit external_declaration { add_child(root, $2);}
	;

external_declaration
	: function_definition { scopeCount++;  $$ = $1;}
	;

function_definition
	: type_specifier function_declarator compound_statement { $$ = new_subtree(FUNCTION_NODE, get_type_func(funcTable,scopeCount), 2, $2, $3); set_data($$, scopeCount); set_args_count_func(funcTable, scopeCount, argsCount); argsCount = 0;}
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

	newFunc("scanf", 0);
	newFunc("printf", 0);
	scopeCount = 2;

    yyparse();
    // printf("PARSE SUCCESSFUL!\n");
	// print_str_table(strTable);
	// print_func_table(funcTable);

	// print_dot(root);
	run_ast(root);

	free_str_table(strTable);
	free_func_table(funcTable);
    free_tree(root);
    yylex_destroy();    // To avoid memory leaks within flex...
    return 0;
}


AST* newVar(char* str){
	VarTable* vt = get_var_table_func(funcTable,scopeCount);
    int index = lookup_var(vt, str);

	if(index != -1){
		printf("SEMANTIC ERROR (%d): variable ’%s’ already declared at line %d.\n", yylineno, str, get_line(vt, index));
		exit(EXIT_FAILURE);
	}

	add_func_var(funcTable, str, yylineno, type, scopeCount);
	return new_node(VAR_DECL_NODE, lookup_var(vt, str), type);
}

void newArrayVar(){
	set_func_last_var_type(funcTable, scopeCount);
}


AST* checkVar(char* str){
	VarTable* vt = get_var_table_func(funcTable,scopeCount);
    int indexVar = lookup_var(vt, str);
	int indexFunc = lookup_func(funcTable, str);

	if ( indexVar == -1 && indexFunc == -1) {
        printf("SEMANTIC ERROR (%d): variable ’%s’ was never declared.\n", yylineno, str);
		exit(EXIT_FAILURE);
    }

	if(indexFunc != -1){
		return new_node(FUNC_USE_NODE, indexFunc, get_type_func(funcTable, indexFunc));
	} else {
		return new_node(VAR_USE_NODE, indexVar, get_type(vt,indexVar));
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

void assign_array_error(Type t) {
	printf("SEMANTIC ERROR (%d): cannot assign an '%s' type.\n",
           yylineno, get_text(t));
    exit(EXIT_FAILURE);
}

AST* unify_bin_op(AST* nodeL, AST* nodeR, NodeKind kind, const char* op, Type (*unify)(Type,Type)) {
	Type l = get_node_type(nodeL);
	Type r = get_node_type(nodeR);
    Type unif = unify(l, r);
    if (unif == NO_TYPE) {
        type_error(op, l, r);
    }
    return new_subtree(kind, unif, 2, nodeL, nodeR);
}

AST* check_number(AST* node){
	Type t = get_node_type(node);
	if(t != INT_TYPE && t != FLOAT_TYPE){
		printf("SEMANTIC ERROR (%d): not a number.\n", yylineno);
    	exit(EXIT_FAILURE);
	}

	return node;
}

AST* check_assign(AST* nodeL, AST* nodeR) {
	Type l = get_node_type(nodeL);
	Type r = get_node_type(nodeR);

	if (l == INT_ARRAY_TYPE  || r == INT_ARRAY_TYPE)  assign_array_error(l);
	if (l == FLOAT_ARRAY_TYPE  || r == FLOAT_ARRAY_TYPE)  assign_array_error(l);
	if (l == CHAR_ARRAY_TYPE  || r == CHAR_ARRAY_TYPE)  assign_array_error(l);

	if (l == VOID_TYPE  || r == VOID_TYPE)  type_error("=", l, r);
	if (l == FLOAT_TYPE && !(r == INT_TYPE || r == FLOAT_TYPE)) type_error("=", l, r);
    if (l == CHAR_TYPE  && r != CHAR_TYPE)  type_error("=", l, r);
    if (l == INT_TYPE  && r != INT_TYPE)  type_error("=", l, r);
    
	return new_subtree(ASSIGN_NODE, NO_TYPE, 2, nodeL, nodeR);
}

AST* check_declarator_assign(AST* nodeL, AST* nodeR) {
	Type l = get_node_type(nodeL);
	Type r = get_node_type(nodeR);

	if (l == INT_ARRAY_TYPE  && r != INT_ARRAY_TYPE)  assign_array_error(l);
	if (l == FLOAT_ARRAY_TYPE  && !(r == INT_ARRAY_TYPE || r == FLOAT_ARRAY_TYPE))  assign_array_error(l);
	if (l == CHAR_ARRAY_TYPE  && r != CHAR_ARRAY_TYPE)  assign_array_error(l);

	if (l == VOID_TYPE  || r == VOID_TYPE)  type_error("=", l, r);
	if (l == FLOAT_TYPE && !(r == INT_TYPE || r == FLOAT_TYPE)) type_error("=", l, r);
    if (l == CHAR_TYPE  && r != CHAR_TYPE)  type_error("=", l, r);
    if (l == INT_TYPE  && r != INT_TYPE)  type_error("=", l, r);
    
	return new_subtree(ASSIGN_NODE, NO_TYPE, 2, nodeL, nodeR);
}

AST* check_int(AST* nodeL, AST* nodeR, NodeKind kind) {
	Type l = get_node_type(nodeL);
	Type r = get_node_type(nodeR);

	if (l != INT_TYPE  || r != INT_TYPE) type_error("not int", l, r);

	return new_subtree(kind, INT_TYPE, 2, nodeL, nodeR);
}


AST* toPrimitive(AST* node) {
	Type t = get_node_type(node);

	if (t == INT_ARRAY_TYPE) t = INT_TYPE;  
	else if (t == FLOAT_ARRAY_TYPE) t = FLOAT_TYPE;
	else if (t == CHAR_ARRAY_TYPE) t = CHAR_TYPE; 
	else {	
		printf("SEMANTIC ERROR (%d): variable has no primitive type.\n", yylineno);
		exit(EXIT_FAILURE);
	}

	set_node_type(node, t);
	return node;
}

AST* toArray(AST* node) {
	Type t = get_node_type(node);

	if (t == INT_TYPE) t = INT_ARRAY_TYPE;  
	if (t == FLOAT_TYPE) t = FLOAT_ARRAY_TYPE;
	if (t == CHAR_TYPE) t = CHAR_ARRAY_TYPE; 

	set_node_type(node, t);
	return node;
}

AST* check_if_then(AST *e, AST *b) {
    check_bool_expr("if", get_node_type(e));
    return new_subtree(IF_NODE, NO_TYPE, 2, e, b);
}

AST* check_if_then_else(AST *e, AST *b1, AST *b2) {
    check_bool_expr("if", get_node_type(e));
    return new_subtree(IF_NODE, NO_TYPE, 3, e, b1, b2);
}

AST* check_while(AST *e, AST *b) {
    check_bool_expr("while", get_node_type(e));
    return new_subtree(WHILE_NODE, NO_TYPE, 2, b, e);
}

void check_bool_expr(const char* cmd, Type t) {
    if (t != INT_TYPE) {
        printf("SEMANTIC ERROR (%d): conditional expression in '%s' is '%s' instead of '%s'.\n",
           yylineno, cmd, get_text(t), get_text(INT_TYPE));
    exit(EXIT_FAILURE);
    }
}

