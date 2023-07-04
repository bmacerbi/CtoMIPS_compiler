
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "tables.h"

// ----------------------------------------------------------------------------

extern StrTable *strTable;
// extern VarTable *vt;

typedef union {
    int   as_int;
    float as_float;
} Word;

// ----------------------------------------------------------------------------

// Data stack -----------------------------------------------------------------

#define STACK_SIZE 100

Word stack[STACK_SIZE];
int sp; // stack pointer

// All these ops should have a boundary check, buuuut... X_X

void pushi(int x) {
    stack[++sp].as_int = x;
}

int popi() {
    return stack[sp--].as_int;
}

void pushf(float x) {
    stack[++sp].as_float = x;
}

float popf() {
    return stack[sp--].as_float;
}

void init_stack() {
    for (int i = 0; i < STACK_SIZE; i++) {
        stack[i].as_int = 0;
    }
    sp = -1;
}

void print_stack() {
    printf("*** STACK: ");
    for (int i = 0; i <= sp; i++) {
        printf("%d ", stack[i].as_int);
    }
    printf("\n");
}

// ----------------------------------------------------------------------------

// Variables memory -----------------------------------------------------------

#define MEM_SIZE 100

Word mem[MEM_SIZE];

void storei(int addr, int val) {
    mem[addr].as_int = val;
}

int loadi(int addr) {
    return mem[addr].as_int;
}

void storef(int addr, float val) {
    mem[addr].as_float = val;
}

float loadf(int addr) {
    return mem[addr].as_float;
}

void init_mem() {
    for (int addr = 0; addr < MEM_SIZE; addr++) {
        mem[addr].as_int = 0;
    }
}

// ----------------------------------------------------------------------------

// #define TRACE
// #ifdef TRACE
#define trace(msg) printf("TRACE: %s\n", msg)
// #else
// #define trace(msg)
// #endif

#define MAX_STR_SIZE 128
static char str_buf[MAX_STR_SIZE];
#define clear_str_buf() str_buf[0] = '\0'

void rec_run_ast(AST *ast);

void read_int(int var_idx) {
    int x;
    printf("read (int): ");
    scanf("%d", &x);
    storei(var_idx, x);
}

void read_real(int var_idx) {
    float x;
    printf("read (real): ");
    scanf("%f", &x);
    storef(var_idx, x);
}

void read_bool(int var_idx) {
    int x;
    do {
        printf("read (bool - 0 = false, 1 = true): ");
        scanf("%d", &x);
    } while (x != 0 && x != 1);
    storei(var_idx, x);
}

void read_str(int var_idx) {
    printf("read (str): ");
    clear_str_buf();
    scanf("%s", str_buf);   // Did anyone say Buffer Overflow..? ;P
    storei(var_idx, add_string(strTable, str_buf));
}

void write_int() {
    printf("%d\n", popi());
}

void write_real() {
    printf("%f\n", popf());
}

void write_bool() {
    popi() == 0 ? printf("false\n") : printf("true\n");
}

// Helper function to write strings.
void escape_str(const char* s, char *n) {
    int i = 0, j = 0;
    char c;
    while ((c = s[i++]) != '\0') {
        if (c == '"') { continue; }
        else if (c == '\\' && s[i] == 'n') {
            n[j++] = '\n';
            i++;
        } else {
            n[j++] = c;
        }
    }
    n[j] = '\0';
}

void write_str() {
    int s = popi(); // String pointer
    clear_str_buf();
    escape_str(get_string(strTable, s), str_buf); 
    printf(str_buf); // Weird language semantics, if printing a string, no new line.
}

// ----------------------------------------------------------------------------

void run_program(AST *ast) {
    trace("program");
    
    rec_run_ast(get_child(ast, get_child_count(ast) - 1)); // chamanda a ultima funcao MAIN

    // O program chamaria a main apenas por enquanto, nao sei como que ficaria chamada de outras funcoes
}

void run_function(AST *ast) {
    trace("function");
    rec_run_ast(get_child(ast, 0)); // run compound
    rec_run_ast(get_child(ast, 1)); // run param_list
}

void run_compound(AST *ast) {
    trace("compound");

    for(int i = 0; i < get_child_count(ast); i++){ //var_list e stmt_list
        rec_run_ast(get_child(ast, i));
    }
}

void run_param_list(AST *ast) {
    //desempilhar os valores de argumentos e salvar na memoria dos parametros
    //soh deve ser feito quando tiver chamada de funcao pronta
    trace("param_list");

}

void run_var_list(AST *ast) {
    trace("var_list");

    for(int i = 0; i < get_child_count(ast); i++){
        rec_run_ast(get_child(ast, i));
    }
}

void run_stmt_list(AST *ast) {
    trace("stmt_list");

}

void run_var_decl(AST *ast) {
    trace("var_decl");
    // Nothing to do, memory was already cleared upon initialization.
}

void run_assign(AST *ast) {
    trace("assign");
    AST *left_child = get_child(ast, 0);
    AST *right_child = get_child(ast, 1);

    int idx = get_data(left_child);

    rec_run_ast(right_child);

    Type type = get_node_type(left_child);
    if(type == INT_TYPE){
        storei(idx, popi());
    } else if(type == FLOAT_TYPE){
        storef(idx, popf());
    }
}

void run_int_val(AST *ast) {
    trace("int_val");
    pushi(get_data(ast));
}

void run_float_val(AST *ast) {
    trace("float_val");
    pushf(get_float_data(ast));
}

void rec_run_ast(AST *ast) {
    switch(get_kind(ast)) {

        case ASSIGN_NODE:          run_assign(ast);             break;
        // case IF_NODE:              run_if(ast);                 break;
        case INT_VAL_NODE:         run_int_val(ast);            break; 
        case FLOAT_VAL_NODE:       run_float_val(ast);          break; 
        // case CHAR_VAL_NODE:        run_char_val(ast);           break; 
        // case INT_ARRAY_VAL_NODE:   run_int_array_val(ast);      break; 
        // case FLOAT_ARRAY_VAL_NODE: run_float_array_val(ast);    break; 
        // case CHAR_ARRAY_VAL_NODE:  run_char_array_val(ast);     break; 
        // case LT_NODE:              run_lt(ast);                 break; 
        // case GT_NODE:              run_gt(ast);                 break; 
        // case LT_EQ_NODE:           run_lt_eq(ast);              break; 
        // case GT_EQ_NODE:           run_gt_eq(ast);              break; 
        // case EQ_NODE:              run_eq(ast);                 break; 
        // case MINUS_NODE:           run_minus(ast);              break; 
        // case OVER_NODE:            run_over(ast);               break; 
        // case PLUS_NODE:            run_plus(ast);               break; 
        // case TIMES_NODE:           run_times(ast);              break; 
        // case PERCENT_NODE:         run_percent(ast);            break; 
        // case N_EQ_NODE:            run_n_eq(ast);               break; 
        // case T_ASGN_NODE:          run_t_asgn(ast);             break; 
        // case O_ASGN_NODE:          run_o_asgn(ast);             break; 
        // case MOD_ASGN_NODE:        run_mod_asgn(ast);           break; 
        // case PL_ASGN_NODE:         run_pl_asgn(ast);            break; 
        // case M_ASGN_NODE:          run_m_asgn(ast);             break; 
        // case L_AND_NODE:           run_l_and(ast);              break; 
        // case L_OR_NODE:            run_l_or(ast);               break; 
        case PROGRAM_NODE:         run_program(ast);            break;
        case COMPOUND_NODE:        run_compound(ast);           break;
        case STMT_LIST_NODE:       run_stmt_list(ast);          break;
        case FUNCTION_NODE:        run_function(ast);           break;
        case PARAM_LIST_NODE:      run_param_list(ast);         break;
        // case ARG_LIST_NODE:        run_arg_list(ast);           break;
        // case WHILE_NODE:           run_while(ast);              break;
        // case RETURN_NODE:          run_return(ast);             break;
        // case CONTINUE_NODE:        run_continue(ast);           break;
        // case BREAK_NODE:           run_break(ast);              break;
        case VAR_DECL_NODE:        run_var_decl(ast);           break; 
        case VAR_LIST_NODE:        run_var_list(ast);           break; 
        // case VAR_USE_NODE:         run_var_use(ast);            break; 
        // case FUNC_USE_NODE:        run_func_use(ast);           break; 
        // case I2F_NODE:             run_i2(ast);                 break; 

        default:
            fprintf(stderr, "Invalid kind: %s!\n", kind2str(get_kind(ast)));
            exit(EXIT_FAILURE);
    }
}

// ----------------------------------------------------------------------------

void run_ast(AST *ast) {
    init_stack();
    init_mem();
    rec_run_ast(ast);
}