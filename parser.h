/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PTR_OP = 258,                  /* PTR_OP  */
    INC = 259,                     /* INC  */
    DEC = 260,                     /* DEC  */
    LT_EQ = 261,                   /* LT_EQ  */
    GT_EQ = 262,                   /* GT_EQ  */
    LT = 263,                      /* LT  */
    GT = 264,                      /* GT  */
    EQ = 265,                      /* EQ  */
    N_EQ = 266,                    /* N_EQ  */
    L_NOT = 267,                   /* L_NOT  */
    L_AND = 268,                   /* L_AND  */
    L_OR = 269,                    /* L_OR  */
    ASGN = 270,                    /* ASGN  */
    T_ASGN = 271,                  /* T_ASGN  */
    O_ASGN = 272,                  /* O_ASGN  */
    MOD_ASGN = 273,                /* MOD_ASGN  */
    PL_ASGN = 274,                 /* PL_ASGN  */
    M_ASGN = 275,                  /* M_ASGN  */
    TYPEDEF = 276,                 /* TYPEDEF  */
    EXTERN = 277,                  /* EXTERN  */
    STATIC = 278,                  /* STATIC  */
    AUTO = 279,                    /* AUTO  */
    REGISTER = 280,                /* REGISTER  */
    INLINE = 281,                  /* INLINE  */
    RESTRICT = 282,                /* RESTRICT  */
    CHAR = 283,                    /* CHAR  */
    SHORT = 284,                   /* SHORT  */
    INT = 285,                     /* INT  */
    LONG = 286,                    /* LONG  */
    SIGNED = 287,                  /* SIGNED  */
    UNSIGNED = 288,                /* UNSIGNED  */
    FLOAT = 289,                   /* FLOAT  */
    DOUBLE = 290,                  /* DOUBLE  */
    CONST = 291,                   /* CONST  */
    VOLATILE = 292,                /* VOLATILE  */
    VOID = 293,                    /* VOID  */
    BOOL = 294,                    /* BOOL  */
    COMPLEX = 295,                 /* COMPLEX  */
    IMAGINARY = 296,               /* IMAGINARY  */
    STRUCT = 297,                  /* STRUCT  */
    UNION = 298,                   /* UNION  */
    ENUM = 299,                    /* ENUM  */
    CASE = 300,                    /* CASE  */
    DEFAULT = 301,                 /* DEFAULT  */
    IF = 302,                      /* IF  */
    ELSE = 303,                    /* ELSE  */
    SWITCH = 304,                  /* SWITCH  */
    WHILE = 305,                   /* WHILE  */
    DO = 306,                      /* DO  */
    FOR = 307,                     /* FOR  */
    GOTO = 308,                    /* GOTO  */
    CONTINUE = 309,                /* CONTINUE  */
    BREAK = 310,                   /* BREAK  */
    RETURN = 311,                  /* RETURN  */
    ID = 312,                      /* ID  */
    FLOAT_VAL = 313,               /* FLOAT_VAL  */
    INT_VAL = 314,                 /* INT_VAL  */
    STR_VAL = 315,                 /* STR_VAL  */
    CHAR_VAL = 316,                /* CHAR_VAL  */
    SIZEOF = 317,                  /* SIZEOF  */
    PLUS = 318,                    /* PLUS  */
    MINUS = 319,                   /* MINUS  */
    TIMES = 320,                   /* TIMES  */
    OVER = 321,                    /* OVER  */
    PERCENT = 322,                 /* PERCENT  */
    LPAR = 323,                    /* LPAR  */
    RPAR = 324,                    /* RPAR  */
    LCURLY = 325,                  /* LCURLY  */
    RCURLY = 326,                  /* RCURLY  */
    LBRAC = 327,                   /* LBRAC  */
    RBRAC = 328,                   /* RBRAC  */
    SEMI = 329,                    /* SEMI  */
    COMMA = 330,                   /* COMMA  */
    AMPER = 331                    /* AMPER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_H_INCLUDED  */
