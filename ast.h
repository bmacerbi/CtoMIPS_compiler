#ifndef AST_H
#define AST_H

#include "types.h"

typedef enum {
    ASSIGN_NODE,
    COMPOUND_NODE,
    STMT_LIST_NODE,
    VAR_LIST_NODE,
    IF_NODE,
    ELSE_NODE,
    INT_VAL_NODE,
    FLOAT_VAL_NODE,
    CHAR_VAL_NODE,
    INT_ARRAY_VAL_NODE,
    FLOAT_ARRAY_VAL_NODE,
    CHAR_ARRAY_VAL_NODE,
    LT_NODE,
    GT_NODE,
    LT_EQ_NODE,
    GT_EQ_NODE,
    EQ_NODE,
    MINUS_NODE,
    OVER_NODE,
    PLUS_NODE,
    TIMES_NODE,
    PERCENT_NODE,
    N_EQ_NODE,
    T_ASGN_NODE,
    O_ASGN_NODE,
    MOD_ASGN_NODE,
    PL_ASGN_NODE,
    M_ASGN_NODE,
    L_AND_NODE,
    L_OR_NODE,
    PROGRAM_NODE,
    PARAMS_NODE,
    ARGS_NODE,
    FUNCTION_NODE, 
    PARAM_LIST_NODE,
    ARG_LIST_NODE,
    WHILE_NODE,
    RETURN_NODE,
    CONTINUE_NODE,
    BREAK_NODE,
    VAR_DECL_NODE,
    VAR_USE_NODE,
    FUNC_USE_NODE,
    I2F_NODE
}NodeKind;

struct node; // Opaque structure to ensure encapsulation.

typedef struct node AST;

AST* new_node(NodeKind kind, int data, Type type);

void add_child(AST *parent, AST *child);
AST* get_child(AST *parent, int idx);

AST* new_subtree(NodeKind kind, Type type, int child_count, ...);

NodeKind get_kind(AST *node);
char* kind2str(NodeKind kind);

void set_data(AST *node, int data);
int get_data(AST *node);
void set_float_data(AST *node, float data);
float get_float_data(AST *node);
void set_char_data(AST *node, char data);
char get_char_data(AST *node);

Type get_node_type(AST *node);
void set_node_type(AST *node, Type t);
int get_child_count(AST *node);

void print_tree(AST *ast);
void print_dot(AST *ast);

void free_tree(AST *ast);

#endif
