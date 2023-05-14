
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tables.h"

// Strings Table
// ----------------------------------------------------------------------------

#define STRING_MAX_SIZE 128
#define STRINGS_TABLE_MAX_SIZE 100

struct str_table {
    char t[STRINGS_TABLE_MAX_SIZE][STRING_MAX_SIZE];
    int size;
};

StrTable* create_str_table() {
    StrTable *st = malloc(sizeof * st);
    st->size = 0;
    return st;
}

int add_string(StrTable* st, char* s) {
    for (int i = 0; i < st->size; i++) {
        if (strcmp(st->t[i], s) == 0) {
            return i;
        }
    }
    strcpy(st->t[st->size], s);
    int idx_added = st->size;
    st->size++;
    return idx_added;
}

char* get_string(StrTable* st, int i) {
    return st->t[i];
}

void print_str_table(StrTable* st) {
    printf("\nStrings table:\n");
    for (int i = 0; i < st->size; i++) {
        printf("Entry %d -- %s\n", i, get_string(st, i));
    }
}

void free_str_table(StrTable* st) {
    free(st);
}

// Variables Table
// ----------------------------------------------------------------------------

#define VARIABLE_MAX_SIZE 128
#define VARIABLES_TABLE_MAX_SIZE 100

typedef struct {
  char name[VARIABLE_MAX_SIZE];
  int line;
  Type type;
} Entry;

struct var_table {
    Entry t[VARIABLES_TABLE_MAX_SIZE];
    int size;
};

VarTable* create_var_table() {
    VarTable *vt = malloc(sizeof * vt);
    vt->size = 0;
    return vt;
}

int lookup_var(VarTable* vt, char* s) {
    for (int i = 0; i < vt->size; i++) {
        if (strcmp(vt->t[i].name, s) == 0)  {
            return i;
        }
    }
    return -1;
}

int add_var(VarTable* vt, char* s, int line, Type type) {
    strcpy(vt->t[vt->size].name, s);

    vt->t[vt->size].line = line;
    vt->t[vt->size].type = type;
    int idx_added = vt->size;
    vt->size++;
    return idx_added;
}

char* get_name(VarTable* vt, int i) {
    return vt->t[i].name;
}

int get_line(VarTable* vt, int i) {
    return vt->t[i].line;
}

Type get_type(VarTable* vt, int i) {
    return vt->t[i].type;
}

void print_var_table(VarTable* vt) {
    printf("\tVariables table:\n");
    for (int i = 0; i < vt->size; i++) {
         printf("\tEntry %d -- name: %s, line: %d, type: %s\n", i,
                get_name(vt, i), get_line(vt, i), get_text(get_type(vt, i)));
    }
}

void free_var_table(VarTable* vt) {
    free(vt);
}


// Function Table
// ----------------------------------------------------------------------------


#define FUNCTION_MAX_SIZE 128
#define FUNCTIONS_TABLE_MAX_SIZE 100

typedef struct {
  char name[FUNCTION_MAX_SIZE];
  int line;
  int args;
  VarTable* localVarTable;
  Type type;
} Entry2;

struct func_table {
    Entry2 t[FUNCTIONS_TABLE_MAX_SIZE];
    int size;
};

FunctionTable* create_func_table() {
    FunctionTable *ft = malloc(sizeof * ft);
    ft->size = 0;
    return ft;
}

int lookup_func(FunctionTable* ft, char* s) {
    for (int i = 0; i < ft->size; i++) {
        if (strcmp(ft->t[i].name, s) == 0)  {
            return i;
        }
    }
    return -1;
}

int add_func(FunctionTable* ft, char* s, int line, int args, Type type) {
    ft->t[ft->size].localVarTable = create_var_table();

    strcpy(ft->t[ft->size].name, s);
    ft->t[ft->size].line = line;
    ft->t[ft->size].type = type;
    ft->t[ft->size].args = args;

    int idx_added = ft->size;
    ft->size++;

    return idx_added;
}

void add_func_var(FunctionTable* ft, char* s, int line, Type type, int scope){
    add_var(ft->t[scope].localVarTable, s, line, type);
}

char* get_name_func(FunctionTable* ft, int i) {
    return ft->t[i].name;
}

int get_line_func(FunctionTable* ft, int i) {
    return ft->t[i].line;
}

Type get_type_func(FunctionTable* ft, int i) {
    return ft->t[i].type;
}

VarTable* get_var_table_func(FunctionTable* ft, int scope) {
    return ft->t[scope].localVarTable;
}

void print_func_table(FunctionTable* ft) {
    printf("\nFunctions table:\n");
    for (int i = 0; i < ft->size; i++) {
        printf("Entry %d -- name: %s, line: %d, returnType: %s\n", i,
            get_name_func(ft, i), get_line_func(ft, i), get_text(get_type_func(ft, i)));

        print_var_table(ft->t[i].localVarTable);
    }
}

void free_func_table(FunctionTable* ft) {
    for(int i = 0; i < ft->size; i++){
        free_var_table(ft->t[i].localVarTable);
    }
    free(ft);
}
