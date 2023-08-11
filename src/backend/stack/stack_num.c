#include "stack_num.h"

stack_num* create_num() {
  stack_num* head = malloc(sizeof(stack_num));
  head->ptr = NULL;
  head->number = '\0';
  return head;
}

void destroy_num(stack_num* stack) {
  while (stack->ptr) pop_num(stack);
  free(stack);
  stack = NULL;
}

void push_num(stack_num* stack, double number) {
  stack_num* tmp = malloc(sizeof(stack_num));
  if (tmp) {
    tmp->ptr = stack->ptr;
    tmp->number = stack->number;
    stack->ptr = tmp;
    stack->number = number;
  }
}

void pop_num(stack_num* stack) {
  if (stack->ptr) {
    stack_num* tmp = stack->ptr;
    stack->number = stack->ptr->number;
    stack->ptr = stack->ptr->ptr;
    free(tmp);
  }
}

double peek_stack_num(stack_num* stack, int* flag) {
  double res = 0.0;
  if (fabs(stack->number) <= EPS) {
  } else if (stack->number == '\0') {
    res = 0.0;
    *flag = -1;
  } else {
    res = stack->number;
  }
  return res;
}
