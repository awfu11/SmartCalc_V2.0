#include "smart_calc_v1.h"

int calculatePN(char *string, double *result, double value) {
  Stack *reversePN = NULL;
  string2stackPN(&reversePN, string);
  Stack *calculationStack = NULL;
  int resultCalc = OK;
  while (reversePN != NULL) {
    if (reversePN->type == NUMBER) {
      pushElement(&calculationStack, NUMBER, NONE, NONE,
                  popElement(&reversePN));
    } else if (reversePN->type >= ADD_SUB && reversePN->type <= POW) {
      if ((resultCalc = binaryOperation(&reversePN, &calculationStack)) != OK) {
        break;
      }
    } else if (reversePN->type >= UNARY) {
      if ((resultCalc = unaryOperation(&reversePN, &calculationStack)) != OK) {
        break;
      }
    } else {
      popElement(&reversePN);
      pushElement(&calculationStack, NUMBER, NONE, NONE, value);
    }
  }
  if (resultCalc == OK) {
    *result = popElement(&calculationStack);
  }
  cleanStack(&reversePN);
  cleanStack(&calculationStack);
  return resultCalc;
}

void string2stackPN(Stack **reversePN, char *string) {
  Stack *outputStack = NULL, *temp = NULL;
  int checkUnary = 1;
  while (*string) {
    if (isdigit(*string) || !strncmp(string, "pi", 2) ||
        !strncmp(string, "e", 1)) {
      fakeAtod(&outputStack, &string);
      checkUnary = 0;
    } else if (*string == 'x' || *string == 'X') {
      pushElement(&outputStack, VARIABLE, NONE, NONE, 0);
      checkUnary = 0;
      string += 1;
    } else if (*string == '(') {
      pushElement(&temp, LEFT_PARENTHESIS, NONE, NONE, 0);
      string += 1;
    } else if (*string == ')') {
      push2stack(&temp, &outputStack, LEFT_PARENTHESIS + 1, NONE, NONE, &string,
                 1);
    } else if (*string == '+') {
      if (checkUnary != 1) {
        push2stack(&temp, &outputStack, ADD_SUB, NONE, ADD, &string, 1);
        checkUnary = 1;
      }
    } else if (*string == '-') {
      push2stack(&temp, &outputStack, ((checkUnary) ? UNARY : ADD_SUB), NONE,
                 ((checkUnary) ? NONE : SUB), &string, 1);
      checkUnary = (checkUnary) ? 0 : 1;
    } else if (*string == '*') {
      push2stack(&temp, &outputStack, MULT_DIV, NONE, MULT, &string, 1);
      checkUnary = 1;
    } else if (*string == '/') {
      push2stack(&temp, &outputStack, MULT_DIV, NONE, DIV, &string, 1);
      checkUnary = 1;
    } else if (*string == '%' || !strncmp(string, "mod", 3)) {
      push2stack(&temp, &outputStack, MULT_DIV, NONE, MOD, &string, 0);
      checkUnary = 1;
      (*string == '%') ? (string += 1) : (string += 3);
    } else if (*string == '^') {
      push2stack(&temp, &outputStack, POW, NONE, NONE, &string, 1);
      checkUnary = 1;
    } else if (!strncmp(string, "sin", 3)) {
      push2stack(&temp, &outputStack, FUNCTION, SIN, NONE, &string, 3);
    } else if (!strncmp(string, "cos", 3)) {
      push2stack(&temp, &outputStack, FUNCTION, COS, NONE, &string, 3);
    } else if (!strncmp(string, "tan", 3)) {
      push2stack(&temp, &outputStack, FUNCTION, TAN, NONE, &string, 3);
    } else if (!strncmp(string, "asin", 4)) {
      push2stack(&temp, &outputStack, FUNCTION, ASIN, NONE, &string, 4);
    } else if (!strncmp(string, "acos", 4)) {
      push2stack(&temp, &outputStack, FUNCTION, ACOS, NONE, &string, 4);
    } else if (!strncmp(string, "atan", 4)) {
      push2stack(&temp, &outputStack, FUNCTION, ATAN, NONE, &string, 4);
    } else if (!strncmp(string, "ln", 2)) {
      push2stack(&temp, &outputStack, FUNCTION, LN, NONE, &string, 2);
    } else if (!strncmp(string, "log", 3)) {
      push2stack(&temp, &outputStack, FUNCTION, LOG, NONE, &string, 3);
    } else if (!strncmp(string, "sqrt", 4)) {
      push2stack(&temp, &outputStack, FUNCTION, SQRT, NONE, &string, 4);
    } else if (*string == ' ') {
      string += 1;
    }
  }
  while (temp != NULL) {
    pushElement(&outputStack, temp->type, temp->func, temp->oper, temp->number);
    popElement(&temp);
  }
  reverseStack(reversePN, &outputStack);
}

void push2stack(Stack **temp, Stack **outputStack, int type, int func, int oper,
                char **string, int shift) {
  while (*temp != NULL && (int)(*temp)->type >= type) {
    pushElement(outputStack, (*temp)->type, (*temp)->func, (*temp)->oper,
                (*temp)->number);
    popElement(temp);
  }
  if (type == LEFT_PARENTHESIS + 1 && oper == NONE) {
    popElement(temp);
  } else {
    pushElement(temp, type, func, oper, 0);
  }
  *string += shift;
}

void reverseStack(Stack **reversePN, Stack **outputStack) {
  while (*outputStack != NULL) {
    pushElement(reversePN, (*outputStack)->type, (*outputStack)->func,
                (*outputStack)->oper, (*outputStack)->number);
    popElement(outputStack);
  }
}

void fakeAtod(Stack **outputStack, char **string) {
  if (!strncmp(*string, "pi", 2)) {
    pushElement(outputStack, NUMBER, NONE, NONE, M_PI);
    *string += 2;
  } else if (!strncmp(*string, "e", 1)) {
    pushElement(outputStack, NUMBER, NONE, NONE, M_E);
    *string += 1;
  } else {
    char *pointer = NULL;
    double num = strtod(*string, &pointer);
    pushElement(outputStack, NUMBER, NONE, NONE, num);
    *string = pointer;
  }
}

int binaryOperation(Stack **reversePN, Stack **calculationStack) {
  double secondNumber = popElement(calculationStack);
  double firstNumber = popElement(calculationStack);
  double result = 0.0;
  int resultCalc = OK;
  if ((*reversePN)->oper == ADD) {
    result = firstNumber + secondNumber;
  } else if ((*reversePN)->oper == SUB) {
    result = firstNumber - secondNumber;
  } else if ((*reversePN)->oper == MULT) {
    result = firstNumber * secondNumber;
  } else if ((*reversePN)->oper == DIV) {
    result = firstNumber / secondNumber;
  } else if ((*reversePN)->oper == MOD) {
    result = fmod(firstNumber, secondNumber);
  } else if ((*reversePN)->type == POW) {
    result = pow(firstNumber, secondNumber);
  }
  if (fabs(result) == S21_INF) {
    resultCalc = INFNTY;
  } else if (isnan(result)) {
    resultCalc = ERROR;
  }
  popElement(reversePN);
  pushElement(reversePN, NUMBER, NONE, NONE, result);
  return resultCalc;
}

int unaryOperation(Stack **reversePN, Stack **calculationStack) {
  int resultCalc = OK;
  double number = popElement(calculationStack);
  double result = 0.0;
  if ((*reversePN)->type == UNARY) {
    result = -1.0 * number;
  } else if ((*reversePN)->func == SIN) {
    result = sin(number);
  } else if ((*reversePN)->func == COS) {
    result = cos(number);
  } else if ((*reversePN)->func == TAN) {
    result = tan(number);
  } else if ((*reversePN)->func == ASIN) {
    result = asin(number);
  } else if ((*reversePN)->func == ACOS) {
    result = acos(number);
  } else if ((*reversePN)->func == ATAN) {
    result = atan(number);
  } else if ((*reversePN)->func == LN) {
    result = log(number);
  } else if ((*reversePN)->func == LOG) {
    result = log10(number);
  } else if ((*reversePN)->func == SQRT) {
    result = sqrt(number);
  }
  if (fabs(result) == S21_INF) {
    resultCalc = INFNTY;
  } else if (isnan(result)) {
    resultCalc = ERROR;
  }
  popElement(reversePN);
  pushElement(reversePN, NUMBER, NONE, NONE, result);
  return resultCalc;
}
