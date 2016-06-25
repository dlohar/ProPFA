/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "grammar.y" /* yacc.c:339  */


#include "parser.h"

bool unary_minus_stack[MAX_UNARY_ARITH_OPERATOR_NESTING] = {false};
size_t unary_minus_stack_top = 0,
	   stmt_number = 0,
	   param_decl_stmt_number,
	   N_params = 0,
	   calling_function_stack[MAX_FUNCTION_CALL_NESTING * 3] = {0},
	   calling_function_stack_top = 0,
	   calling_function_N_args_stack[MAX_FUNCTION_CALL_NESTING + 1] = {0},
	   calling_function_N_args_stack_top = 0;
int current_function_table_index = -1;	// -1 for global scope

void semantic_error(const char *token, ErrorT type) {
  char error[200];
  switch (type) {
    case MULT_DECL_VAR:
      sprintf(error, "multiple declaration of variable ‘%s’", token);
      break;
    case MULT_DECL_PARAM:
      sprintf(error, "multiple declaration of parameter ‘%s’", token);
      break;
    case UN_DECL:
      sprintf(error, "undeclared variable ‘%s’", token);
      break;
    case NO_INIT:
      sprintf(error, "uninitialized variable ‘%s’", token);
      break;
    case UN_DEF:
      sprintf(error, "undefined function ‘%s’, called", token);
      break;
    case MULT_DEF_FUNC:
      sprintf(error, "multiple definition of function ‘%s’", token);
      break;
    case PARAM_MISMATCH:
      sprintf(error, "number of parameters mismatched for function ‘%s’, called", token);
      break;
  }
  yyerror(error);
}

bool is_declared(size_t s_index, size_t f_index, size_t stmt_number) {
  return
	(symbol_table[s_index].decl_scope[f_index] != -1 &&
	symbol_table[s_index].decl_scope[f_index] < stmt_number) ||
	(symbol_table[s_index].decl_scope[FUNCTION_TABLE_SIZE] != -1 &&
	symbol_table[s_index].decl_scope[FUNCTION_TABLE_SIZE] < stmt_number);
}

bool is_initialized(size_t s_index, size_t f_index, size_t stmt_number) {
  return
	symbol_table[s_index].decl_scope[f_index] != -1 ?
	(symbol_table[s_index].init_scope[f_index] != -1 &&
	symbol_table[s_index].init_scope[f_index] < stmt_number) :
	(symbol_table[s_index].init_scope[FUNCTION_TABLE_SIZE] != -1 &&
	symbol_table[s_index].init_scope[FUNCTION_TABLE_SIZE] < stmt_number) ||
	(symbol_table[s_index].init_scope[f_index] != -1 &&
	symbol_table[s_index].init_scope[f_index] < stmt_number);
}

int is_defined_function(const char *func) {
  size_t index = string_hash(func, FUNCTION_TABLE_SIZE);
  while (function_table[index].id) {
    if (!strcmp(function_table[index].id, func))
      return index;
    index = (index + 1) % FUNCTION_TABLE_SIZE;
  }
  return -1;
}


#line 140 "grammar.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "grammar.tab.h".  */
#ifndef YY_YY_GRAMMAR_TAB_H_INCLUDED
# define YY_YY_GRAMMAR_TAB_H_INCLUDED
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
    SEMICOLON = 258,
    COMMA = 259,
    POPEN = 260,
    PCLOSE = 261,
    BOPEN = 262,
    BCLOSE = 263,
    VOID = 264,
    INT = 265,
    IF = 266,
    ELSE = 267,
    WHILE = 268,
    RETURN = 269,
    ASSIGN = 270,
    NUM = 271,
    ID = 272,
    OR = 273,
    AND = 274,
    UNIARITHOP = 275,
    UNILOGOP = 276,
    ADDOP = 277,
    MULOP = 278,
    LOGEQOP = 279,
    LOGCMPOP = 280,
    UNARY = 281
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef char * YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_GRAMMAR_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 218 "grammar.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   128

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  27
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  133

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      25,    26
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   118,   118,   122,   124,   126,   127,   129,   136,   135,
     138,   140,   154,   140,   158,   171,   171,   173,   176,   187,
     188,   197,   176,   211,   212,   215,   220,   219,   222,   224,
     240,   244,   244,   251,   253,   257,   259,   263,   264,   265,
     266,   267,   269,   274,   278,   281,   282,   286,   278,   298,
     301,   302,   306,   307,   298,   321,   324,   324,   331,   331,
     337,   337,   345,   356,   345,   362,   361,   373,   372,   384,
     383,   395,   394,   409,   408,   420,   419,   431,   431,   441,
     441,   457,   457,   462,   474,   475,   462,   491,   507,   515,
     516,   521,   520,   525
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "COMMA", "POPEN", "PCLOSE",
  "BOPEN", "BCLOSE", "VOID", "INT", "IF", "ELSE", "WHILE", "RETURN",
  "ASSIGN", "NUM", "ID", "OR", "AND", "UNIARITHOP", "UNILOGOP", "ADDOP",
  "MULOP", "LOGEQOP", "LOGCMPOP", "UNARY", "$accept", "program",
  "decl_list", "decl", "var_decl", "id_list", "$@1", "decl_or_def", "$@2",
  "$@3", "func_decl", "$@4", "func_body", "$@5", "$@6", "$@7", "$@8",
  "params", "param_list", "$@9", "param", "var_type", "compound_stmt",
  "$@10", "local_decl_list", "stmt_list", "stmt", "expr_stmt",
  "while_stmt", "$@11", "$@12", "$@13", "$@14", "if_stmt", "$@15", "$@16",
  "$@17", "$@18", "$@19", "else_stmt", "$@20", "return_stmt", "$@21",
  "$@22", "expr", "$@23", "$@24", "$@25", "$@26", "$@27", "$@28", "$@29",
  "$@30", "$@31", "$@32", "$@33", "$@34", "$@35", "$@36", "args",
  "arg_list", "$@37", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281
};
# endif

#define YYPACT_NINF -54

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-54)))

#define YYTABLE_NINF -84

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      17,   -54,   -54,     3,    17,   -54,   -54,   -54,    -9,    15,
     -54,   -54,    -1,    37,   -54,   -54,   -54,   -54,   -10,    43,
     -54,   -54,   -54,   -54,    38,    82,    44,    47,   -54,   -54,
     -54,    42,   -54,   -54,   -12,   -54,   -54,    55,   -54,    51,
      82,    61,    77,    82,    82,   -54,   -54,   -54,   -54,   -54,
     -54,    88,   -54,   -54,    27,   -54,   -54,   -54,   -54,    82,
      82,    82,    82,    82,    82,   -54,    86,   -54,    82,    82,
      85,    89,    74,   -54,    93,    58,    94,   -54,   -12,   -12,
     -54,    91,   -54,   -54,    99,   -54,   -54,   -54,    82,    86,
     -12,   -54,    38,    53,   -54,   -54,   -54,   -54,    97,   -54,
     -54,   -54,   -54,   -54,   -54,    -2,   101,   112,   116,    82,
     -54,   -54,   -54,   -54,     6,    82,    82,   -54,   -12,   -12,
     114,   115,   -54,   -54,    72,    72,   -54,   -54,   110,   -54,
     -54,    72,   -54
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    15,    30,     0,     2,     4,     5,     6,     0,     0,
       1,     3,    14,     0,    10,    17,    18,    16,     0,     0,
       7,     8,    12,    19,     0,     0,    25,    14,     9,    81,
      88,    87,    79,    77,    13,    24,    20,    23,    28,     0,
       0,     0,     0,     0,     0,    65,    67,    73,    75,    69,
      71,     0,    26,    29,     0,    63,    84,    80,    78,     0,
       0,     0,     0,     0,     0,    21,     0,    82,     0,    90,
      66,    68,    74,    76,    70,    72,     0,    27,    64,    93,
      85,    89,    31,    22,     0,    91,    34,    86,     0,    36,
      92,    33,     0,     0,    43,    32,    49,    44,    60,    38,
      35,    37,    40,    39,    41,     0,     0,     0,     0,     0,
      42,    50,    45,    59,     0,     0,     0,    61,    51,    46,
       0,     0,    52,    47,     0,     0,    53,    48,    55,    56,
      54,     0,    57
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -54,   -54,   -54,   119,    35,   -54,   -54,   102,   -54,   -54,
     -54,   -54,   118,   -54,   -54,   -54,   -54,   -54,   -54,   -54,
      59,   -24,    52,   -54,   -54,   -54,   -53,   -54,   -54,   -54,
     -54,   -54,   -54,   -54,   -54,   -54,   -54,   -54,   -54,   -54,
     -54,   -54,   -54,   -54,   -25,   -54,   -54,   -54,   -54,   -54,
     -54,   -54,   -54,   -54,   -54,   -54,   -54,   -54,   -54,   -54,
     -54,   -54
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    13,    24,    14,    18,    25,
       7,     9,    15,    19,    26,    51,    76,    36,    37,    66,
      38,     8,    99,    86,    89,    93,   100,   101,   102,   107,
     116,   121,   125,   103,   106,   115,   120,   124,   128,   130,
     131,   104,   108,   109,   105,    41,    68,    59,    60,    63,
      64,    61,    62,    44,    43,    40,    42,    69,    84,    80,
      81,    88
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      34,   110,    39,    10,   -18,    22,    45,    46,    12,   117,
      47,    48,    49,    50,   -11,    54,    45,    46,    57,    58,
      47,    48,    49,    50,    45,    46,     1,     2,    47,    48,
      49,    50,    16,    67,    70,    71,    72,    73,    74,    75,
      20,    21,    39,    78,    79,    45,    46,   -83,    23,    47,
      48,    49,    50,    35,     2,    27,    94,   -62,    29,    52,
      82,    95,   -11,    90,    96,    92,    97,    98,    53,    30,
      31,   126,   127,    32,    33,    94,    55,    29,   132,    82,
      47,    48,    56,    96,   114,    97,    98,    29,    30,    31,
     118,   119,    32,    33,    65,    85,     2,    48,    30,    31,
     -58,    82,    32,    33,    46,    87,   111,    47,    48,    49,
      50,    47,    48,    49,    50,    47,    48,   112,    50,   113,
     122,   123,   129,    11,    91,    77,    28,    17,    83
};

static const yytype_uint8 yycheck[] =
{
      25,     3,    26,     0,     5,    15,    18,    19,    17,     3,
      22,    23,    24,    25,    15,    40,    18,    19,    43,    44,
      22,    23,    24,    25,    18,    19,     9,    10,    22,    23,
      24,    25,    17,     6,    59,    60,    61,    62,    63,    64,
       3,     4,    66,    68,    69,    18,    19,     5,     5,    22,
      23,    24,    25,     9,    10,    17,     3,    15,     5,     4,
       7,     8,    15,    88,    11,    89,    13,    14,    17,    16,
      17,   124,   125,    20,    21,     3,    15,     5,   131,     7,
      22,    23,     5,    11,   109,    13,    14,     5,    16,    17,
     115,   116,    20,    21,     6,     4,    10,    23,    16,    17,
       3,     7,    20,    21,    19,     6,     5,    22,    23,    24,
      25,    22,    23,    24,    25,    22,    23,     5,    25,     3,
       6,     6,    12,     4,    89,    66,    24,     9,    76
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    10,    28,    29,    30,    31,    37,    48,    38,
       0,    30,    17,    32,    34,    39,    17,    39,    35,    40,
       3,     4,    15,     5,    33,    36,    41,    17,    34,     5,
      16,    17,    20,    21,    71,     9,    44,    45,    47,    48,
      82,    72,    83,    81,    80,    18,    19,    22,    23,    24,
      25,    42,     4,    17,    71,    15,     5,    71,    71,    74,
      75,    78,    79,    76,    77,     6,    46,     6,    73,    84,
      71,    71,    71,    71,    71,    71,    43,    47,    71,    71,
      86,    87,     7,    49,    85,     4,    50,     6,    88,    51,
      71,    31,    48,    52,     3,     8,    11,    13,    14,    49,
      53,    54,    55,    60,    68,    71,    61,    56,    69,    70,
       3,     5,     5,     3,    71,    62,    57,     3,    71,    71,
      63,    58,     6,     6,    64,    59,    53,    53,    65,    12,
      66,    67,    53
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    27,    28,    29,    29,    30,    30,    31,    33,    32,
      32,    35,    36,    34,    34,    38,    37,    37,    40,    41,
      42,    43,    39,    44,    44,    44,    46,    45,    45,    47,
      48,    50,    49,    51,    51,    52,    52,    53,    53,    53,
      53,    53,    54,    54,    56,    57,    58,    59,    55,    61,
      62,    63,    64,    65,    60,    66,    67,    66,    69,    68,
      70,    68,    72,    73,    71,    74,    71,    75,    71,    76,
      71,    77,    71,    78,    71,    79,    71,    80,    71,    81,
      71,    82,    71,    83,    84,    85,    71,    71,    71,    86,
      86,    88,    87,    87
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     0,     4,
       1,     0,     0,     5,     1,     0,     3,     2,     0,     0,
       0,     0,     9,     1,     1,     0,     0,     4,     1,     2,
       1,     0,     5,     2,     0,     2,     0,     1,     1,     1,
       1,     1,     2,     1,     0,     0,     0,     0,     9,     0,
       0,     0,     0,     0,    11,     0,     0,     3,     0,     3,
       0,     4,     0,     0,     5,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     3,     0,
       3,     0,     4,     0,     0,     0,     7,     1,     1,     1,
       0,     0,     4,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
  switch (yyn)
    {
        case 2:
#line 118 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("program", NULL, false, 1);
												  build_abstract_syntax_tree("program", 0, 0, ast_stack_top, 0, 0);
												}
#line 1403 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 123 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("decl_list", NULL, false, 2); }
#line 1409 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 124 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("decl_list", NULL, false, 1); }
#line 1415 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 126 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("decl", NULL, false, 1); }
#line 1421 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 127 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("decl", NULL, false, 1); }
#line 1427 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 131 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree(";", NULL, true, 0);
												  build_parse_tree("var_decl", NULL, false, 3);
												}
#line 1435 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 136 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree(",", NULL, true, 0); }
#line 1441 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 137 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("id_list", NULL, false, 3); }
#line 1447 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 138 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("id_list", NULL, false, 1); }
#line 1453 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 140 "grammar.y" /* yacc.c:1646  */
    { size_t s_index = symbol_table_entry(yylval),
														 f_index = current_function_table_index < 0 ? FUNCTION_TABLE_SIZE : current_function_table_index;
												  stmt_line_map[++stmt_number] = line_number + 1;
												  if (symbol_table[s_index].decl_scope[f_index] == -1)
												  	symbol_table[s_index].decl_scope[f_index] = stmt_number;
												  else {
												  	semantic_error(yylval, MULT_DECL_VAR);
												  	YYABORT;
												  }
												  if (symbol_table[s_index].init_scope[f_index] == -1)
												  	symbol_table[s_index].init_scope[f_index] = stmt_number;
												  build_parse_tree("ID", yylval, true, 0);
												  build_abstract_syntax_tree(yylval, IDBLOCK, 0, 0, 0, 0);
												}
#line 1472 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 154 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("=", NULL, true, 0); }
#line 1478 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 155 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("decl_def", NULL, false, 3);
												  build_abstract_syntax_tree("=", ASSIGNBLOCK, 0, 2, line_number + 1, stmt_number);
												}
#line 1486 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 158 "grammar.y" /* yacc.c:1646  */
    { size_t s_index = symbol_table_entry(yylval),
														 f_index = current_function_table_index < 0 ? FUNCTION_TABLE_SIZE : current_function_table_index;
												  stmt_line_map[++stmt_number] = line_number + 1;
												  if (symbol_table[s_index].decl_scope[f_index] == -1)
												  	symbol_table[s_index].decl_scope[f_index] = stmt_number;
												  else {
												  	semantic_error(yylval, MULT_DECL_VAR);
												  	YYABORT;
												  }
												  build_parse_tree("ID", yylval, true, 0);
												  build_parse_tree("decl_def", NULL, false, 1);
												}
#line 1503 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 171 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("void", NULL, true, 0); }
#line 1509 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 172 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("func_decl", NULL, false, 2); }
#line 1515 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 174 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("func_decl", NULL, false, 2); }
#line 1521 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 176 "grammar.y" /* yacc.c:1646  */
    { current_function_table_index = is_defined_function(yylval);
												  if (current_function_table_index != -1) {
												  	semantic_error(yylval, MULT_DEF_FUNC);
												  	YYABORT;
												  }
												  current_function_table_index = function_table_entry(yylval);
												  build_parse_tree("ID", yylval, true, 0);
												  stmt_line_map[++stmt_number] = line_number + 1;
												  build_abstract_syntax_tree(yylval, FUNCBLOCK, 0, 0, line_number + 1, stmt_number);
												  param_decl_stmt_number = stmt_number;
												}
#line 1537 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 187 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("(", NULL, true, 0); }
#line 1543 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 188 "grammar.y" /* yacc.c:1646  */
    { size_t stmt_count = ast_stack_top - 1;
												  while (!(ast_stack[stmt_count--]->type & FUNCBLOCK));
												  build_abstract_syntax_tree("param", 0, 0, ast_stack_top - stmt_count - 2, 0, 0);
												  Ast *tmp = ast_stack[ast_stack_top - 2];
												  ast_stack[ast_stack_top - 2] = ast_stack[ast_stack_top - 1];
												  ast_stack[ast_stack_top - 1] = tmp;
												  function_table[current_function_table_index].N_params = N_params;
												  N_params = 0;
												}
#line 1557 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 197 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree(")", NULL, true, 0); }
#line 1563 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 198 "grammar.y" /* yacc.c:1646  */
    { current_function_table_index = -1;
												  build_parse_tree("func_body", NULL, false, 5);
												  size_t stmt_count = ast_stack_top - 1;
												  while (!(ast_stack[stmt_count--]->type & FUNCBLOCK));
												  build_abstract_syntax_tree("body", 0, 0, ast_stack_top - stmt_count - 2, 0, 0);
												  Ast *tmp = ast_stack[ast_stack_top - 2];
												  ast_stack[ast_stack_top - 2] = ast_stack[--ast_stack_top];
												  build_abstract_syntax_tree(tmp->token, tmp->type, tmp->operator_type, 2,
												  	tmp->line_number, tmp->stmt_number);
												  free(tmp->token);
												  free(tmp);
												}
#line 1580 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 211 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("params", NULL, false, 1); }
#line 1586 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 212 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("void", NULL, true, 0);
												  build_parse_tree("params", NULL, false, 1);
												}
#line 1594 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 215 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("ε", NULL, true, 0);
												  build_parse_tree("params", NULL, false, 1);
												}
#line 1602 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 220 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree(",", NULL, true, 0); }
#line 1608 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 221 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("param_list", NULL, false, 3); }
#line 1614 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 222 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("param_list", NULL, false, 1); }
#line 1620 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 225 "grammar.y" /* yacc.c:1646  */
    { size_t s_index = symbol_table_entry(yylval);
												  if (symbol_table[s_index].decl_scope[current_function_table_index] == -1)
												  	symbol_table[s_index].decl_scope[current_function_table_index] =
												  	symbol_table[s_index].init_scope[current_function_table_index] = param_decl_stmt_number;
												  else {
												  	semantic_error(yylval, MULT_DECL_PARAM);
												  	YYABORT;
												  }
												  N_params++;
												  build_parse_tree("ID", yylval, true, 0);
												  build_parse_tree("param", NULL, false, 2);
												  stmt_line_map[++stmt_number] = line_number + 1;
												  build_abstract_syntax_tree(yylval, IDBLOCK, 0, 0, line_number + 1, stmt_number);
												}
#line 1639 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 240 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("int", NULL, true, 0);
												  build_parse_tree("type", NULL, false, 1);
												}
#line 1647 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 244 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("{", NULL, true, 0); }
#line 1653 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 247 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("}", NULL, true, 0);
												  build_parse_tree("comp_stmt", NULL, false, 4);
												}
#line 1661 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 252 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("local_decl", NULL, false, 2); }
#line 1667 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 253 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("ε", NULL, true, 0);
												  build_parse_tree("local_decl", NULL, false, 1);
												}
#line 1675 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 258 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("stmt_list", NULL, false, 2); }
#line 1681 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 259 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("ε", NULL, true, 0);
												  build_parse_tree("stmt_list", NULL, false, 1);
												}
#line 1689 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 263 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("stmt", NULL, false, 1); }
#line 1695 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 264 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("stmt", NULL, false, 1); }
#line 1701 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 265 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("stmt", NULL, false, 1); }
#line 1707 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 266 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("stmt", NULL, false, 1); }
#line 1713 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 267 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("stmt", NULL, false, 1); }
#line 1719 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 270 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree(";", NULL, true, 0);
												  build_parse_tree("expr_stmt", NULL, false, 2);
												  stmt_line_map[++stmt_number] = line_number + 1;
												}
#line 1728 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 274 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree(";", NULL, true, 0);
												  build_parse_tree("expr_stmt", NULL, false, 1);
												}
#line 1736 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 278 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("while", NULL, true, 0);
												  stmt_line_map[++stmt_number] = line_number + 1;
												}
#line 1744 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 281 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("(", NULL, true, 0); }
#line 1750 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 282 "grammar.y" /* yacc.c:1646  */
    { ast_stack[ast_stack_top - 1]->type |= CONDITION;
												  ast_stack[ast_stack_top - 1]->line_number = line_number + 1;
												  ast_stack[ast_stack_top - 1]->stmt_number = stmt_number;
												}
#line 1759 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 286 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree(")", NULL, true, 0); }
#line 1765 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 287 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("while_stmt", NULL, false, 5);
												  size_t stmt_count = ast_stack_top - 1;
												  while (!(ast_stack[stmt_count--]->type & CONDITION));
												  build_abstract_syntax_tree("true\nblock", TRUEBLOCK, 0, ast_stack_top - stmt_count - 2, 0, 0);
												  int stmt_line_number = ast_stack[ast_stack_top - 2]->line_number,
												  	  stmt_stmt_number = ast_stack[ast_stack_top - 2]->stmt_number;
												  ast_stack[ast_stack_top - 2]->line_number = ast_stack[ast_stack_top - 2]->stmt_number = 0;
												  ast_stack[ast_stack_top - 2]->type |= LOGOPBLOCK;
												  build_abstract_syntax_tree("while", CONTROLBLOCK, 0, 2, stmt_line_number, stmt_stmt_number);
												}
#line 1780 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 298 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("if", NULL, true, 0);
												  stmt_line_map[++stmt_number] = line_number + 1;
												}
#line 1788 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 301 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("(", NULL, true, 0); }
#line 1794 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 302 "grammar.y" /* yacc.c:1646  */
    { ast_stack[ast_stack_top - 1]->type |= CONDITION;
												  ast_stack[ast_stack_top - 1]->line_number = line_number + 1;
												  ast_stack[ast_stack_top - 1]->stmt_number = stmt_number;
												}
#line 1803 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 306 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree(")", NULL, true, 0); }
#line 1809 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 307 "grammar.y" /* yacc.c:1646  */
    { size_t stmt_count = ast_stack_top - 1;
												  while (!(ast_stack[stmt_count--]->type & CONDITION));
												  build_abstract_syntax_tree("true\nblock", TRUEBLOCK, 0, ast_stack_top - stmt_count - 2, 0, 0);
												}
#line 1818 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 311 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("if_stmt", NULL, false, 6);
												  size_t cond_block_offset = ast_stack[ast_stack_top - 1]->type & TRUEBLOCK ? 2 : 3,
												  		 stmt_line_number = ast_stack[ast_stack_top - cond_block_offset]->line_number,
												  		 stmt_stmt_number = ast_stack[ast_stack_top - cond_block_offset]->stmt_number;
												  ast_stack[ast_stack_top - cond_block_offset]->line_number = 0;
												  ast_stack[ast_stack_top - cond_block_offset]->stmt_number = 0;
												  ast_stack[ast_stack_top - cond_block_offset]->type |= LOGOPBLOCK;
												  build_abstract_syntax_tree("if", CONTROLBLOCK, 0, cond_block_offset, stmt_line_number, stmt_stmt_number);
												}
#line 1832 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 321 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("ε", NULL, true, 0);
												  build_parse_tree("else_stmt", NULL, false, 1);
												}
#line 1840 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 324 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("else", NULL, true, 0); }
#line 1846 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 325 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("else_stmt", NULL, false, 2);
												  size_t stmt_count = ast_stack_top - 1;
												  while (!(ast_stack[stmt_count--]->type & TRUEBLOCK));
												  build_abstract_syntax_tree("false\nblock", FALSEBLOCK, 0, ast_stack_top - stmt_count - 2, 0, 0);
												}
#line 1856 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 331 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("return", NULL, true, 0); }
#line 1862 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 332 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree(";", NULL, true, 0);
												  build_parse_tree("return_stmt", NULL, false, 2);
												  stmt_line_map[++stmt_number] = line_number + 1;
												  build_abstract_syntax_tree("return", RETURNBLOCK, 0, 0, line_number + 1, stmt_number);
												}
#line 1872 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 337 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("return", NULL, true, 0); }
#line 1878 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 339 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree(";", NULL, true, 0);
												  build_parse_tree("return_stmt", NULL, false, 3);
												  stmt_line_map[++stmt_number] = line_number + 1;
												  build_abstract_syntax_tree("return", RETURNBLOCK, 0, 1, line_number + 1, stmt_number);
												}
#line 1888 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 345 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("ID", yylval, true, 0);
												  build_abstract_syntax_tree(yylval, IDBLOCK, 0, 0, 0, 0);
												  size_t s_index = symbol_table_entry(yylval);
												  stmt_line_map[++stmt_number] = line_number + 1;
												  if (!is_declared(s_index, current_function_table_index, stmt_number)) {
												  	semantic_error(yylval, UN_DECL);
												  	YYABORT;
												  }
												  if (symbol_table[s_index].init_scope[current_function_table_index] == -1)
												  	symbol_table[s_index].init_scope[current_function_table_index] = stmt_number;
												}
#line 1904 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 356 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("=", NULL, true, 0); }
#line 1910 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 357 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("expr", NULL, false, 3);
												  build_abstract_syntax_tree("=", ASSIGNBLOCK, 0, 2, line_number + 1, stmt_number);
												  --stmt_number;
												}
#line 1919 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 362 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("\\|\\|", NULL, true, 0);
												  build_abstract_syntax_tree("||", LOGOPBLOCK, LOR, 0, 0, 0);
												}
#line 1927 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 365 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("expr", NULL, false, 3);
												  Ast *tmp = ast_stack[ast_stack_top - 2];
												  ast_stack[ast_stack_top - 2] = ast_stack[--ast_stack_top];
												  build_abstract_syntax_tree(tmp->token, tmp->type, tmp->operator_type, 2, 0, 0);
												  free(tmp->token);
												  free(tmp);
												}
#line 1939 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 373 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("&&", NULL, true, 0);
												  build_abstract_syntax_tree("&&", LOGOPBLOCK, LAND, 0, 0, 0);
												}
#line 1947 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 376 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("expr", NULL, false, 3);
												  Ast *tmp = ast_stack[ast_stack_top - 2];
												  ast_stack[ast_stack_top - 2] = ast_stack[--ast_stack_top];
												  build_abstract_syntax_tree(tmp->token, tmp->type, tmp->operator_type, 2, 0, 0);
												  free(tmp->token);
												  free(tmp);
												}
#line 1959 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 384 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("LOGEQOP", yytext, true, 0);
												  build_abstract_syntax_tree(yytext, LOGOPBLOCK, !strcmp(yytext, "==") ? EQ : NEQ, 0, 0, 0);
												}
#line 1967 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 387 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("expr", NULL, false, 3);
												  Ast *tmp = ast_stack[ast_stack_top - 2];
												  ast_stack[ast_stack_top - 2] = ast_stack[--ast_stack_top];
												  build_abstract_syntax_tree(tmp->token, tmp->type, tmp->operator_type, 2, 0, 0);
												  free(tmp->token);
												  free(tmp);
												}
#line 1979 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 395 "grammar.y" /* yacc.c:1646  */
    { char printable[10];
												  sprintf(printable, "\\%s", yytext);
												  build_parse_tree("LOGCMPOP", printable, true, 0);
												  build_abstract_syntax_tree(yytext, LOGOPBLOCK, !strcmp(yytext, ">=") ? GEQ :
												  	!strcmp(yytext, ">") ? GT : !strcmp(yytext, "<") ? LT : LEQ, 0, 0, 0);
												}
#line 1990 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 401 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("expr", NULL, false, 3);
												  Ast *tmp = ast_stack[ast_stack_top - 2];
												  ast_stack[ast_stack_top - 2] = ast_stack[--ast_stack_top];
												  build_abstract_syntax_tree(tmp->token, tmp->type, tmp->operator_type, 2, 0, 0);
												  free(tmp->token);
												  free(tmp);
												}
#line 2002 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 409 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("ADDOP", yytext, true, 0);
												  build_abstract_syntax_tree(yytext, ARITHOPBLOCK, !strcmp(yytext, "+") ? ADD : SUB, 0, 0, 0);
												}
#line 2010 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 412 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("expr", NULL, false, 3);
												  Ast *tmp = ast_stack[ast_stack_top - 2];
												  ast_stack[ast_stack_top - 2] = ast_stack[--ast_stack_top];
												  build_abstract_syntax_tree(tmp->token, tmp->type, tmp->operator_type, 2, 0, 0);
												  free(tmp->token);
												  free(tmp);
												}
#line 2022 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 420 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("MULOP", yytext, true, 0);
												  build_abstract_syntax_tree(yytext, ARITHOPBLOCK, !strcmp(yytext, "*") ? MUL :
												  	!strcmp(yytext, "/") ? DIV : REM, 0, 0, 0);
												}
#line 2031 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 424 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("expr", NULL, false, 3);
												  Ast *tmp = ast_stack[ast_stack_top - 2];
												  ast_stack[ast_stack_top - 2] = ast_stack[--ast_stack_top];
												  build_abstract_syntax_tree(tmp->token, tmp->type, tmp->operator_type, 2, 0, 0);
												  free(tmp->token);
												  free(tmp);
												}
#line 2043 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 431 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("UNILOGOP", yytext, true, 0);
												  build_abstract_syntax_tree(yytext, LOGOPBLOCK, NOT, 0, 0, 0);
												}
#line 2051 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 434 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("expr", NULL, false, 2);
												  Ast *tmp = ast_stack[ast_stack_top - 2];
												  ast_stack[ast_stack_top - 2] = ast_stack[--ast_stack_top];
												  build_abstract_syntax_tree(tmp->token, tmp->type, tmp->operator_type, 1, 0, 0);
												  free(tmp->token);
												  free(tmp);
												}
#line 2063 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 441 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("UNIARITHOP", yytext, true, 0);
												  unary_minus_stack[unary_minus_stack_top++] = !strcmp(yytext, "-") ? true : false;
												  if (unary_minus_stack[unary_minus_stack_top - 1]) {
												  	build_abstract_syntax_tree("0", NUMBLOCK, 0, 0, 0, 0);
												  	build_abstract_syntax_tree(yytext, ARITHOPBLOCK, SUB, 0, 0, 0);
												  }
												}
#line 2075 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 448 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("expr", NULL, false, 2);
												  if (unary_minus_stack[--unary_minus_stack_top]) {
												  	Ast *tmp = ast_stack[ast_stack_top - 2];
												  	ast_stack[ast_stack_top - 2] = ast_stack[--ast_stack_top];
												  	build_abstract_syntax_tree(tmp->token, tmp->type, tmp->operator_type, 2, 0, 0);
												  	free(tmp->token);
												  	free(tmp);
												  }
												}
#line 2089 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 457 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("(", NULL, true, 0); }
#line 2095 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 459 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree(")", NULL, true, 0);
												  build_parse_tree("expr", NULL, false, 3);
												}
#line 2103 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 462 "grammar.y" /* yacc.c:1646  */
    { int f_index = is_defined_function(yylval);
												  if (f_index < 0) {
												  	semantic_error(yylval, UN_DEF);
												  	YYABORT;
												  }
												  build_parse_tree("ID", yylval, true, 0);
												  calling_function_stack[calling_function_stack_top++] = f_index;
												  calling_function_stack[calling_function_stack_top++] = is_new_stmt ? line_number + 1 : 0;
												  calling_function_stack[calling_function_stack_top++] = is_new_stmt ? stmt_number + 1 : 0;
												  calling_function_N_args_stack_top += 1;
												  is_new_stmt = false;
												}
#line 2120 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 474 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("(", NULL, true, 0); }
#line 2126 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 475 "grammar.y" /* yacc.c:1646  */
    { size_t f_index = calling_function_stack[calling_function_stack_top - 3],
												               line = calling_function_stack[calling_function_stack_top - 2],
												               stmt = calling_function_stack[calling_function_stack_top - 1];
												  calling_function_stack_top -= 3;
												  if (calling_function_N_args_stack[calling_function_N_args_stack_top--] !=
												  	function_table[f_index].N_params) {
												  	semantic_error(function_table[f_index].id, PARAM_MISMATCH);
												  	YYABORT;
												  }
												  calling_function_N_args_stack[calling_function_N_args_stack_top + 1] = 0;
												  build_abstract_syntax_tree(function_table[f_index].id, CALLBLOCK, 0,
												  	function_table[f_index].N_params, line, stmt);
												}
#line 2144 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 488 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree(")", NULL, true, 0);
												  build_parse_tree("expr", NULL, false, 4);
												}
#line 2152 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 491 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("ID", yylval, true, 0);
												  build_parse_tree("expr", NULL, false, 1);
												  build_abstract_syntax_tree(yylval, IDBLOCK, 0, 0, 0, 0);
												  size_t s_index = symbol_table_entry(yylval),
												  		 f_index = current_function_table_index < 0 ? FUNCTION_TABLE_SIZE : current_function_table_index;
												  if (!is_declared(s_index, f_index, stmt_number)) {
												  	semantic_error(yylval, UN_DECL);
												  	YYABORT;
												  }
												  if (!is_initialized(s_index, f_index, stmt_number)) {
												  	semantic_error(yylval, NO_INIT);
												  	YYABORT;
												  }
												  if (symbol_table[s_index].use_scope[f_index] == -1)
												  	symbol_table[s_index].use_scope[f_index] = stmt_number;
												}
#line 2173 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 507 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("NUM", yylval, true, 0);
												  build_parse_tree("expr", NULL, false, 1);
												  build_abstract_syntax_tree(yylval, NUMBLOCK, 0, 0, 0, 0);
												  int i = unary_minus_stack_top - 1, is_minus = 0;
												  while (i >= 0) is_minus += unary_minus_stack[i--] ? 1 : 0;
												  constant_set = insert_into_constant_set(constant_set, is_minus % 2 ? - atol(yylval) : atol(yylval));
												}
#line 2185 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 515 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("args", NULL, false, 1); }
#line 2191 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 516 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("ε", NULL, true, 0);
												  build_parse_tree("args", NULL, false, 1);
												}
#line 2199 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 521 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree(",", NULL, true, 0); }
#line 2205 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 522 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("arg_list", NULL, false, 3);
												  calling_function_N_args_stack[calling_function_N_args_stack_top] += 1;
												}
#line 2213 "grammar.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 525 "grammar.y" /* yacc.c:1646  */
    { build_parse_tree("arg_list", NULL, false, 1);
												  calling_function_N_args_stack[calling_function_N_args_stack_top] += 1;
												}
#line 2221 "grammar.tab.c" /* yacc.c:1646  */
    break;


#line 2225 "grammar.tab.c" /* yacc.c:1646  */
      default: break;
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 528 "grammar.y" /* yacc.c:1906  */
