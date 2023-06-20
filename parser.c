/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 6 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "tables.h"
#include "ast.h"
#include "parser.h"

StrTable* strTable;
VarTable* varTable;
FunctionTable* funcTable;
Type type;
int scopeCount = 0;
int isFunction = 1;
int argsCount =  0;
AST *root;

int yylex(void);
int yylex_destroy(void);
void yyerror(char const *s);
AST* newVar(char* str);
AST* checkVar(char* str);
void newArrayVar();
void newFunc(char* str, int line);
AST* check_number(AST* node);
AST* check_assign(AST* nodeL, AST* nodeR);
AST* check_declarator_assign(AST* nodeL, AST* nodeR);
AST* check_int(AST* nodeL, AST* nodeR, NodeKind kind);
AST* toPrimitive(AST* node);
AST* toArray(AST* node);
AST* check_if_then(AST *e, AST *b);
AST* check_if_then_else(AST *e, AST *b1, AST *b2);
void check_bool_expr(const char* cmd, Type t);
AST* check_while(AST *e, AST *b);

AST* unify_bin_op(AST* nodeL, AST* nodeR, NodeKind kind, const char* op, Type (*unify)(Type,Type));
void type_error(const char* op, Type t1, Type t2);

extern char *yytext;
extern int yylineno;
extern char *idCopy;

#line 114 "parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INC = 3,                        /* INC  */
  YYSYMBOL_DEC = 4,                        /* DEC  */
  YYSYMBOL_LT_EQ = 5,                      /* LT_EQ  */
  YYSYMBOL_GT_EQ = 6,                      /* GT_EQ  */
  YYSYMBOL_LT = 7,                         /* LT  */
  YYSYMBOL_GT = 8,                         /* GT  */
  YYSYMBOL_EQ = 9,                         /* EQ  */
  YYSYMBOL_N_EQ = 10,                      /* N_EQ  */
  YYSYMBOL_L_NOT = 11,                     /* L_NOT  */
  YYSYMBOL_L_AND = 12,                     /* L_AND  */
  YYSYMBOL_L_OR = 13,                      /* L_OR  */
  YYSYMBOL_ASGN = 14,                      /* ASGN  */
  YYSYMBOL_T_ASGN = 15,                    /* T_ASGN  */
  YYSYMBOL_O_ASGN = 16,                    /* O_ASGN  */
  YYSYMBOL_MOD_ASGN = 17,                  /* MOD_ASGN  */
  YYSYMBOL_PL_ASGN = 18,                   /* PL_ASGN  */
  YYSYMBOL_M_ASGN = 19,                    /* M_ASGN  */
  YYSYMBOL_CHAR = 20,                      /* CHAR  */
  YYSYMBOL_INT = 21,                       /* INT  */
  YYSYMBOL_FLOAT = 22,                     /* FLOAT  */
  YYSYMBOL_VOID = 23,                      /* VOID  */
  YYSYMBOL_IF = 24,                        /* IF  */
  YYSYMBOL_ELSE = 25,                      /* ELSE  */
  YYSYMBOL_WHILE = 26,                     /* WHILE  */
  YYSYMBOL_GOTO = 27,                      /* GOTO  */
  YYSYMBOL_CONTINUE = 28,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 29,                     /* BREAK  */
  YYSYMBOL_RETURN = 30,                    /* RETURN  */
  YYSYMBOL_ID = 31,                        /* ID  */
  YYSYMBOL_FLOAT_VAL = 32,                 /* FLOAT_VAL  */
  YYSYMBOL_INT_VAL = 33,                   /* INT_VAL  */
  YYSYMBOL_STR_VAL = 34,                   /* STR_VAL  */
  YYSYMBOL_CHAR_VAL = 35,                  /* CHAR_VAL  */
  YYSYMBOL_PLUS = 36,                      /* PLUS  */
  YYSYMBOL_MINUS = 37,                     /* MINUS  */
  YYSYMBOL_TIMES = 38,                     /* TIMES  */
  YYSYMBOL_OVER = 39,                      /* OVER  */
  YYSYMBOL_PERCENT = 40,                   /* PERCENT  */
  YYSYMBOL_LPAR = 41,                      /* LPAR  */
  YYSYMBOL_RPAR = 42,                      /* RPAR  */
  YYSYMBOL_LCURLY = 43,                    /* LCURLY  */
  YYSYMBOL_RCURLY = 44,                    /* RCURLY  */
  YYSYMBOL_LBRAC = 45,                     /* LBRAC  */
  YYSYMBOL_RBRAC = 46,                     /* RBRAC  */
  YYSYMBOL_SEMI = 47,                      /* SEMI  */
  YYSYMBOL_COMMA = 48,                     /* COMMA  */
  YYSYMBOL_AMPER = 49,                     /* AMPER  */
  YYSYMBOL_COLON = 50,                     /* COLON  */
  YYSYMBOL_UMINUS = 51,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 52,                  /* $accept  */
  YYSYMBOL_expression = 53,                /* expression  */
  YYSYMBOL_argument_expression_list = 54,  /* argument_expression_list  */
  YYSYMBOL_unary_operator = 55,            /* unary_operator  */
  YYSYMBOL_declaration = 56,               /* declaration  */
  YYSYMBOL_init_declarator = 57,           /* init_declarator  */
  YYSYMBOL_type_specifier = 58,            /* type_specifier  */
  YYSYMBOL_declarator = 59,                /* declarator  */
  YYSYMBOL_function_declarator = 60,       /* function_declarator  */
  YYSYMBOL_parameter_list = 61,            /* parameter_list  */
  YYSYMBOL_parameter_declaration = 62,     /* parameter_declaration  */
  YYSYMBOL_initializer = 63,               /* initializer  */
  YYSYMBOL_initializer_list = 64,          /* initializer_list  */
  YYSYMBOL_statement = 65,                 /* statement  */
  YYSYMBOL_compound_statement = 66,        /* compound_statement  */
  YYSYMBOL_declaration_list = 67,          /* declaration_list  */
  YYSYMBOL_statement_list = 68,            /* statement_list  */
  YYSYMBOL_expression_statement = 69,      /* expression_statement  */
  YYSYMBOL_selection_statement = 70,       /* selection_statement  */
  YYSYMBOL_iteration_statement = 71,       /* iteration_statement  */
  YYSYMBOL_jump_statement = 72,            /* jump_statement  */
  YYSYMBOL_translation_unit = 73,          /* translation_unit  */
  YYSYMBOL_external_declaration = 74,      /* external_declaration  */
  YYSYMBOL_function_definition = 75        /* function_definition  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
# define YYCOPY_NEEDED 1
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   842

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  150

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   306


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    75,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   112,   113,   117,   118,   119,
     120,   124,   128,   129,   133,   134,   135,   136,   140,   141,
     142,   146,   147,   148,   152,   153,   157,   158,   162,   163,
     164,   168,   169,   173,   174,   175,   176,   177,   181,   182,
     183,   184,   188,   189,   193,   194,   198,   199,   203,   204,
     208,   212,   213,   214,   215,   219,   220,   224,   228
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INC", "DEC", "LT_EQ",
  "GT_EQ", "LT", "GT", "EQ", "N_EQ", "L_NOT", "L_AND", "L_OR", "ASGN",
  "T_ASGN", "O_ASGN", "MOD_ASGN", "PL_ASGN", "M_ASGN", "CHAR", "INT",
  "FLOAT", "VOID", "IF", "ELSE", "WHILE", "GOTO", "CONTINUE", "BREAK",
  "RETURN", "ID", "FLOAT_VAL", "INT_VAL", "STR_VAL", "CHAR_VAL", "PLUS",
  "MINUS", "TIMES", "OVER", "PERCENT", "LPAR", "RPAR", "LCURLY", "RCURLY",
  "LBRAC", "RBRAC", "SEMI", "COMMA", "AMPER", "COLON", "UMINUS", "$accept",
  "expression", "argument_expression_list", "unary_operator",
  "declaration", "init_declarator", "type_specifier", "declarator",
  "function_declarator", "parameter_list", "parameter_declaration",
  "initializer", "initializer_list", "statement", "compound_statement",
  "declaration_list", "statement_list", "expression_statement",
  "selection_statement", "iteration_statement", "jump_statement",
  "translation_unit", "external_declaration", "function_definition", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-130)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     101,  -130,  -130,  -130,  -130,   -21,     4,  -130,  -130,  -130,
     -36,  -130,  -130,    -9,    68,  -130,  -130,   -12,   -33,  -130,
     383,   383,  -130,    -4,     0,   -29,   -27,   274,  -130,  -130,
    -130,  -130,  -130,  -130,  -130,   383,  -130,  -130,  -130,   430,
     383,  -130,   -12,  -130,  -130,   115,   150,  -130,  -130,  -130,
    -130,  -130,   -16,  -130,   101,    42,    42,   383,   383,  -130,
    -130,  -130,   475,   608,  -130,  -130,   383,   383,   383,   383,
     383,   383,   383,   383,   383,   383,   383,   383,   383,   383,
     383,   383,   383,   383,   383,   309,   383,  -130,  -130,   -17,
     -11,  -130,  -130,   185,  -130,  -130,   328,  -130,   651,   694,
    -130,  -130,   234,   234,   234,   234,   165,   165,   797,   754,
     737,   737,   737,   737,   737,   737,    42,    42,    -5,    -5,
      -5,  -130,   737,   -20,   520,  -130,   364,  -130,  -130,   564,
      -1,   220,  -130,   383,  -130,   364,   737,  -130,  -130,     7,
    -130,   737,  -130,   -13,    -1,  -130,   255,  -130,  -130,  -130
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    45,    46,    47,    44,     0,     0,    85,    87,    51,
       0,     1,    86,     0,     0,    88,    53,    57,     0,    54,
       0,     0,    40,     0,     0,     0,     0,     0,     2,     3,
       4,     5,     6,    38,    39,     0,    68,    76,    37,     0,
       0,    72,     0,    74,    63,     0,     0,    64,    65,    66,
      67,    48,    56,    52,     0,    13,    14,     0,     0,    81,
      82,    83,     0,     0,    11,    12,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    77,    15,     0,
      42,    70,    73,     0,    69,    75,     0,    55,     0,     0,
      84,     7,    23,    24,    21,    22,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    19,    20,    16,    17,
      18,     9,    35,     0,     0,    41,     0,    71,    50,     0,
       0,     0,    10,     0,     8,     0,    58,    43,    49,    78,
      80,    36,    61,     0,     0,    59,     0,    79,    60,    62
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -130,   -19,  -130,  -130,    23,  -130,    30,    27,  -130,  -130,
      19,  -129,  -130,   -23,   -10,  -130,    29,  -130,  -130,  -130,
    -130,  -130,    70,  -130
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    39,   123,    40,    41,    89,     5,    52,    10,    18,
      19,   137,   143,    43,    44,    45,    46,    47,    48,    49,
      50,     6,     7,     8
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      15,    55,    56,   126,    11,    13,   142,    14,    62,    53,
       9,     1,     2,     3,     4,    54,    63,   149,    59,    51,
      60,    88,   132,    95,     1,     2,     3,     4,   133,    96,
     125,   145,   144,    16,    96,   146,    85,    57,    98,    99,
      86,    58,    14,    17,    42,    64,    65,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   122,   124,    92,    90,
      95,    20,    21,    97,    93,    42,    12,   129,     0,    22,
      82,    83,    84,    85,    17,     0,     0,    86,     1,     2,
       3,     4,    23,     0,    24,     0,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,     0,   136,   140,    35,
       0,    14,    36,     0,   141,    37,   136,    38,    20,    21,
     139,     1,     2,     3,     4,     0,    22,   136,     0,     0,
       0,     0,     0,     0,   147,     1,     2,     3,     4,    23,
       0,    24,     0,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    20,    21,     0,    35,     0,    14,    91,
       0,    22,    37,     0,    38,     0,     0,     0,    64,    65,
      66,    67,    68,    69,    23,     0,    24,     0,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    20,    21,
       0,    35,     0,    14,    94,     0,    22,    37,     0,    38,
       0,    80,    81,    82,    83,    84,    85,     0,     0,    23,
      86,    24,     0,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    20,    21,     0,    35,     0,    14,   127,
       0,    22,    37,     0,    38,     0,     0,    64,    65,     0,
       0,     0,     0,     0,    23,     0,    24,     0,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    20,    21,
       0,    35,     0,    14,     0,     0,    22,    37,     0,    38,
      80,    81,    82,    83,    84,    85,     0,    20,    21,    86,
       0,     0,     0,     0,     0,    22,    28,    29,    30,    31,
      32,    33,    34,     0,     0,     0,    35,     0,   135,   148,
       0,     0,     0,     0,    38,    28,    29,    30,    31,    32,
      33,    34,    20,    21,     0,    35,     0,     0,     0,     0,
      22,    61,     0,    38,     0,     0,     0,     0,     0,     0,
       0,    20,    21,     0,     0,     0,     0,     0,     0,    22,
      28,    29,    30,    31,    32,    33,    34,     0,     0,     0,
      35,   121,     0,     0,     0,     0,     0,     0,    38,    28,
      29,    30,    31,    32,    33,    34,     0,    20,    21,    35,
       0,     0,     0,     0,   128,    22,     0,    38,     0,     0,
       0,     0,     0,     0,     0,     0,    20,    21,     0,     0,
       0,     0,     0,     0,    22,    28,    29,    30,    31,    32,
      33,    34,     0,     0,     0,    35,     0,   135,     0,     0,
       0,     0,     0,    38,    28,    29,    30,    31,    32,    33,
      34,     0,     0,     0,    35,     0,     0,     0,     0,     0,
       0,     0,    38,    64,    65,    66,    67,    68,    69,    70,
      71,     0,    72,    73,    74,    75,    76,    77,    78,    79,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    80,    81,    82,    83,
      84,    85,     0,     0,     0,    86,     0,    87,    64,    65,
      66,    67,    68,    69,    70,    71,     0,    72,    73,    74,
      75,    76,    77,    78,    79,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    80,    81,    82,    83,    84,    85,     0,     0,     0,
      86,     0,   100,    64,    65,    66,    67,    68,    69,    70,
      71,     0,    72,    73,    74,    75,    76,    77,    78,    79,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    80,    81,    82,    83,
      84,    85,     0,     0,     0,    86,   134,    64,    65,    66,
      67,    68,    69,    70,    71,     0,    72,    73,    74,    75,
      76,    77,    78,    79,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      80,    81,    82,    83,    84,    85,     0,     0,     0,    86,
     138,    64,    65,    66,    67,    68,    69,    70,    71,     0,
      72,    73,    74,    75,    76,    77,    78,    79,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    80,    81,    82,    83,    84,    85,
     101,     0,     0,    86,    64,    65,    66,    67,    68,    69,
      70,    71,     0,    72,    73,    74,    75,    76,    77,    78,
      79,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    80,    81,    82,
      83,    84,    85,   130,     0,     0,    86,    64,    65,    66,
      67,    68,    69,    70,    71,     0,    72,    73,    74,    75,
      76,    77,    78,    79,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      80,    81,    82,    83,    84,    85,   131,     0,     0,    86,
      64,    65,    66,    67,    68,    69,    70,    71,     0,    72,
      73,    74,    75,    76,    77,    78,    79,    64,    65,    66,
      67,    68,    69,    70,    71,     0,    72,     0,     0,     0,
       0,     0,     0,    80,    81,    82,    83,    84,    85,     0,
       0,     0,    86,     0,     0,     0,     0,     0,     0,     0,
      80,    81,    82,    83,    84,    85,     0,     0,     0,    86,
      64,    65,    66,    67,    68,    69,    70,    71,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    80,    81,    82,    83,    84,    85,     0,
       0,     0,    86
};

static const yytype_int16 yycheck[] =
{
      10,    20,    21,    14,     0,    41,   135,    43,    27,    42,
      31,    20,    21,    22,    23,    48,    35,   146,    47,    31,
      47,    40,    42,    46,    20,    21,    22,    23,    48,    45,
      47,    44,    25,    42,    45,    48,    41,    41,    57,    58,
      45,    41,    43,    13,    14,     3,     4,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    45,    42,
      93,     3,     4,    54,    45,    45,     6,    96,    -1,    11,
      38,    39,    40,    41,    54,    -1,    -1,    45,    20,    21,
      22,    23,    24,    -1,    26,    -1,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,   126,   131,    41,
      -1,    43,    44,    -1,   133,    47,   135,    49,     3,     4,
     130,    20,    21,    22,    23,    -1,    11,   146,    -1,    -1,
      -1,    -1,    -1,    -1,   144,    20,    21,    22,    23,    24,
      -1,    26,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,     3,     4,    -1,    41,    -1,    43,    44,
      -1,    11,    47,    -1,    49,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,    24,    -1,    26,    -1,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,     3,     4,
      -1,    41,    -1,    43,    44,    -1,    11,    47,    -1,    49,
      -1,    36,    37,    38,    39,    40,    41,    -1,    -1,    24,
      45,    26,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,     3,     4,    -1,    41,    -1,    43,    44,
      -1,    11,    47,    -1,    49,    -1,    -1,     3,     4,    -1,
      -1,    -1,    -1,    -1,    24,    -1,    26,    -1,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,     3,     4,
      -1,    41,    -1,    43,    -1,    -1,    11,    47,    -1,    49,
      36,    37,    38,    39,    40,    41,    -1,     3,     4,    45,
      -1,    -1,    -1,    -1,    -1,    11,    31,    32,    33,    34,
      35,    36,    37,    -1,    -1,    -1,    41,    -1,    43,    44,
      -1,    -1,    -1,    -1,    49,    31,    32,    33,    34,    35,
      36,    37,     3,     4,    -1,    41,    -1,    -1,    -1,    -1,
      11,    47,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,    -1,    -1,    -1,    -1,    -1,    -1,    11,
      31,    32,    33,    34,    35,    36,    37,    -1,    -1,    -1,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    49,    31,
      32,    33,    34,    35,    36,    37,    -1,     3,     4,    41,
      -1,    -1,    -1,    -1,    46,    11,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,    -1,    -1,
      -1,    -1,    -1,    -1,    11,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    -1,    41,    -1,    43,    -1,    -1,
      -1,    -1,    -1,    49,    31,    32,    33,    34,    35,    36,
      37,    -1,    -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    49,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,    39,
      40,    41,    -1,    -1,    -1,    45,    -1,    47,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      45,    -1,    47,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,    39,
      40,    41,    -1,    -1,    -1,    45,    46,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    37,    38,    39,    40,    41,    -1,    -1,    -1,    45,
      46,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,    41,
      42,    -1,    -1,    45,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,
      39,    40,    41,    42,    -1,    -1,    45,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    37,    38,    39,    40,    41,    42,    -1,    -1,    45,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    12,
      13,    14,    15,    16,    17,    18,    19,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    37,    38,    39,    40,    41,    -1,    -1,    -1,    45,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    45
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    20,    21,    22,    23,    58,    73,    74,    75,    31,
      60,     0,    74,    41,    43,    66,    42,    58,    61,    62,
       3,     4,    11,    24,    26,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    41,    44,    47,    49,    53,
      55,    56,    58,    65,    66,    67,    68,    69,    70,    71,
      72,    31,    59,    42,    48,    53,    53,    41,    41,    47,
      47,    47,    53,    53,     3,     4,     5,     6,     7,     8,
       9,    10,    12,    13,    14,    15,    16,    17,    18,    19,
      36,    37,    38,    39,    40,    41,    45,    47,    53,    57,
      59,    44,    56,    68,    44,    65,    45,    62,    53,    53,
      47,    42,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    42,    53,    54,    53,    47,    14,    44,    46,    53,
      42,    42,    42,    48,    46,    43,    53,    63,    46,    66,
      65,    53,    63,    64,    25,    44,    48,    66,    44,    63
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    52,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    54,    54,    55,    55,    55,
      55,    56,    57,    57,    58,    58,    58,    58,    59,    59,
      59,    60,    60,    60,    61,    61,    62,    62,    63,    63,
      63,    64,    64,    65,    65,    65,    65,    65,    66,    66,
      66,    66,    67,    67,    68,    68,    69,    69,    70,    70,
      71,    72,    72,    72,    72,    73,    73,    74,    75
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     3,     4,     3,
       4,     2,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     3,     1,     1,     1,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     4,
       3,     1,     4,     3,     1,     3,     2,     1,     1,     3,
       4,     1,     3,     1,     1,     1,     1,     1,     2,     3,
       3,     4,     1,     2,     1,     2,     1,     2,     5,     7,
       5,     2,     2,     2,     3,     1,     2,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        YY_LAC_DISCARD ("YYBACKUP");                              \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Given a state stack such that *YYBOTTOM is its bottom, such that
   *YYTOP is either its top or is YYTOP_EMPTY to indicate an empty
   stack, and such that *YYCAPACITY is the maximum number of elements it
   can hold without a reallocation, make sure there is enough room to
   store YYADD more elements.  If not, allocate a new stack using
   YYSTACK_ALLOC, copy the existing elements, and adjust *YYBOTTOM,
   *YYTOP, and *YYCAPACITY to reflect the new capacity and memory
   location.  If *YYBOTTOM != YYBOTTOM_NO_FREE, then free the old stack
   using YYSTACK_FREE.  Return 0 if successful or if no reallocation is
   required.  Return YYENOMEM if memory is exhausted.  */
static int
yy_lac_stack_realloc (YYPTRDIFF_T *yycapacity, YYPTRDIFF_T yyadd,
#if YYDEBUG
                      char const *yydebug_prefix,
                      char const *yydebug_suffix,
#endif
                      yy_state_t **yybottom,
                      yy_state_t *yybottom_no_free,
                      yy_state_t **yytop, yy_state_t *yytop_empty)
{
  YYPTRDIFF_T yysize_old =
    *yytop == yytop_empty ? 0 : *yytop - *yybottom + 1;
  YYPTRDIFF_T yysize_new = yysize_old + yyadd;
  if (*yycapacity < yysize_new)
    {
      YYPTRDIFF_T yyalloc = 2 * yysize_new;
      yy_state_t *yybottom_new;
      /* Use YYMAXDEPTH for maximum stack size given that the stack
         should never need to grow larger than the main state stack
         needs to grow without LAC.  */
      if (YYMAXDEPTH < yysize_new)
        {
          YYDPRINTF ((stderr, "%smax size exceeded%s", yydebug_prefix,
                      yydebug_suffix));
          return YYENOMEM;
        }
      if (YYMAXDEPTH < yyalloc)
        yyalloc = YYMAXDEPTH;
      yybottom_new =
        YY_CAST (yy_state_t *,
                 YYSTACK_ALLOC (YY_CAST (YYSIZE_T,
                                         yyalloc * YYSIZEOF (*yybottom_new))));
      if (!yybottom_new)
        {
          YYDPRINTF ((stderr, "%srealloc failed%s", yydebug_prefix,
                      yydebug_suffix));
          return YYENOMEM;
        }
      if (*yytop != yytop_empty)
        {
          YYCOPY (yybottom_new, *yybottom, yysize_old);
          *yytop = yybottom_new + (yysize_old - 1);
        }
      if (*yybottom != yybottom_no_free)
        YYSTACK_FREE (*yybottom);
      *yybottom = yybottom_new;
      *yycapacity = yyalloc;
    }
  return 0;
}

/* Establish the initial context for the current lookahead if no initial
   context is currently established.

   We define a context as a snapshot of the parser stacks.  We define
   the initial context for a lookahead as the context in which the
   parser initially examines that lookahead in order to select a
   syntactic action.  Thus, if the lookahead eventually proves
   syntactically unacceptable (possibly in a later context reached via a
   series of reductions), the initial context can be used to determine
   the exact set of tokens that would be syntactically acceptable in the
   lookahead's place.  Moreover, it is the context after which any
   further semantic actions would be erroneous because they would be
   determined by a syntactically unacceptable token.

   YY_LAC_ESTABLISH should be invoked when a reduction is about to be
   performed in an inconsistent state (which, for the purposes of LAC,
   includes consistent states that don't know they're consistent because
   their default reductions have been disabled).  Iff there is a
   lookahead token, it should also be invoked before reporting a syntax
   error.  This latter case is for the sake of the debugging output.

   For parse.lac=full, the implementation of YY_LAC_ESTABLISH is as
   follows.  If no initial context is currently established for the
   current lookahead, then check if that lookahead can eventually be
   shifted if syntactic actions continue from the current context.
   Report a syntax error if it cannot.  */
#define YY_LAC_ESTABLISH                                                \
do {                                                                    \
  if (!yy_lac_established)                                              \
    {                                                                   \
      YYDPRINTF ((stderr,                                               \
                  "LAC: initial context established for %s\n",          \
                  yysymbol_name (yytoken)));                            \
      yy_lac_established = 1;                                           \
      switch (yy_lac (yyesa, &yyes, &yyes_capacity, yyssp, yytoken))    \
        {                                                               \
        case YYENOMEM:                                                  \
          YYNOMEM;                                                      \
        case 1:                                                         \
          goto yyerrlab;                                                \
        }                                                               \
    }                                                                   \
} while (0)

/* Discard any previous initial lookahead context because of Event,
   which may be a lookahead change or an invalidation of the currently
   established initial context for the current lookahead.

   The most common example of a lookahead change is a shift.  An example
   of both cases is syntax error recovery.  That is, a syntax error
   occurs when the lookahead is syntactically erroneous for the
   currently established initial context, so error recovery manipulates
   the parser stacks to try to find a new initial context in which the
   current lookahead is syntactically acceptable.  If it fails to find
   such a context, it discards the lookahead.  */
#if YYDEBUG
# define YY_LAC_DISCARD(Event)                                           \
do {                                                                     \
  if (yy_lac_established)                                                \
    {                                                                    \
      YYDPRINTF ((stderr, "LAC: initial context discarded due to "       \
                  Event "\n"));                                          \
      yy_lac_established = 0;                                            \
    }                                                                    \
} while (0)
#else
# define YY_LAC_DISCARD(Event) yy_lac_established = 0
#endif

/* Given the stack whose top is *YYSSP, return 0 iff YYTOKEN can
   eventually (after perhaps some reductions) be shifted, return 1 if
   not, or return YYENOMEM if memory is exhausted.  As preconditions and
   postconditions: *YYES_CAPACITY is the allocated size of the array to
   which *YYES points, and either *YYES = YYESA or *YYES points to an
   array allocated with YYSTACK_ALLOC.  yy_lac may overwrite the
   contents of either array, alter *YYES and *YYES_CAPACITY, and free
   any old *YYES other than YYESA.  */
static int
yy_lac (yy_state_t *yyesa, yy_state_t **yyes,
        YYPTRDIFF_T *yyes_capacity, yy_state_t *yyssp, yysymbol_kind_t yytoken)
{
  yy_state_t *yyes_prev = yyssp;
  yy_state_t *yyesp = yyes_prev;
  /* Reduce until we encounter a shift and thereby accept the token.  */
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yysymbol_name (yytoken)));
  if (yytoken == YYSYMBOL_YYUNDEF)
    {
      YYDPRINTF ((stderr, " Always Err\n"));
      return 1;
    }
  while (1)
    {
      int yyrule = yypact[+*yyesp];
      if (yypact_value_is_default (yyrule)
          || (yyrule += yytoken) < 0 || YYLAST < yyrule
          || yycheck[yyrule] != yytoken)
        {
          /* Use the default action.  */
          yyrule = yydefact[+*yyesp];
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
        }
      else
        {
          /* Use the action from yytable.  */
          yyrule = yytable[yyrule];
          if (yytable_value_is_error (yyrule))
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
          if (0 < yyrule)
            {
              YYDPRINTF ((stderr, " S%d\n", yyrule));
              return 0;
            }
          yyrule = -yyrule;
        }
      /* By now we know we have to simulate a reduce.  */
      YYDPRINTF ((stderr, " R%d", yyrule - 1));
      {
        /* Pop the corresponding number of values from the stack.  */
        YYPTRDIFF_T yylen = yyr2[yyrule];
        /* First pop from the LAC stack as many tokens as possible.  */
        if (yyesp != yyes_prev)
          {
            YYPTRDIFF_T yysize = yyesp - *yyes + 1;
            if (yylen < yysize)
              {
                yyesp -= yylen;
                yylen = 0;
              }
            else
              {
                yyesp = yyes_prev;
                yylen -= yysize;
              }
          }
        /* Only afterwards look at the main stack.  */
        if (yylen)
          yyesp = yyes_prev -= yylen;
      }
      /* Push the resulting state of the reduction.  */
      {
        yy_state_fast_t yystate;
        {
          const int yylhs = yyr1[yyrule] - YYNTOKENS;
          const int yyi = yypgoto[yylhs] + *yyesp;
          yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyesp
                     ? yytable[yyi]
                     : yydefgoto[yylhs]);
        }
        if (yyesp == yyes_prev)
          {
            yyesp = *yyes;
            YY_IGNORE_USELESS_CAST_BEGIN
            *yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
          }
        else
          {
            if (yy_lac_stack_realloc (yyes_capacity, 1,
#if YYDEBUG
                                      " (", ")",
#endif
                                      yyes, yyesa, &yyesp, yyes_prev))
              {
                YYDPRINTF ((stderr, "\n"));
                return YYENOMEM;
              }
            YY_IGNORE_USELESS_CAST_BEGIN
            *++yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}

/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yy_state_t *yyesa;
  yy_state_t **yyes;
  YYPTRDIFF_T *yyes_capacity;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;

  int yyx;
  for (yyx = 0; yyx < YYNTOKENS; ++yyx)
    {
      yysymbol_kind_t yysym = YY_CAST (yysymbol_kind_t, yyx);
      if (yysym != YYSYMBOL_YYerror && yysym != YYSYMBOL_YYUNDEF)
        switch (yy_lac (yyctx->yyesa, yyctx->yyes, yyctx->yyes_capacity, yyctx->yyssp, yysym))
          {
          case YYENOMEM:
            return YYENOMEM;
          case 1:
            continue;
          default:
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = yysym;
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
       In the first two cases, it might appear that the current syntax
       error should have been detected in the previous state when yy_lac
       was invoked.  However, at that time, there might have been a
       different syntax error that discarded a different initial context
       during error recovery, leaving behind the current lookahead.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      YYDPRINTF ((stderr, "Constructing syntax error message\n"));
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else if (yyn == 0)
        YYDPRINTF ((stderr, "No expected tokens.\n"));
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.  In order to see if a particular token T is a
   valid looakhead, invoke yy_lac (YYESA, YYES, YYES_CAPACITY, YYSSP, T).

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store or if
   yy_lac returned YYENOMEM.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    yy_state_t yyesa[20];
    yy_state_t *yyes = yyesa;
    YYPTRDIFF_T yyes_capacity = 20 < YYMAXDEPTH ? 20 : YYMAXDEPTH;

  /* Whether LAC context is established.  A Boolean.  */
  int yy_lac_established = 0;
  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    {
      YY_LAC_ESTABLISH;
      goto yydefault;
    }
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      YY_LAC_ESTABLISH;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  YY_LAC_DISCARD ("shift");
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  {
    int yychar_backup = yychar;
    switch (yyn)
      {
  case 2: /* expression: ID  */
#line 75 "parser.y"
             { yyval = checkVar(idCopy); }
#line 1924 "parser.c"
    break;

  case 3: /* expression: FLOAT_VAL  */
#line 76 "parser.y"
                        { yyval = yyvsp[0]; }
#line 1930 "parser.c"
    break;

  case 4: /* expression: INT_VAL  */
#line 77 "parser.y"
                        { yyval = yyvsp[0]; }
#line 1936 "parser.c"
    break;

  case 5: /* expression: STR_VAL  */
#line 78 "parser.y"
                        { yyval = yyvsp[0]; }
#line 1942 "parser.c"
    break;

  case 6: /* expression: CHAR_VAL  */
#line 79 "parser.y"
                        { yyval = yyvsp[0]; }
#line 1948 "parser.c"
    break;

  case 7: /* expression: LPAR expression RPAR  */
#line 80 "parser.y"
                               { yyval = yyvsp[-1]; }
#line 1954 "parser.c"
    break;

  case 8: /* expression: expression LBRAC expression RBRAC  */
#line 81 "parser.y"
                                            { yyval = toPrimitive(yyvsp[-3]);}
#line 1960 "parser.c"
    break;

  case 9: /* expression: expression LPAR RPAR  */
#line 82 "parser.y"
                               { yyval = yyvsp[-2]; }
#line 1966 "parser.c"
    break;

  case 10: /* expression: expression LPAR argument_expression_list RPAR  */
#line 83 "parser.y"
                                                        { yyval = yyvsp[-3]; }
#line 1972 "parser.c"
    break;

  case 11: /* expression: expression INC  */
#line 84 "parser.y"
                         { yyval = check_number(yyvsp[-1]); }
#line 1978 "parser.c"
    break;

  case 12: /* expression: expression DEC  */
#line 85 "parser.y"
                         { yyval = check_number(yyvsp[-1]); }
#line 1984 "parser.c"
    break;

  case 13: /* expression: INC expression  */
#line 86 "parser.y"
                         { yyval = check_number(yyvsp[0]); }
#line 1990 "parser.c"
    break;

  case 14: /* expression: DEC expression  */
#line 87 "parser.y"
                         { yyval = check_number(yyvsp[0]); }
#line 1996 "parser.c"
    break;

  case 15: /* expression: unary_operator expression  */
#line 88 "parser.y"
                                                 { yyval = check_number(yyvsp[0]); }
#line 2002 "parser.c"
    break;

  case 16: /* expression: expression TIMES expression  */
#line 89 "parser.y"
                                                { yyval = unify_bin_op(yyvsp[-2], yyvsp[0], TIMES_NODE, "*", unify_arith); }
#line 2008 "parser.c"
    break;

  case 17: /* expression: expression OVER expression  */
#line 90 "parser.y"
                                                { yyval = unify_bin_op(yyvsp[-2], yyvsp[0], OVER_NODE, "/", unify_arith); }
#line 2014 "parser.c"
    break;

  case 18: /* expression: expression PERCENT expression  */
#line 91 "parser.y"
                                                { yyval = unify_bin_op(yyvsp[-2], yyvsp[0], PERCENT_NODE, "%%", unify_arith); }
#line 2020 "parser.c"
    break;

  case 19: /* expression: expression PLUS expression  */
#line 92 "parser.y"
                                                { yyval = unify_bin_op(yyvsp[-2], yyvsp[0], PLUS_NODE, "+", unify_arith); }
#line 2026 "parser.c"
    break;

  case 20: /* expression: expression MINUS expression  */
#line 93 "parser.y"
                                                { yyval = unify_bin_op(yyvsp[-2], yyvsp[0], MINUS_NODE, "-", unify_arith); }
#line 2032 "parser.c"
    break;

  case 21: /* expression: expression LT expression  */
#line 94 "parser.y"
                                                        { yyval = unify_bin_op(yyvsp[-2], yyvsp[0], LT_NODE, "<", unify_comp); }
#line 2038 "parser.c"
    break;

  case 22: /* expression: expression GT expression  */
#line 95 "parser.y"
                                                        { yyval = unify_bin_op(yyvsp[-2], yyvsp[0], GT_NODE, ">", unify_comp); }
#line 2044 "parser.c"
    break;

  case 23: /* expression: expression LT_EQ expression  */
#line 96 "parser.y"
                                                { yyval = unify_bin_op(yyvsp[-2], yyvsp[0], LT_EQ_NODE, "<=", unify_comp); }
#line 2050 "parser.c"
    break;

  case 24: /* expression: expression GT_EQ expression  */
#line 97 "parser.y"
                                                { yyval = unify_bin_op(yyvsp[-2], yyvsp[0], GT_EQ_NODE, ">=", unify_comp); }
#line 2056 "parser.c"
    break;

  case 25: /* expression: expression EQ expression  */
#line 98 "parser.y"
                                                        { yyval = unify_bin_op(yyvsp[-2], yyvsp[0], EQ_NODE, "==", unify_comp); }
#line 2062 "parser.c"
    break;

  case 26: /* expression: expression N_EQ expression  */
#line 99 "parser.y"
                                                { yyval = unify_bin_op(yyvsp[-2], yyvsp[0], N_EQ_NODE, "!=", unify_comp); }
#line 2068 "parser.c"
    break;

  case 27: /* expression: expression L_AND expression  */
#line 100 "parser.y"
                                                { yyval = check_int(yyvsp[-2], yyvsp[0], L_AND_NODE); }
#line 2074 "parser.c"
    break;

  case 28: /* expression: expression L_OR expression  */
#line 101 "parser.y"
                                                { yyval = check_int(yyvsp[-2], yyvsp[0], L_OR_NODE); }
#line 2080 "parser.c"
    break;

  case 29: /* expression: expression ASGN expression  */
#line 102 "parser.y"
                                            { yyval = check_assign(yyvsp[-2], yyvsp[0]); }
#line 2086 "parser.c"
    break;

  case 30: /* expression: expression T_ASGN expression  */
#line 103 "parser.y"
                                                { yyval = unify_bin_op(yyvsp[-2], yyvsp[0], T_ASGN_NODE, "*", unify_arith); }
#line 2092 "parser.c"
    break;

  case 31: /* expression: expression O_ASGN expression  */
#line 104 "parser.y"
                                                { yyval = unify_bin_op(yyvsp[-2], yyvsp[0], O_ASGN_NODE, "/", unify_arith); }
#line 2098 "parser.c"
    break;

  case 32: /* expression: expression MOD_ASGN expression  */
#line 105 "parser.y"
                                                { yyval = unify_bin_op(yyvsp[-2], yyvsp[0], MOD_ASGN_NODE, "%%", unify_arith); }
#line 2104 "parser.c"
    break;

  case 33: /* expression: expression PL_ASGN expression  */
#line 106 "parser.y"
                                                { yyval = unify_bin_op(yyvsp[-2], yyvsp[0], PL_ASGN_NODE, "+", unify_arith); }
#line 2110 "parser.c"
    break;

  case 34: /* expression: expression M_ASGN expression  */
#line 107 "parser.y"
                                                { yyval = unify_bin_op(yyvsp[-2], yyvsp[0], M_ASGN_NODE, "-", unify_arith); }
#line 2116 "parser.c"
    break;

  case 41: /* declaration: type_specifier init_declarator SEMI  */
#line 124 "parser.y"
                                              { yyval = yyvsp[-1]; }
#line 2122 "parser.c"
    break;

  case 42: /* init_declarator: declarator  */
#line 128 "parser.y"
                     { yyval = yyvsp[0]; }
#line 2128 "parser.c"
    break;

  case 43: /* init_declarator: declarator ASGN initializer  */
#line 129 "parser.y"
                                      { yyval = check_declarator_assign(yyvsp[-2], yyvsp[0]); }
#line 2134 "parser.c"
    break;

  case 44: /* type_specifier: VOID  */
#line 133 "parser.y"
                { type = VOID_TYPE;  }
#line 2140 "parser.c"
    break;

  case 45: /* type_specifier: CHAR  */
#line 134 "parser.y"
                { type = CHAR_TYPE;  }
#line 2146 "parser.c"
    break;

  case 46: /* type_specifier: INT  */
#line 135 "parser.y"
                { type = INT_TYPE;   }
#line 2152 "parser.c"
    break;

  case 47: /* type_specifier: FLOAT  */
#line 136 "parser.y"
                { type = FLOAT_TYPE; }
#line 2158 "parser.c"
    break;

  case 48: /* declarator: ID  */
#line 140 "parser.y"
             { yyval = newVar(yytext); }
#line 2164 "parser.c"
    break;

  case 49: /* declarator: declarator LBRAC expression RBRAC  */
#line 141 "parser.y"
                                            { newArrayVar(); yyval = toArray(yyvsp[-3]);}
#line 2170 "parser.c"
    break;

  case 50: /* declarator: declarator LBRAC RBRAC  */
#line 142 "parser.y"
                                 { newArrayVar(); yyval = toArray(yyvsp[-2]);}
#line 2176 "parser.c"
    break;

  case 51: /* function_declarator: ID  */
#line 146 "parser.y"
             { newFunc(yytext, yylineno); yyval = new_node(PARAM_LIST_NODE, 0, NO_TYPE); }
#line 2182 "parser.c"
    break;

  case 52: /* function_declarator: function_declarator LPAR parameter_list RPAR  */
#line 147 "parser.y"
                                                       { yyval = yyvsp[-1]; }
#line 2188 "parser.c"
    break;

  case 53: /* function_declarator: function_declarator LPAR RPAR  */
#line 148 "parser.y"
                                        { yyval = new_node(PARAM_LIST_NODE, 0, NO_TYPE); }
#line 2194 "parser.c"
    break;

  case 54: /* parameter_list: parameter_declaration  */
#line 152 "parser.y"
                                {argsCount++; yyval = new_subtree(PARAM_LIST_NODE, NO_TYPE, 1, yyvsp[0]); }
#line 2200 "parser.c"
    break;

  case 55: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 153 "parser.y"
                                                     {argsCount++; add_child(yyvsp[-2], yyvsp[0]); yyval = yyvsp[-2]; }
#line 2206 "parser.c"
    break;

  case 56: /* parameter_declaration: type_specifier declarator  */
#line 157 "parser.y"
                                    { yyval = yyvsp[0]; }
#line 2212 "parser.c"
    break;

  case 58: /* initializer: expression  */
#line 162 "parser.y"
                     { yyval = yyvsp[0]; }
#line 2218 "parser.c"
    break;

  case 59: /* initializer: LCURLY initializer_list RCURLY  */
#line 163 "parser.y"
                                          { yyval = toArray(yyvsp[-1]); }
#line 2224 "parser.c"
    break;

  case 60: /* initializer: LCURLY initializer_list COMMA RCURLY  */
#line 164 "parser.y"
                                                { yyval = toArray(yyvsp[-2]); }
#line 2230 "parser.c"
    break;

  case 61: /* initializer_list: initializer  */
#line 168 "parser.y"
                      { yyval = yyvsp[0]; }
#line 2236 "parser.c"
    break;

  case 62: /* initializer_list: initializer_list COMMA initializer  */
#line 169 "parser.y"
                                             { yyval = yyvsp[-2]; }
#line 2242 "parser.c"
    break;

  case 63: /* statement: compound_statement  */
#line 173 "parser.y"
                                { yyval = yyvsp[0]; }
#line 2248 "parser.c"
    break;

  case 64: /* statement: expression_statement  */
#line 174 "parser.y"
                                { yyval = yyvsp[0]; }
#line 2254 "parser.c"
    break;

  case 65: /* statement: selection_statement  */
#line 175 "parser.y"
                                { yyval = yyvsp[0]; }
#line 2260 "parser.c"
    break;

  case 66: /* statement: iteration_statement  */
#line 176 "parser.y"
                                { yyval = yyvsp[0]; }
#line 2266 "parser.c"
    break;

  case 67: /* statement: jump_statement  */
#line 177 "parser.y"
                                        { yyval = yyvsp[0]; }
#line 2272 "parser.c"
    break;

  case 69: /* compound_statement: LCURLY statement_list RCURLY  */
#line 182 "parser.y"
                                       { yyval = new_subtree(COMPOUND_NODE, NO_TYPE, 1, yyvsp[-1]); }
#line 2278 "parser.c"
    break;

  case 70: /* compound_statement: LCURLY declaration_list RCURLY  */
#line 183 "parser.y"
                                         { yyval = new_subtree(COMPOUND_NODE, NO_TYPE, 1, yyvsp[-1]); }
#line 2284 "parser.c"
    break;

  case 71: /* compound_statement: LCURLY declaration_list statement_list RCURLY  */
#line 184 "parser.y"
                                                        { yyval = new_subtree(COMPOUND_NODE, NO_TYPE, 2, yyvsp[-2], yyvsp[-1]); }
#line 2290 "parser.c"
    break;

  case 72: /* declaration_list: declaration  */
#line 188 "parser.y"
                                                        { yyval = new_subtree(VAR_LIST_NODE, NO_TYPE, 1, yyvsp[0]); }
#line 2296 "parser.c"
    break;

  case 73: /* declaration_list: declaration_list declaration  */
#line 189 "parser.y"
                                        { add_child(yyvsp[-1], yyvsp[0]); yyval = yyvsp[-1]; }
#line 2302 "parser.c"
    break;

  case 74: /* statement_list: statement  */
#line 193 "parser.y"
                                        { yyval = new_subtree(STMT_LIST_NODE, NO_TYPE, 1, yyvsp[0]); }
#line 2308 "parser.c"
    break;

  case 75: /* statement_list: statement_list statement  */
#line 194 "parser.y"
                                        { add_child(yyvsp[-1], yyvsp[0]); yyval = yyvsp[-1]; }
#line 2314 "parser.c"
    break;

  case 77: /* expression_statement: expression SEMI  */
#line 199 "parser.y"
                          { yyval = yyvsp[-1]; }
#line 2320 "parser.c"
    break;

  case 78: /* selection_statement: IF LPAR expression RPAR compound_statement  */
#line 203 "parser.y"
                                                     { yyval = check_if_then(yyvsp[-2], yyvsp[0]); }
#line 2326 "parser.c"
    break;

  case 79: /* selection_statement: IF LPAR expression RPAR compound_statement ELSE compound_statement  */
#line 204 "parser.y"
                                                                             { yyval = check_if_then_else(yyvsp[-4], yyvsp[-2], yyvsp[0]); }
#line 2332 "parser.c"
    break;

  case 80: /* iteration_statement: WHILE LPAR expression RPAR statement  */
#line 208 "parser.y"
                                               { yyval = check_while(yyvsp[-2], yyvsp[0]); }
#line 2338 "parser.c"
    break;

  case 81: /* jump_statement: CONTINUE SEMI  */
#line 212 "parser.y"
                                                { yyval = new_subtree(CONTINUE_NODE, NO_TYPE, 0); }
#line 2344 "parser.c"
    break;

  case 82: /* jump_statement: BREAK SEMI  */
#line 213 "parser.y"
                                                { yyval = new_subtree(BREAK_NODE, NO_TYPE, 0); }
#line 2350 "parser.c"
    break;

  case 83: /* jump_statement: RETURN SEMI  */
#line 214 "parser.y"
                                                { yyval = new_subtree(RETURN_NODE, NO_TYPE, 0); }
#line 2356 "parser.c"
    break;

  case 84: /* jump_statement: RETURN expression SEMI  */
#line 215 "parser.y"
                                        { yyval = new_subtree(RETURN_NODE, NO_TYPE, 1, yyvsp[-1]);}
#line 2362 "parser.c"
    break;

  case 85: /* translation_unit: external_declaration  */
#line 219 "parser.y"
                               { root = new_subtree(PROGRAM_NODE, NO_TYPE, 1, yyvsp[0]);}
#line 2368 "parser.c"
    break;

  case 86: /* translation_unit: translation_unit external_declaration  */
#line 220 "parser.y"
                                                { add_child(root, yyvsp[0]);}
#line 2374 "parser.c"
    break;

  case 87: /* external_declaration: function_definition  */
#line 224 "parser.y"
                              { scopeCount++;  yyval = yyvsp[0];}
#line 2380 "parser.c"
    break;

  case 88: /* function_definition: type_specifier function_declarator compound_statement  */
#line 228 "parser.y"
                                                                { yyval = new_subtree(FUNCTION_NODE, get_type_func(funcTable,scopeCount), 2, yyvsp[-1], yyvsp[0]); set_data(yyval, scopeCount); set_args_count_func(funcTable, scopeCount, argsCount); argsCount = 0;}
#line 2386 "parser.c"
    break;


#line 2390 "parser.c"

        default: break;
      }
    if (yychar_backup != yychar)
      YY_LAC_DISCARD ("yychar change");
  }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yyesa, &yyes, &yyes_capacity, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        if (yychar != YYEMPTY)
          YY_LAC_ESTABLISH;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  /* If the stack popping above didn't lose the initial context for the
     current lookahead token, the shift below will for sure.  */
  YY_LAC_DISCARD ("error recovery");

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yyes != yyesa)
    YYSTACK_FREE (yyes);
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 231 "parser.y"


// Primitive error handling.
void yyerror (char const *s) {
    printf("SYNTAX ERROR (%d): %s\n", yylineno, s);
    exit(EXIT_FAILURE);
}

int main() {
	strTable = create_str_table();
	funcTable = create_func_table();

    yyparse();
    printf("PARSE SUCCESSFUL!\n");
	print_str_table(strTable);
	print_func_table(funcTable);

	print_dot(root);

	free_str_table(strTable);
	free_func_table(funcTable);
    free_tree(root);
    yylex_destroy();    // To avoid memory leaks within flex...
    return 0;
}


AST* newVar(char* str){
	VarTable* vt = get_var_table_func(funcTable,scopeCount);
    int index = lookup_var(vt, str);

	if(index != -1){
		printf("SEMANTIC ERROR (%d): variable ’%s’ already declared at line %d.\n", yylineno, str, get_line(vt, index));
		exit(EXIT_FAILURE);
	}

	add_func_var(funcTable, str, yylineno, type, scopeCount);
	return new_node(VAR_DECL_NODE, lookup_var(vt, str), type);
}

void newArrayVar(){
	set_func_last_var_type(funcTable, scopeCount);
}


AST* checkVar(char* str){
	VarTable* vt = get_var_table_func(funcTable,scopeCount);
    int indexVar = lookup_var(vt, str);
	int indexFunc = lookup_func(funcTable, str);

	if ( indexVar == -1 && indexFunc == -1) {
        printf("SEMANTIC ERROR (%d): variable ’%s’ was never declared.\n", yylineno, str);
		exit(EXIT_FAILURE);
    }

	if(indexFunc != -1){
		return new_node(FUNC_USE_NODE, indexFunc, get_type_func(funcTable, indexFunc));
	} else {
		return new_node(VAR_USE_NODE, indexVar, get_type(vt,indexVar));
	}
}

void newFunc(char* str, int line){
    int index = lookup_func(funcTable, str);
    if ( index == -1 ) {
        add_func(funcTable, str, line, argsCount, type);
    } else {
        printf("SEMANTIC ERROR (%d): function ’%s’ already declared at line %d.\n", line, str, get_line_func(funcTable, index));
		exit(EXIT_FAILURE);
    }
}

// ----------------------------------------------------------------------------

// Type checking and inference.

void type_error(const char* op, Type t1, Type t2) {
    printf("SEMANTIC ERROR (%d): incompatible types for operator '%s', LHS is '%s' and RHS is '%s'.\n",
           yylineno, op, get_text(t1), get_text(t2));
    exit(EXIT_FAILURE);
}

void assign_array_error(Type t) {
	printf("SEMANTIC ERROR (%d): cannot assign an '%s' type.\n",
           yylineno, get_text(t));
    exit(EXIT_FAILURE);
}

AST* unify_bin_op(AST* nodeL, AST* nodeR, NodeKind kind, const char* op, Type (*unify)(Type,Type)) {
	Type l = get_node_type(nodeL);
	Type r = get_node_type(nodeR);
    Type unif = unify(l, r);
    if (unif == NO_TYPE) {
        type_error(op, l, r);
    }
    return new_subtree(kind, unif, 2, nodeL, nodeR);
}

AST* check_number(AST* node){
	Type t = get_node_type(node);
	if(t != INT_TYPE && t != FLOAT_TYPE){
		printf("SEMANTIC ERROR (%d): not a number.\n", yylineno);
    	exit(EXIT_FAILURE);
	}

	return node;
}

AST* check_assign(AST* nodeL, AST* nodeR) {
	Type l = get_node_type(nodeL);
	Type r = get_node_type(nodeR);

	if (l == INT_ARRAY_TYPE  || r == INT_ARRAY_TYPE)  assign_array_error(l);
	if (l == FLOAT_ARRAY_TYPE  || r == FLOAT_ARRAY_TYPE)  assign_array_error(l);
	if (l == CHAR_ARRAY_TYPE  || r == CHAR_ARRAY_TYPE)  assign_array_error(l);

	if (l == VOID_TYPE  || r == VOID_TYPE)  type_error("=", l, r);
	if (l == FLOAT_TYPE && !(r == INT_TYPE || r == FLOAT_TYPE)) type_error("=", l, r);
    if (l == CHAR_TYPE  && r != CHAR_TYPE)  type_error("=", l, r);
    if (l == INT_TYPE  && r != INT_TYPE)  type_error("=", l, r);
    
	return new_subtree(ASSIGN_NODE, NO_TYPE, 2, nodeL, nodeR);
}

AST* check_declarator_assign(AST* nodeL, AST* nodeR) {
	Type l = get_node_type(nodeL);
	Type r = get_node_type(nodeR);

	if (l == INT_ARRAY_TYPE  && r != INT_ARRAY_TYPE)  assign_array_error(l);
	if (l == FLOAT_ARRAY_TYPE  && !(r == INT_ARRAY_TYPE || r == FLOAT_ARRAY_TYPE))  assign_array_error(l);
	if (l == CHAR_ARRAY_TYPE  && r != CHAR_ARRAY_TYPE)  assign_array_error(l);

	if (l == VOID_TYPE  || r == VOID_TYPE)  type_error("=", l, r);
	if (l == FLOAT_TYPE && !(r == INT_TYPE || r == FLOAT_TYPE)) type_error("=", l, r);
    if (l == CHAR_TYPE  && r != CHAR_TYPE)  type_error("=", l, r);
    if (l == INT_TYPE  && r != INT_TYPE)  type_error("=", l, r);
    
	return new_subtree(ASSIGN_NODE, NO_TYPE, 2, nodeL, nodeR);
}

AST* check_int(AST* nodeL, AST* nodeR, NodeKind kind) {
	Type l = get_node_type(nodeL);
	Type r = get_node_type(nodeR);

	if (l != INT_TYPE  || r != INT_TYPE) type_error("not int", l, r);

	return new_subtree(kind, INT_TYPE, 2, nodeL, nodeR);
}


AST* toPrimitive(AST* node) {
	Type t = get_node_type(node);

	if (t == INT_ARRAY_TYPE) t = INT_TYPE;  
	else if (t == FLOAT_ARRAY_TYPE) t = FLOAT_TYPE;
	else if (t == CHAR_ARRAY_TYPE) t = CHAR_TYPE; 
	else {	
		printf("SEMANTIC ERROR (%d): variable has no primitive type.\n", yylineno);
		exit(EXIT_FAILURE);
	}

	set_node_type(node, t);
	return node;
}

AST* toArray(AST* node) {
	Type t = get_node_type(node);

	if (t == INT_TYPE) t = INT_ARRAY_TYPE;  
	if (t == FLOAT_TYPE) t = FLOAT_ARRAY_TYPE;
	if (t == CHAR_TYPE) t = CHAR_ARRAY_TYPE; 

	set_node_type(node, t);
	return node;
}

AST* check_if_then(AST *e, AST *b) {
    check_bool_expr("if", get_node_type(e));
    return new_subtree(IF_NODE, NO_TYPE, 2, e, b);
}

AST* check_if_then_else(AST *e, AST *b1, AST *b2) {
    check_bool_expr("if", get_node_type(e));
    return new_subtree(IF_NODE, NO_TYPE, 3, e, b1, b2);
}

AST* check_while(AST *e, AST *b) {
    check_bool_expr("while", get_node_type(e));
    return new_subtree(WHILE_NODE, NO_TYPE, 2, b, e);
}

void check_bool_expr(const char* cmd, Type t) {
    if (t != INT_TYPE) {
        printf("SEMANTIC ERROR (%d): conditional expression in '%s' is '%s' instead of '%s'.\n",
           yylineno, cmd, get_text(t), get_text(INT_TYPE));
    exit(EXIT_FAILURE);
    }
}

