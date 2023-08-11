#ifndef SRC_BACKEND_STACK_STACK_SYM_H
#define SRC_BACKEND_STACK_STACK_SYM_H

#include <stdio.h>
#include <stdlib.h>
/*!
  Стек символов
*/
typedef struct stack_s {
  struct stack_s *ptr;  ///< указатель на следующий узел
  char symbol;          ///< данные
} stack_sym;

/*!
Функция создания стека
*/
stack_sym *create_sym();
/*!
Функция занесения элемента в стек
\param *stack - указатель на стек к которому хотим добавить элемент
\param symbol - данные
*/
void push_sym(stack_sym *stack, char symbol);
/*!
Функция для извлечения верхнего элемента из стека
\param *stack - указатель на стек из которого мы хотим извлечь элемент
*/
void pop_sym(stack_sym *stack);
/*!
Функция для удаления стека
\param *stack - указатель на стек который мы хотим удалить
*/
void destroy_sym(stack_sym *stack);
/*!
Функция для возврата верхнего элемента стека
\param *stack - указатель на стек к которому хотим добавить элемент
\return Верхний элемент стека
*/
char peek_stack_sym(stack_sym *stack);

#endif  // SRC_BACKEND_STACK_STACK_SYM_H