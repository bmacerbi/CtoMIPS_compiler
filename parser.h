/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INC = 258,
    DEC = 259,
    LT_EQ = 260,
    GT_EQ = 261,
    LT = 262,
    GT = 263,
    EQ = 264,
    N_EQ = 265,
    L_NOT = 266,
    L_AND = 267,
    L_OR = 268,
    ASGN = 269,
    T_ASGN = 270,
    O_ASGN = 271,
    MOD_ASGN = 272,
    PL_ASGN = 273,
    M_ASGN = 274,
    CHAR = 275,
    SHORT = 276,
    INT = 277,
    LONG = 278,
    SIGNED = 279,
    UNSIGNED = 280,
    FLOAT = 281,
    DOUBLE = 282,
    VOID = 283,
    CASE = 284,
    DEFAULT = 285,
    IF = 286,
    ELSE = 287,
    SWITCH = 288,
    WHILE = 289,
    DO = 290,
    FOR = 291,
    GOTO = 292,
    CONTINUE = 293,
    BREAK = 294,
    RETURN = 295,
    ID = 296,
    FLOAT_VAL = 297,
    INT_VAL = 298,
    STR_VAL = 299,
    CHAR_VAL = 300,
    SIZEOF = 301,
    PLUS = 302,
    MINUS = 303,
    TIMES = 304,
    OVER = 305,
    PERCENT = 306,
    LPAR = 307,
    RPAR = 308,
    LCURLY = 309,
    RCURLY = 310,
    LBRAC = 311,
    RBRAC = 312,
    SEMI = 313,
    COMMA = 314,
    AMPER = 315,
    COLON = 316,
    UMINUS = 317
  };
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
