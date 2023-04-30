%output "parser.c"
%defines "parser.h"
%define parse.error verbose
%define parse.lac full

%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"


int yylex(void);
int yylex_destroy(void);
void yyerror(char const *s);

extern char *yytext;
extern int yylineno;
%}

%token PTR_OP INC DEC LT_EQ GT_EQ LT GT EQ N_EQ L_NOT
%token L_AND L_OR ASGN T_ASGN O_ASGN MOD_ASGN PL_ASGN M_ASGN
%token TYPEDEF EXTERN STATIC AUTO REGISTER INLINE RESTRICT
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token BOOL COMPLEX IMAGINARY
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN
%token ID FLOAT_VAL INT_VAL STR_VAL CHAR_VAL SIZEOF
%token PLUS MINUS TIMES OVER PERCENT LPAR RPAR 
%token LCURLY RCURLY LBRAC RBRAC SEMI COMMA AMPER


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
%precedence UMINUS UPLUS UPTR

%start translation_unit
%%

expression
	: ID
	| FLOAT_VAL
	| INT_VAL
	| STR_VAL
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
	| expression assignment_operator expression
	| expression COMMA expression
	;


argument_expression_list
	: expression
	| argument_expression_list COMMA expression
	;

unary_operator
	: AMPER
	| TIMES
	| PLUS
	| MINUS
	| L_NOT
	;

assignment_operator
	: ASGN
	| T_ASGN
	| O_ASGN
	| MOD_ASGN
	| PL_ASGN
	| M_ASGN
	;

declaration
	: declaration_specifiers SEMI
	| declaration_specifiers init_declarator_list SEMI
	;

declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier
	| type_specifier declaration_specifiers
	| type_qualifier
	| type_qualifier declaration_specifiers
	;

init_declarator_list
	: init_declarator
	| init_declarator_list COMMA init_declarator
	;

init_declarator
	: declarator
	| declarator ASGN initializer
	;

storage_class_specifier
	: TYPEDEF
	| EXTERN
	| STATIC
	| AUTO
	| REGISTER
	;

type_specifier
	: VOID
	| CHAR
	| SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| SIGNED
	| UNSIGNED
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

type_qualifier
	: CONST
	| VOLATILE
	;

declarator
	: pointer direct_declarator
	| direct_declarator
	;

direct_declarator
	: ID
	| LPAR declarator RPAR
	| direct_declarator LBRAC expression RBRAC
	| direct_declarator LBRAC RBRAC
	| direct_declarator LPAR parameter_type_list RPAR
	| direct_declarator LPAR identifier_list RPAR
	| direct_declarator LPAR RPAR
	;

pointer
	: TIMES
	| TIMES type_qualifier_list
	| TIMES pointer
	| TIMES type_qualifier_list pointer
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;


parameter_type_list
	: parameter_list
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
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: LPAR abstract_declarator RPAR
	| LBRAC RBRAC
	| LBRAC expression RBRAC
	| direct_abstract_declarator LBRAC RBRAC
	| direct_abstract_declarator LBRAC expression RBRAC
	| LPAR RPAR
	| LPAR parameter_type_list RPAR
	| direct_abstract_declarator LPAR RPAR
	| direct_abstract_declarator LPAR parameter_type_list RPAR
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
	: ID ':' statement
	| CASE expression ':' statement
	| DEFAULT ':' statement
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
	: IF LPAR expression RPAR statement
	| IF LPAR expression RPAR statement ELSE statement
	| SWITCH LPAR expression RPAR statement
	;

iteration_statement
	: WHILE LPAR expression RPAR statement
	| DO statement WHILE LPAR expression RPAR SEMI
	| FOR LPAR expression_statement expression_statement RPAR statement
	| FOR LPAR expression_statement expression_statement expression RPAR statement
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
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement
	| declarator declaration_list compound_statement
	| declarator compound_statement
	;

%%

// Primitive error handling.
void yyerror (char const *s) {
    printf("SYNTAX ERROR (%d): %s\n", yylineno, s);
    exit(EXIT_FAILURE);
}

int main() {
    yyparse();
    printf("PARSE SUCCESSFUL!\n");
    yylex_destroy();    // To avoid memory leaks within flex...
    return 0;
}