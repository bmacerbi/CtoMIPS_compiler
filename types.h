
#ifndef TYPES_H
#define TYPES_H

typedef enum {
    INT_TYPE,
    FLOAT_TYPE,
    CHAR_TYPE,
    VOID_TYPE,
    INT_ARRAY_TYPE,
    FLOAT_ARRAY_TYPE,
    CHAR_ARRAY_TYPE,
    NO_TYPE
} Type;

const char* get_text(Type type);

Type unify_arith(Type lt, Type rt);
Type unify_comp(Type lt, Type rt);


#endif // TYPES_H

