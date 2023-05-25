
#include "types.h"

static const char *TYPE_STRING[] = {
    "int",
    "float",
    "char",
    "void"
};

const char* get_text(Type type) {
    return TYPE_STRING[type];
}

static const Type arith[4][4] = {
{INT_TYPE, FLOAT_TYPE, NO_TYPE, NO_TYPE},
{FLOAT_TYPE, FLOAT_TYPE, NO_TYPE, NO_TYPE},
{NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE},
{NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE}
};

static const Type comp[4][4] = {
{INT_TYPE, INT_TYPE, NO_TYPE, NO_TYPE},
{INT_TYPE, INT_TYPE, NO_TYPE, NO_TYPE},
{NO_TYPE, NO_TYPE, INT_TYPE, NO_TYPE},
{NO_TYPE, NO_TYPE, NO_TYPE, NO_TYPE}
};

Type unify_arith(Type lt, Type rt) {
    return arith[lt][rt];
}

Type unify_comp(Type lt, Type rt) {
    return comp[lt][rt];
}