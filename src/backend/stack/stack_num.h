#ifndef SRC_BACKEND_STACK_STACK_NUM_H
#define SRC_BACKEND_STACK_STACK_NUM_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPS 1e-7
/*!
  Стек чисел типа 'double'
*/
typedef struct stack_n {
  struct stack_n *ptr;  ///< указатель на следующий узел
  double number;        ///< данные
} stack_num;

/*!
Функция создания стека
*/
stack_num *create_num();
/*!
Функция занесения элемента в стек
\param *stack - указатель на стек к которому хотим добавить элемент
\param number - данные
*/
void push_num(stack_num *stack, double number);
/*!
Функция для извлечения верхнего элемента из стека
\param *stack - указатель на стек из которого мы хотим извлечь элемент
*/
void pop_num(stack_num *stack);
/*!
Функция для удаления стека
\param *stack - указатель на стек который мы хотим удалить
*/
void destroy_num(stack_num *stack);
/*!
Функция для возврата верхнего элемента стека
\param *stack - указатель на стек к которому хотим добавить элемент
\param *flag - флаг наличия данных в стеке
\return Верхний элемент стека
*/
double peek_stack_num(stack_num *stack, int *flag);

#endif  // SRC_BACKEND_STACK_STACK_NUM_H