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
    INC = 258,                     /* INC  */
    DEC = 259,                     /* DEC  */
    LT_EQ = 260,                   /* LT_EQ  */
    GT_EQ = 261,                   /* GT_EQ  */
    LT = 262,                      /* LT  */
    GT = 263,                      /* GT  */
    EQ = 264,                      /* EQ  */
    N_EQ = 265,                    /* N_EQ  */
    L_NOT = 266,                   /* L_NOT  */
    L_AND = 267,                   /* L_AND  */
    L_OR = 268,                    /* L_OR  */
    ASGN = 269,                    /* ASGN  */
    T_ASGN = 270,                  /* T_ASGN  */
    O_ASGN = 271,                  /* O_ASGN  */
    MOD_ASGN = 272,                /* MOD_ASGN  */
    PL_ASGN = 273,                 /* PL_ASGN  */
    M_ASGN = 274,                  /* M_ASGN  */
    CHAR = 275,                    /* CHAR  */
    SHORT = 276,                   /* SHORT  */
    INT = 277,                     /* INT  */
    LONG = 278,                    /* LONG  */
    SIGNED = 279,                  /* SIGNED  */
    UNSIGNED = 280,                /* UNSIGNED  */
    FLOAT = 281,                   /* FLOAT  */
    DOUBLE = 282,                  /* DOUBLE  */
    VOID = 283,                    /* VOID  */
    CASE = 284,                    /* CASE  */
    DEFAULT = 285,                 /* DEFAULT  */
    IF = 286,                      /* IF  */
    ELSE = 287,                    /* ELSE  */
    SWITCH = 288,                  /* SWITCH  */
    WHILE = 289,                   /* WHILE  */
    DO = 290,                      /* DO  */
    FOR = 291,                     /* FOR  */
    GOTO = 292,                    /* GOTO  */
    CONTINUE = 293,                /* CONTINUE  */
    BREAK = 294,                   /* BREAK  */
    RETURN = 295,                  /* RETURN  */
    ID = 296,                      /* ID  */
    FLOAT_VAL = 297,               /* FLOAT_VAL  */
    INT_VAL = 298,                 /* INT_VAL  */
    STR_VAL = 299,                 /* STR_VAL  */
    CHAR_VAL = 300,                /* CHAR_VAL  */
    SIZEOF = 301,                  /* SIZEOF  */
    PLUS = 302,                    /* PLUS  */
    MINUS = 303,                   /* MINUS  */
    TIMES = 304,                   /* TIMES  */
    OVER = 305,                    /* OVER  */
    PERCENT = 306,                 /* PERCENT  */
    LPAR = 307,                    /* LPAR  */
    RPAR = 308,                    /* RPAR  */
    LCURLY = 309,                  /* LCURLY  */
    RCURLY = 310,                  /* RCURLY  */
    LBRAC = 311,                   /* LBRAC  */
    RBRAC = 312,                   /* RBRAC  */
    SEMI = 313,                    /* SEMI  */
    COMMA = 314,                   /* COMMA  */
    AMPER = 315,                   /* AMPER  */
    COLON = 316,                   /* COLON  */
    UMINUS = 317                   /* UMINUS  */
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
