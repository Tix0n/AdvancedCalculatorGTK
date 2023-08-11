#ifndef SRC_BACKEND_PARSING_AND_CALC_H
#define SRC_BACKEND_PARSING_AND_CALC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./stack/stack_num.h"
#include "./stack/stack_sym.h"

#define EPS 1e-7
#define ERROR -1

/*!
Функция преобразующая инфиксную запись в постфиксную
\param *string - входная строка для преобразования
\param output_string - выходная строка
\return Код ошибки
*/
int dijkstra(char *string, char *output_string);
/*!
Вспомогательная функция для функции 'dijkstra', переносит число из первой строки
во вторую и ставит пробел \param *string - входная строка для преобразования
\param output_string - выходная строка
\param *count - счетчик для выходной строки
\param *i - счетчик для входной строки
\param *res - флаг ошибки
*/
void proc_numbers(char *string, char *output_string, int *count, int *i,
                  int *res);
/*!
Вспомогательная функция для функции 'dijkstra', обрабатывающая математические
функции, проверяет корректность их ввода \param *string - входная строка для
преобразования \param *i - счетчик для входной строки \param *res - флаг ошибки
*/
void proc_trig(stack_sym *head, char *string, int *i, int *res);
/*!
Вспомогательная функция для функции 'dijkstra', обрабатывающая функцию 'mod'
\param *string - входная строка для преобразования
\param *i - счетчик для входной строки
\param *res - флаг ошибки
*/
void if_mod(char *string, int *i, int *res);
/*!
Вспомогательная функция проверяющая корректность функции 'mod'
\param *string - входная строка для преобразования
\param *i - счетчик для входной строки
\param *res - флаг ошибки
*/
int check_mod(char *string, char *sym_trig, int i);
/*!
Функция вычисляющая выражение в польской нотации
\param *string - входная строка для преобразования
\param *flag - флаг ошибки
\return Вычисленное число типа 'double'
*/
double calculate(char *string, int *flag);
/*!
Функция переводящая строку в число типа 'double'
\param *str - входная строка для преобразования
\param flag_double - флаг говорящий о типе числа полученного ранее(целочисленное
или дробное) \return Число типа 'double'
*/
double str_to_double(char *str, int flag_double);
/*!
Вспомогательная функция опреляющая символ и его приоритет
\param symbol - символ который нужно определить
\return Приоритет или другую информацию о символе
*/
int what_is_it(char symbol);
/*!
Вспомогательная функция обрабатывающая математические функции
\param *string - входная строка
\param *sym_trig - символ для возврата
\param i - позиция начала математичской функции
\return Флаг ошибки
*/
int check_post_func(char *string, char *sym_trig, int i);
/*!
Вспомогательная функция обрабатывающая короткие математические функции(3
символа) \param *string - входная строка \param *sym_trig - символ для возврата
\param i - позиция начала математичской функции
\param count - длина оставшейся(от начала математические функции) до конца
входной строки \return Флаг ошибки
*/
int check_short_trig(char *string, char *sym_trig, int i, int count);
/*!
Вспомогательная функция обрабатывающая длинные математические функции(более 3
символов) \param *string - входная строка \param *sym_trig - символ для возврата
\param i - позиция начала математичской функции
\param count - длина оставшейся(от начала математические функции) до конца
входной строки \return Флаг ошибки
*/
int check_long_trig(char *string, char *sym_trig, int i, int count);
/*!
Вспомогательная функция производящая вычисления в зависимости от поданного
оператора \param num_1 - первое число для вычислений \param num_1 - второе число
для вычислений \return Результат вычисления
*/
double operation(double num_1, double num_2, char oper);
/*!
Функция проверяющая польскую нотация на корректность(соотвествия чисел и
операторов и т.п.) \param *string - входная строка \return Код ошибки
*/
int is_correct(char *string);
/*!
Функция заменяющая символы 'x' в поданное число типа 'double'
\param *string - входная строка
\param *str_2 - выходная строка
\param x - число которое станет заменой символов 'x'
*/
void x_to_string(char *string, char *str_2, double x);
/*!
Функция возвращает запись указанного целого числа
\param n - число для преобразования
\param *s - строка для записи
*/
void itoa(int n, char *s);
/*!
Функция переворачивает строку
\param *s - строка преобразования
*/
void reverse(char *s);

#endif  // SRC_BACKEND_PARSING_AND_CALC_H