#ifndef _SMART_CALC_V1_H_
#define _SMART_CALC_V1_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 255

#define S21_INF 1.0 / 0.0

#define NONE -1

typedef enum { OK, ERROR, INFNTY } Errors;

typedef enum { ADD, SUB, MULT, DIV, MOD } BinaryOp;

typedef enum { COS, SIN, TAN, ACOS, ASIN, ATAN, SQRT, LN, LOG } Function;

typedef enum {
  VARIABLE,
  NUMBER,
  LEFT_PARENTHESIS,
  ADD_SUB,
  MULT_DIV,
  POW,
  UNARY,
  FUNCTION
} Token;

typedef struct stack {
  Token type;
  Function func;
  BinaryOp oper;
  double number;
  struct stack *next;
} Stack;

void pushElement(Stack **stack, int type, int func, int oper, double num);
double popElement(Stack **stack);
void cleanStack(Stack **stack);

void fakeAtod(Stack **outputStack, char **string);
void push2stack(Stack **temp, Stack **outputStack, int type, int func, int oper,
                char **string, int shift);
void reverseStack(Stack **reversePN, Stack **outputStack);
void string2stackPN(Stack **reversePN, char *string);
int binaryOperation(Stack **reversePN, Stack **calculationStack);
int unaryOperation(Stack **reversePN, Stack **calculationStack);
int calculatePN(char *string, double *result, double value);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // _SMART_CALC_V1_H_
