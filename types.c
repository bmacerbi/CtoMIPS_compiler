
#include "types.h"

static const char *TYPE_STRING[] = {
    "int",
    "float",
    "void",
    "char"
};

const char* get_text(Type type) {
    return TYPE_STRING[type];
}
