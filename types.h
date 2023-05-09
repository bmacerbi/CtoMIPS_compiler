
#ifndef TYPES_H
#define TYPES_H

typedef enum {
    INT_TYPE,
    FLOAT_TYPE,
    VOID_TYPE,
    CHAR_TYPE
} Type;

const char* get_text(Type type);

#endif // TYPES_H

