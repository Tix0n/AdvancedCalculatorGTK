#include "stack_sym.h"

stack_sym *create_sym() {
  stack_sym *head = malloc(sizeof(stack_sym));
  head->ptr = NULL;
  head->symbol = '\0';
  return head;
}

void destroy_sym(stack_sym *stack) {
  while (stack->ptr) pop_sym(stack);
  free(stack);
  stack = NULL;
}

void push_sym(stack_sym *stack, char symbol) {
  stack_sym *tmp = malloc(sizeof(stack_sym));
  if (tmp) {
    tmp->ptr = stack->ptr;
    tmp->symbol = stack->symbol;
    stack->ptr = tmp;
    stack->symbol = symbol;
  }
}

void pop_sym(stack_sym *stack) {
  if (stack->ptr) {
    stack_sym *tmp = stack->ptr;
    stack->symbol = stack->ptr->symbol;
    stack->ptr = stack->ptr->ptr;
    free(tmp);
  } else {
    free(stack);
    stack = NULL;
  }
}

char peek_stack_sym(stack_sym *stack) {
  char res = '\0';
  if (stack->symbol == '\0') {
    res = '\0';
  } else {
    res = stack->symbol;
  }
  return res;
}