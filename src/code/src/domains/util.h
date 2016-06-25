#ifndef UTIL_H
#define UTIL_H

#include "../limit.h"
#include "../parser/parser.h"
#include "../dataflow/cfg.h"

#define   PR_RD   1
#define   PR_WR   1

#define   PR_ADD  1
#define   PR_SUB  1
#define   PR_MUL  1
#define   PR_DIV  1
#define   PR_REM  1

#define   PR_EQ   1
#define   PR_NEQ  1
#define   PR_GEQ  1
#define   PR_LEQ  1
#define   PR_GT   1
#define   PR_LT   1
#define   PR_NEG  1
#define   PR_AND  1
#define   PR_OR	  1

#define EVALUATION_STACK_SIZE 1000

#define PR_ARITH(p) (p + (1-p)/(var_t) ((var_t) MAXINT - (var_t) MININT + 1))
#define PR_BOOL(p) (p + (1-p)/2)

#endif