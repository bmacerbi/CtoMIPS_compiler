
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "tables.h"
#include "types.h"

extern StrTable *strTable;

#define CHILDREN_LIMIT 20 // Don't try this at home, kids... :P

struct node {
    NodeKind kind;
    union {
        int   as_int;
        float as_float;
        char  as_char;
    } data;
    Type type;
    int count;
    AST* child[CHILDREN_LIMIT];
};

AST* new_node(NodeKind kind, int data, Type type) {
    AST* node = malloc(sizeof * node);
    node->kind = kind;
    node->data.as_int = data;
    node->type = type;
    node->count = 0;
    for (int i = 0; i < CHILDREN_LIMIT; i++) {
        node->child[i] = NULL;
    }
    return node;
}

void add_child(AST *parent, AST *child) {
    if (parent->count == CHILDREN_LIMIT) {
        fprintf(stderr, "Cannot add another child!\n");
        exit(1);
    }
    parent->child[parent->count] = child;
    parent->count++;
}

AST* get_child(AST *parent, int idx) {
    return parent->child[idx];
}

AST* new_subtree(NodeKind kind, Type type, int child_count, ...) {
    if (child_count > CHILDREN_LIMIT) {
        fprintf(stderr, "Too many children as arguments!\n");
        exit(1);
    }

    AST* node = new_node(kind, 0, type);
    va_list ap;
    va_start(ap, child_count);
    for (int i = 0; i < child_count; i++) {
        add_child(node, va_arg(ap, AST*));
    }
    va_end(ap);
    return node;
}

NodeKind get_kind(AST *node) {
    return node->kind;
}

void set_data(AST *node, int data) {
    node->data.as_int = data;
}

int get_data(AST *node) {
    return node->data.as_int;
}

void set_float_data(AST *node, float data) {
    node->data.as_float = data;
}

float get_float_data(AST *node) {
    return node->data.as_float;
}

void set_char_data(AST *node, char data){
    node->data.as_char = data;
}

char get_char_data(AST *node){
    return node->data.as_char;
}

Type get_node_type(AST *node) {
    return node->type;
}

void set_node_type(AST *node, Type t) {
    node->type = t;
}

int get_child_count(AST *node) {
    return node->count;
}

void free_tree(AST *tree) {
    if (tree == NULL) return;
    for (int i = 0; i < tree->count; i++) {
        free_tree(tree->child[i]);
    }
    free(tree);
}

// Dot output.

int nr;

extern FunctionTable *ft;

char* kind2str(NodeKind kind) {
    switch(kind) {
        case ASSIGN_NODE:          return "=";
        case IF_NODE:              return "if";
        case ELSE_NODE:            return "else";
        case INT_VAL_NODE:         return "";
        case FLOAT_VAL_NODE:       return "";
        case CHAR_VAL_NODE:        return "";
        case INT_ARRAY_VAL_NODE:   return "";
        case FLOAT_ARRAY_VAL_NODE: return "";
        case CHAR_ARRAY_VAL_NODE:  return "";
        case LT_NODE:              return "<";
        case GT_NODE:              return ">";
        case LT_EQ_NODE:           return "<=";
        case GT_EQ_NODE:           return ">=";
        case EQ_NODE:              return "==";
        case MINUS_NODE:           return "-";
        case OVER_NODE:            return "/";
        case PLUS_NODE:            return "+";
        case TIMES_NODE:           return "*";
        case PERCENT_NODE:         return "%";
        case N_EQ_NODE:            return "!=";
        case T_ASGN_NODE:          return "*=";
        case O_ASGN_NODE:          return "/=";
        case MOD_ASGN_NODE:        return "%=";
        case PL_ASGN_NODE:         return "+=";
        case M_ASGN_NODE:          return "-=";
        case L_AND_NODE:           return "&&";
        case L_OR_NODE:            return "||";
        case PROGRAM_NODE:         return "program";
        case COMPOUND_NODE:        return "compound";
        case STMT_LIST_NODE:       return "stmt_list";
        case FUNCTION_NODE:        return "function";
        case PARAM_LIST_NODE:      return "param_list";
        case ARG_LIST_NODE:        return "arg_list";
        case WHILE_NODE:           return "while";
        case VAR_DECL_NODE:        return "var_decl";
        case VAR_LIST_NODE:        return "var_list";
        case VAR_USE_NODE:         return "var_use";
        case FUNC_USE_NODE:        return "func_use";
        case I2F_NODE:             return "I2F";
        default:                   return "ERROR!!";
    }
}

int has_data(NodeKind kind) {
    switch(kind) {
        case INT_VAL_NODE:        
        case FLOAT_VAL_NODE:      
        case CHAR_VAL_NODE:       
        case INT_ARRAY_VAL_NODE:  
        case FLOAT_ARRAY_VAL_NODE:
        case CHAR_ARRAY_VAL_NODE: 
        case VAR_DECL_NODE:
        case VAR_USE_NODE:
            return 1;
        default:
            return 0;
    }
}

int print_node_dot(AST *node) {
    int my_nr = nr++;

    fprintf(stderr, "node%d[label=\"", my_nr);
    if (node->type != NO_TYPE) {
        fprintf(stderr, "(%s) ", get_text(node->type));
    }
    if (node->kind == VAR_DECL_NODE || node->kind == VAR_USE_NODE) {
        // fprintf(stderr, "%s@", get_name(vt, node->data.as_int));
    } else {
        fprintf(stderr, "%s", kind2str(node->kind));
    }
    if (has_data(node->kind)) {
        if (node->kind == FLOAT_VAL_NODE) {
            fprintf(stderr, "%.2f", node->data.as_float);
        } else if (node->kind == CHAR_ARRAY_VAL_NODE) {
            fprintf(stderr, "%s", get_string(strTable, node->data.as_int));
        } else if (node->kind == CHAR_VAL_NODE) {
            fprintf(stderr, "@%d", node->data.as_char);
        } else {
            fprintf(stderr, "%d", node->data.as_int);
        }
    }
    fprintf(stderr, "\"];\n");

    for (int i = 0; i < node->count; i++) {
        int child_nr = print_node_dot(node->child[i]);
        fprintf(stderr, "node%d -> node%d;\n", my_nr, child_nr);
    }
    return my_nr;
}

void print_dot(AST *tree) {
    nr = 0;
    fprintf(stderr, "digraph {\ngraph [ordering=\"out\"];\n");
    print_node_dot(tree);
    fprintf(stderr, "}\n");
}
