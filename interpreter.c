
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "tables.h"

// ----------------------------------------------------------------------------

extern StrTable *strTable;
extern FunctionTable* funcTable;
AST* functionList[100];

typedef union {
    int   as_int;
    float as_float;
} Word;

// ----------------------------------------------------------------------------

// Frame stack ----------------------------------------------------------------

#define STACK_SIZE 100
#define MEM_SIZE 100
void init_stack();
void init_mem();

typedef struct {
    Word stack[STACK_SIZE];
    int sp; // stack pointer
    Word mem[MEM_SIZE];
} FrameStack;

#define FRAME_STACK_SIZE 100

FrameStack frameStack[FRAME_STACK_SIZE];
int frameStackPtr; // frame stack pointer

void pushFrame() {
    if (frameStackPtr < FRAME_STACK_SIZE - 1) {
        frameStackPtr++;
        frameStack[frameStackPtr].sp = -1; // Initialize stack pointer for the new frame
        init_stack(); // Initialize the stack of the new frame
        init_mem(); // Initialize the memory of the new frame
    } else {
        fprintf(stderr, "Frame stack overflow!\n");
        exit(EXIT_FAILURE);
    }
}

void popFrame() {
    if (frameStackPtr >= 0) {
        frameStackPtr--;
    } else {
        fprintf(stderr, "Frame stack underflow!\n");
        exit(EXIT_FAILURE);
    }
}

FrameStack* getCurrentFrame() {
    return &frameStack[frameStackPtr];
}

// ----------------------------------------------------------------------------

// Data stack -----------------------------------------------------------------

#define stack (getCurrentFrame()->stack)
#define sp (getCurrentFrame()->sp)

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

#define mem (getCurrentFrame()->mem)

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

#define run_bin_op()                \
    AST *lexpr = get_child(ast, 0); \
    AST *rexpr = get_child(ast, 1); \
    rec_run_ast(lexpr);             \
    rec_run_ast(rexpr)

void run_cmp(AST *ast, int (*int_cmp)(int,int), int (*real_cmp)(float,float)) {
    run_bin_op();

    if (get_node_type(rexpr) == INT_TYPE) {
        int r = popi();
        int l = popi();
        pushi(int_cmp(l, r));
    } 
    else { // Result is REAL_TYPE.
        float r = popf();
        float l = popf();
        pushi(real_cmp(l,r));
    }
}

int int_eq(int l, int r) {
    return l == r;
}

int float_eq(float l, float r) {
    return l == r;
}

int int_n_eq(int l, int r) {
    return l != r;
}

int float_n_eq(float l, float r) {
    return l != r;
}

int int_lt(int l, int r) {
    return l < r;
}

int float_lt(float l, float r) {
    return l < r;
}

int int_gt(int l, int r) {
    return l > r;
}

int float_gt(float l, float r) {
    return l > r;
}

int int_lte(int l, int r) {
    return l <= r;
}

int float_lte(float l, float r) {
    return l <= r;
}

int int_gte(int l, int r) {
    return l >= r;
}

int float_gte(float l, float r) {
    return l >= r;
}

int int_l_and(int l, int r) {
    return l && r;
}

int float_l_and(float l, float r) {
    return l && r;
}

int int_l_or(int l, int r) {
    return l || r;
}

int float_l_or(float l, float r) {
    return l || r;
}

void run_other_arith(AST *ast, int (*int_op)(int,int), float (*real_op)(float,float)) {
    run_bin_op();
    if (get_node_type(ast) == INT_TYPE) {
        int r = popi();
        int l = popi();
        pushi(int_op(l,r));
    } else { // Result must be FLOAT_TYPE.
        float r = popf();
        float l = popf();
        pushf(real_op(l,r));
    }
}

int int_minus(int l, int r) {
    return l - r;
}

float float_minus(float l, float r) {
    return l - r;
}

int int_over(int l, int r) {
    return l / r;
}

float float_over(float l, float r) {
    return l / r;
}

int int_times(int l, int r) {
    return l * r;
}

float float_times(float l, float r) {
    return l * r;
}

void plus_int(AST *ast) {
    run_bin_op();
    int r = popi();
    int l = popi();
    pushi(l + r);
}

void plus_real(AST *ast) {
    run_bin_op();
    float r = popf();
    float l = popf();
    pushf(l + r);
}

void run_plus(AST *ast) {
    trace("plus");
    Type plus_type = get_node_type(ast);
    switch(plus_type) {
        case INT_TYPE:  plus_int(ast);     break;
        case FLOAT_TYPE: plus_real(ast);    break;
        case NO_TYPE:
        default:
            fprintf(stderr, "Invalid type: %s!\n", get_text(plus_type));
            exit(EXIT_FAILURE);
    }
}

void store(AST *ast) {
    int var_idx = get_data(ast);
    Type var_type = get_node_type(ast);

    switch(var_type) {
        case INT_TYPE:  storei(var_idx, popi());     break;
        case FLOAT_TYPE: storef(var_idx, popf());    break;
        case NO_TYPE:
        default:
            fprintf(stderr, "Invalid type: %s!\n", get_text(var_type));
            exit(EXIT_FAILURE);
    }
}

// ----------------------------------------------------------------------------

void run_program(AST *ast) {
    trace("program");
    AST* child;

    for(int i = 0; i < get_child_count(ast); i++){
        child = get_child(ast, i);
        functionList[get_data(child)] = child;
    }
    
    pushFrame();
    int childCount = get_child_count(ast) - 1;
    if(childCount == 2) childCount = 0;

    rec_run_ast(get_child(ast, childCount)); // chamanda a ultima funcao MAIN
    popFrame();
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
    trace("param_list");
    Type type;
    int idx;
    AST* child;

    for(int i = get_child_count(ast) - 1; i >= 0; i--){
        child = get_child(ast, i);
        idx = get_data(child);
        type = get_node_type(child);
        if(type == INT_TYPE || type == CHAR_TYPE){
            storei(idx, popi());
        } else if(type == FLOAT_TYPE){
            storef(idx, popf());
        }
    }
}

void run_var_list(AST *ast) {
    trace("var_list");

    for(int i = 0; i < get_child_count(ast); i++){
        rec_run_ast(get_child(ast, i));
    }
}

void run_stmt_list(AST *ast) {
    trace("stmt_list");

    for(int i = 0; i < get_child_count(ast); i++){
        rec_run_ast(get_child(ast, i));
    }
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
    if(type == INT_TYPE || type == CHAR_TYPE){
        storei(idx, popi());
    } else if(type == FLOAT_TYPE){
        storef(idx, popf());
    }
}

void run_if(AST *ast) {
    trace("if");
    rec_run_ast(get_child(ast, 0));
    int test = popi();
    if (test != 0) {
        rec_run_ast(get_child(ast, 1));
    } else if (test == 0 && get_child_count(ast) == 3) {
        rec_run_ast(get_child(ast, 2));
    }
}

void run_while(AST *ast) {
    trace("while");
    rec_run_ast(get_child(ast, 1));
    int test = popi();
    while(test){
        rec_run_ast(get_child(ast, 0));
        rec_run_ast(get_child(ast, 1));
        test = popi();
    }
}

void run_write(AST *ast, Type type) {
    trace("write");
    switch(type) {
        case INT_TYPE:  write_int();    break;
        case FLOAT_TYPE: write_real();   break;
        case CHAR_TYPE:  write_int();    break;
        case NO_TYPE:
        default:
            fprintf(stderr, "Invalid type: %s!\n", get_text(type));
            exit(EXIT_FAILURE);
    }
}

void run_func_use(AST *ast) {
    trace("func_use");
    int scope = get_data(ast);
    AST* args = get_child(ast, 0);
    AST* child;
    Type returnType;
    int intAux;
    float floatAux;

    if(scope != 1 && scope != 0) {
        pushFrame();

        rec_run_ast(args); // arg list
        rec_run_ast(functionList[scope]); //function
        returnType = get_node_type(functionList[scope]);

        if(returnType == INT_TYPE || returnType == CHAR_TYPE){
            intAux = popi();
            popFrame();
            pushi(intAux);
        } else if(returnType == FLOAT_TYPE){
            floatAux = popf();
            popFrame();
            pushf(floatAux);
        } else { popFrame(); }

    } else { // scanf and printf
        for(int i = 0; i<get_child_count(args); i++){
            child = get_child(args, i);
            rec_run_ast(child);
            run_write(args, get_node_type(child));
        }
    }
}

void run_arg_list(AST *ast) {
    trace("arg_list");
    AST* child;

    for(int i = 0; i < get_child_count(ast); i++){
        child = get_child(ast, i);
        rec_run_ast(child);
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

void run_char_val(AST *ast) {
    trace("char_val");
    pushi(get_char_data(ast));
}

void run_eq(AST *ast) {
    trace("eq");
    run_cmp(ast, int_eq, float_eq);
}

void run_n_eq(AST *ast) {
    trace("n_eq");
    run_cmp(ast, int_n_eq, float_n_eq);
}

void run_lt(AST *ast) {
    trace("lt");
    run_cmp(ast, int_lt, float_lt);
}

void run_gt(AST *ast) {
    trace("gt");
    run_cmp(ast, int_lt, float_lt);
}

void run_lte(AST *ast) {
    trace("lte");
    run_cmp(ast, int_lte, float_lte);
}

void run_gte(AST *ast) {
    trace("gte");
    run_cmp(ast, int_gte, float_gte);
}

void run_l_and(AST *ast) {
    trace("l_and");
    run_cmp(ast, int_l_and, float_l_and);
}

void run_l_or(AST *ast) {
    trace("l_or");
    run_cmp(ast, int_l_or, float_l_or);
}

void run_var_use(AST *ast) {
    trace("var_use");
    int var_idx = get_data(ast);
    if (get_node_type(ast) == FLOAT_TYPE) {
        pushf(loadf(var_idx));
    } else {
        pushi(loadi(var_idx));
    }
}

void run_minus(AST *ast) {
    trace("minus");
    run_other_arith(ast, int_minus, float_minus);
}

void run_over(AST *ast) {
    trace("over");
    run_other_arith(ast, int_over, float_over);
}

void run_times(AST *ast) {
    trace("times");
    run_other_arith(ast, int_times, float_times);
}

void run_i2f(AST *ast) {
    trace("i2f");
    rec_run_ast(get_child(ast, 0));
    pushf((float) popi());
}

void run_return(AST *ast) {
    trace("return");

    rec_run_ast(get_child(ast, 0));
}

void run_t_asgn(AST *ast) {
    trace("t_asgn");
    run_times(ast);
    store(get_child(ast, 0));
}

void run_o_asgn(AST *ast) {
    trace("o_asgn");
    run_over(ast);
    store(get_child(ast, 0));
}

void run_pl_asgn(AST *ast) {
    trace("pl_asgn");
    run_plus(ast);
    store(get_child(ast, 0));
}

void run_m_asgn(AST *ast) {
    trace("m_asgn");
    run_minus(ast);
    store(get_child(ast, 0));
}

void rec_run_ast(AST *ast) {

    switch(get_kind(ast)) {

        case ASSIGN_NODE:          run_assign(ast);             break;
        case IF_NODE:              run_if(ast);                 break;
        case INT_VAL_NODE:         run_int_val(ast);            break; 
        case FLOAT_VAL_NODE:       run_float_val(ast);          break; 
        case CHAR_VAL_NODE:        run_char_val(ast);           break; 
        // case INT_ARRAY_VAL_NODE:   run_int_array_val(ast);      break; 
        // case FLOAT_ARRAY_VAL_NODE: run_float_array_val(ast);    break; 
        // case CHAR_ARRAY_VAL_NODE:  run_char_array_val(ast);     break; 
        case LT_NODE:              run_lt(ast);                 break; 
        case GT_NODE:              run_gt(ast);                 break; 
        case LT_EQ_NODE:           run_lte(ast);                break; 
        case GT_EQ_NODE:           run_gte(ast);                break; 
        case EQ_NODE:              run_eq(ast);                 break; 
        case MINUS_NODE:           run_minus(ast);              break; 
        case OVER_NODE:            run_over(ast);               break; 
        case PLUS_NODE:            run_plus(ast);               break; 
        case TIMES_NODE:           run_times(ast);              break; 
        // case PERCENT_NODE:         run_percent(ast);            break; 
        case N_EQ_NODE:            run_n_eq(ast);               break; 
        case T_ASGN_NODE:          run_t_asgn(ast);             break; 
        case O_ASGN_NODE:          run_o_asgn(ast);             break; 
        // case MOD_ASGN_NODE:        run_mod_asgn(ast);           break; 
        case PL_ASGN_NODE:         run_pl_asgn(ast);            break; 
        case M_ASGN_NODE:          run_m_asgn(ast);             break; 
        case L_AND_NODE:           run_l_and(ast);              break; 
        case L_OR_NODE:            run_l_or(ast);               break; 
        case PROGRAM_NODE:         run_program(ast);            break;
        case COMPOUND_NODE:        run_compound(ast);           break;
        case STMT_LIST_NODE:       run_stmt_list(ast);          break;
        case FUNCTION_NODE:        run_function(ast);           break;
        case PARAM_LIST_NODE:      run_param_list(ast);         break;
        case ARG_LIST_NODE:        run_arg_list(ast);           break;
        case WHILE_NODE:           run_while(ast);              break;
        case RETURN_NODE:          run_return(ast);             break;
        // case CONTINUE_NODE:        run_continue(ast);           break;
        // case BREAK_NODE:           run_break(ast);              break;
        case VAR_DECL_NODE:        run_var_decl(ast);           break; 
        case VAR_LIST_NODE:        run_var_list(ast);           break; 
        case VAR_USE_NODE:         run_var_use(ast);            break; 
        case FUNC_USE_NODE:        run_func_use(ast);           break; 
        case I2F_NODE:             run_i2f(ast);                 break; 

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
