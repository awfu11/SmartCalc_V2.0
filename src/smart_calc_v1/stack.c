#include "smart_calc_v1.h"

void pushElement(Stack **stack, int type, int func, int oper, double num) {
  Stack *temp = (Stack *)malloc(sizeof(Stack));
  if (temp == NULL) {
    return;
  }
  temp->type = type;
  temp->func = func;
  temp->oper = oper;
  temp->number = num;
  temp->next = *stack;
  *stack = temp;
}

double popElement(Stack **stack) {
  double number = 0;
  Stack *temp = NULL;
  if (*stack == NULL) {
    exit(0);
  }
  number = (*stack)->number;
  temp = *stack;
  *stack = (*stack)->next;
  free(temp);
  return number;
}

void cleanStack(Stack **stack) {
  while (*stack != NULL) {
    popElement(stack);
  }
}
