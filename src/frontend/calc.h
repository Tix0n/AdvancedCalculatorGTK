#ifndef SRC_FRONTEND_CALC_H
#define SRC_FRONTEND_CALC_H
#include <cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../backend/credit.h"
#include "../backend/deposit.h"
#include "../backend/parsing_and_calc.h"

#define WIDTH 560
#define HEIGHT 731

#define ZOOM_X 25.0
#define ZOOM_Y 25.0

#define EPS 1e-7
/*!
  Структура содержащая виджеты и другие данные необходимые всем режимам
  калькулятора
*/
struct calc {
  GtkWidget *entry_str,  ///<  виджет для ввода строки
      *main_window,      ///<  основное окно
      *checkbutton,  ///<  кнопка для влючения режима с 'x'
      *spin_x,       ///<  кнопка для выбора значения 'x'
      *d_area;       ///<  виджет для рисования графика

  char string[1024];  ///<  строка для ввода данных в обычным калькуляторе
  double x;  ///<  переменная хранящая значение x для подстановки
  char label_menu[4][50];  ///<  массив для хранения пуктов меню

  GtkWidget *butt_range_v1,  ///<  максимальное значение x
      *butt_range_v2,        ///<  минимальное значение x
      *butt_range_v3,        ///<  минимальное значение y
      *butt_range_v4;        ///<  максимальное значение y
  int count_range_v;  ///< флаг заполненности массива границ 'x' и 'y'
  int d_num;  ///<  флаг для определения первого и последующих рисований
  double range_val[4];  ///<  массив границ 'x' и 'y'

  GtkWidget
      *label_1,  ///<  для вывода результата в кредитном и депозитном режимах
      *label_2,  ///<  для вывода результата в кредитном и депозитном режимах
      *label_3;  ///<  для вывода результата в кредитном и депозитном режимах
  GtkWidget
      *spin_x_2,  ///< кнопка для процента в кредитном и депозитном режимах
      *spin_x_3;  ///< кнопка для суммы в кредитном и депозитном режимах
  GtkWidget
      *radiobutton1,  ///<  для выбора режима в кредитном и депозитном режимах
      *radiobutton2;  ///<  для выбора режима в кредитном режиме
  GtkWidget
      *periodicity_of_payments_combobox;  ///<  для выбора частоты платежей
  GtkWidget *deposit_combobox_1,  ///<  для выбора частоты первого пополнения
      *deposit_combobox_2;  ///<  для выбора частоты второго пополнения
  GtkWidget *withdrawal_combobox_1,  ///<  для выбора частоты первого снятия
      *withdrawal_combobox_2;  ///<  для выбора частоты второго снятия
  GtkWidget *spin_add_1,  ///<  для выбора суммы первого пополнения
      *spin_add_2;  ///<  для выбора суммы второго пополнения
  GtkWidget *spin_withdrawal_1,  ///<  для выбора суммы первого снятия
      *spin_withdrawal_2;  ///<  для выбора суммы второго снятия
  GtkWidget *calendar_add_1,  ///< кнопка выбора даты первого пополнения
      *calendar_add_2;  ///< кнопка выбора даты второго пополнения
  GtkWidget *calendar_withdrawal_1,  ///< кнопка выбора даты первого снятия
      *calendar_withdrawal_2;  ///< кнопка выбора даты второго снятия

  struct info_deposit
      info_d;  ///< данные о депозите(суммы, переодичности, даты)
};

/*!
Создает основное окно в зависимости от выбранного режима в меню
\param mode - режим
\param *info_calc - необходимая информация
*/
void make_window(int mode, struct calc *info_calc);

//  finance_mode

/*!
Добавляет к 'vbox' окна составляющие кредитный калькулятор
\param *vbox - окно к которуме все присоединяется
\param *info_calc - необходимая информация
*/
void add_credit(GtkWidget *vbox, struct calc *info_calc);
/*!
Вспомогательная функция которая добавляет сумму, срок, ставку и тип платежей
кредита
\param *sum_credit_hbox - виджет для хранение кнопки и подписи суммы
кредита
\param *term_credit_hbox - виджет для хранение кнопки и подписи срока
кредита
\param *percent_credit_hbox - виджет для хранение кнопки и подписи
процентной ставки кредита
\param *credit_mode_switch_hbox - виджет для хранение
кнопки выбора и подписи режимов кредита
\param *info_calc - необходимая
информация
*/
void add_spin_and_radio(GtkWidget *sum_credit_hbox, GtkWidget *term_credit_hbox,
                        GtkWidget *percent_credit_hbox,
                        GtkWidget *credit_mode_switch_hbox,
                        struct calc *info_calc);
/*!
Функция обратного вызова для установки результата после вычислений (срабатывает
при нажатии на кнопку c подписью 'Рассчитать')
\param *button - необходимый
виджет из-за структуры функции обратного вызова
\param data - дополнительная
информация несущая в себе указатель на структуру 'info_calc'
*/
void set_label_credit(GtkSpinButton *button, gpointer data);
/*!
Добавляет к 'vbox' окна составляющие депозитный калькулятор
\param *vbox - окно к которуме все присоединяется
\param *info_calc - необходимая информация
*/
void add_deposit(GtkWidget *vbox, struct calc *info_calc);
/*!
Вспомогательная функция которая создает подписи и создает виджеты для
последующих пополнений и снятий
\param *add_deposit_hbox - виджет для хранение
подписи и виджетов для пополнений
\param *add_withdrawal_hbox - виджет для
хранение подписи и виджетов для снятий
\param *info_calc - необходимая
информация
*/
void add_deposits_and_withdrawal(GtkWidget *add_deposit_hbox,
                                 GtkWidget *add_withdrawal_hbox,
                                 struct calc *info_calc);
/*!
Вспомогательная функция для 'add_deposits_and_withdrawal', которая добавляет
виджеты для установки даты, суммы и частоты пополнений
\param *info_calc -
необходимая информация
\param *deposit_list_vbox - виджеты хранящий установки
даты, суммы и частоты пополнений
*/
void add_deposit_list(struct calc *info_calc, GtkWidget *deposit_list_vbox);
/*!
Вспомогательная функция для 'add_deposits_and_withdrawal', которая добавляет
виджеты для установки даты, суммы и частоты снятий
\param *info_calc -
необходимая информация
\param *deposit_list_vbox - виджеты хранящий установки
даты, суммы и частоты снятий
*/
void add_withdrawal_list(struct calc *info_calc,
                         GtkWidget *withdrawal_list_vbox);
/*!
Функция обратного вызова для установки результата после вычислений (срабатывает
при нажатии на кнопку c подписью 'Рассчитать')
\param *button - необходимый
виджет из-за структуры функции обратного вызова
\param data - дополнительная
информация несущая в себе указатель на структуру 'info_calc'
*/
void set_label_deposit(GtkSpinButton *button, gpointer data);

//  calc_mode

/*!
Добавляет к 'vbox' окна составляющие обычный калькулятор
\param *vbox - окно к которуме все присоединяется
\param *info_calc - необходимая информация
*/
void add_buttons_and_entry(GtkWidget *vbox, struct calc *info_calc);
/*!
Функция обратного вызова для получение значение переменной 'x' (срабатывает при
нажатии на кнопку с подписью '=')
\param *button - необходимый виджет из-за
структуры функции обратного вызова
\param data - дополнительная информация
несущая в себе указатель на структуру 'info_calc'
*/
void take_x(GtkSpinButton *button, gpointer data);
/*!
Функция обратного вызова для установки результата после вычислений (срабатывает
при нажатии на кнопку с подписью '=')
\param *button - необходимый виджет из-за
структуры функции обратного вызова
\param data - дополнительная информация
несущая в себе указатель на структуру 'info_calc'
*/
void butt_of_eq(GtkButton *button, gpointer data);
/*!
Функция обратного вызова для очистки поля ввода (срабатывает при нажатии на
кнопку с подписью 'AC')
\param *button - необходимый виджет из-за структуры
функции обратного вызова
\param data - дополнительная информация несущая в себе
указатель на структуру 'info_calc'
*/
void all_clear(GtkButton *button, gpointer data);
/*!
Функция обратного вызова записи нажатия на кнопки(цифры, мат. фукнциями и т.д.)
и вывода их в виджет для ввода строки (срабатывает при нажатии на кнопки с
цифры, мат. фукнциями и т.д.)
\param *button - необходимый виджет из-за
структуры функции обратного вызова
\param data - дополнительная информация
несущая в себе указатель на структуру 'info_calc'
*/
void print_in_entry(GtkButton *button, gpointer data);

//  menu

/*!
Добавляет к 'vbox' меню с пыпадающим списком
\param *vbox - окно к которуме все присоединяется
\param *info_calc - необходимая информация
*/
void add_menu(GtkWidget *vbox, struct calc *info_calc);
/*!
Функция обратного вызова и ставящая в начало списка 'Обычный режим' и задающий
последовательность для остальных (срабатывает при активации одного из пункта
списка кроме начального)
\param *dummy - необходимый виджет из-за структуры
функции обратного вызова
\param *info_calc - необходимая информация
*/
void crete_new_wind_ordinary(GtkButton *dummy, gpointer widget);
/*!
Функция обратного вызова и ставящая в начало списка 'Построение графика' и
задающий последовательность для остальных (срабатывает при активации одного из
пункта списка кроме начального)
\param *dummy - необходимый виджет из-за
структуры функции обратного вызова
\param *info_calc - необходимая информация
*/
void crete_new_wind_graph(GtkButton *dummy, gpointer widget);
/*!
Функция обратного вызова и ставящая в начало списка 'Кредитный калькулятор' и
задающий последовательность для остальных (срабатывает при активации одного из
пункта списка кроме начального)
\param *dummy - необходимый виджет из-за
структуры функции обратного вызова
\param *info_calc - необходимая информация
*/
void crete_new_wind_credit(GtkButton *button, gpointer widget);
/*!
Функция обратного вызова и ставящая в начало списка 'Депозитный калькулятор' и
задающий последовательность для остальных (срабатывает при активации одного из
пункта списка кроме начального)
\param *dummy - необходимый виджет из-за
структуры функции обратного вызова
\param *info_calc - необходимая информация
*/
void crete_new_wind_deposit(GtkButton *button, gpointer widget);

//  graphic_mode

/*!
Добавляет к 'vbox' окна составляющие построение графика
\param *vbox - окно к которуме все присоединяется
\param *info_calc - необходимая информация
*/
void add_graph_and_entry(GtkWidget *vbox, struct calc *info_calc);
/*!
Функция обратного вызова для получение максимальных и минимальных значений 'x' и
'y' (срабатывает при нажатии на кнопку с подписью 'Нарисовать')
\param *button -
необходимый виджет из-за структуры функции обратного вызова
\param data -
дополнительная информация несущая в себе указатель на структуру 'info_calc'
*/
void take_value(GtkSpinButton *button, gpointer data);
/*!
Функция обратного вызова для перерисовки графика (срабатывает при нажатии на
кнопку с подписью 'Нарисовать')
\param *widget - необходимый виджет из-за
структуры функции обратного вызова
\param data - дополнительная информация
несущая в себе указатель на структуру 'info_calc'
*/
void redrawing(GtkWidget *widget, gpointer data);
/*!
Функция обратного вызова для рисования графика и определяющая происходило ли
раньше рисование(если нет, на экран выведется 'заглушка')
\param *widget -
необходимый виджет для передачи дальше
\param *cr - указатель на контекст
рисования
\param data - дополнительная информация несущая в себе указатель на
структуру 'info_calc'
*/
void drawing(GtkWidget *widget, cairo_t *cr, gpointer data);
/*!
Функция рисования 'заглушки'
\param *widget - необходимый виджет для передачи дальше
\param *cr - указатель на контекст рисования
*/
void draw_empty(GtkWidget *widget, cairo_t *cr);
/*!
Функция рисования графика
\param *widget - виджет содержащий в себе информация о размерах поля рисования
\param *cr - указатель на контекст рисования
\param *info_calc - необходимая информация
*/
void draw_func(GtkWidget *widget, cairo_t *cr, struct calc *info_calc);

//  help_graph

/*!
Функция для построения графки на поле для рисования
\param *cr - указатель на контекст рисования
\param *info_calc - необходимая информация
\param zoom_x - параметр маштаба по оси x
\param zoom_y - параметр маштаба по оси y
*/
void plotting_func(cairo_t *cr, struct calc *info_calc, double zoom_x,
                   double zoom_y);
/*!
Функция для рассчета координаты y по необходимой функции и значению 'x'
\param x - значение 'x'
\param *info_calc - необходимая информация
*/
double func(double x, struct calc *info_calc);
/*!
Функция для поиска центральной точки по оси x на поле рисования
\param min - заданное пользователем минимальное значение 'x'
\param max - заданное пользователем максимальное значение 'x'
\param *centr - указатель на центральную точку
*/
void found_centre_x(double min, double max, int *centr);
/*!
Функция для поиска центральной точки по оси x на поле рисования
\param min - заданное пользователем минимальное значение 'y'
\param max - заданное пользователем максимальное значение 'y'
\param *centr - указатель на центральную точку
*/
void found_centre_y(double min, double max, int *centr);
/*!
Функция для рисования координатных прямых
\param *cr - указатель на контекст рисования
\param range_val[] - массив границ 'x' и 'y'
\param clip_y2 - максимальное значение по 'x' в поле рисования
\param zoom_x - параметр маштаба по оси x
\param zoom_y - параметр маштаба по оси y
*/
void plotting_axes(cairo_t *cr, double range_val[], double clip_y2,
                   double zoom_x, double zoom_y);
/*!
Функция для рисования сетки с адаптивным шагом
\param *cr - указатель на контекст рисования
\param range_val[] - массив границ 'x' и 'y'
\param clip_y2 - минимальное значение по 'y' в поле рисования
\param zoom_x - параметр маштаба по оси x
\param zoom_y - параметр маштаба по оси y
*/
void plotting_grid(cairo_t *cr, double range_val[], double clip_y2,
                   double zoom_x, double zoom_y);
/*!
Функция для добавление подписей значений по оси 'y'
\param *cr - указатель на контекст рисования
\param range_val[] - массив границ 'x' и 'y'
\param zoom_x - параметр маштаба по оси x
\param zoom_y - параметр маштаба по оси y
*/
void adding_digits_y(cairo_t *cr, double range_val[], double zoom_x,
                     double zoom_y);
/*!
Функция для добавление подписей значений по оси 'x'
\param *cr - указатель на контекст рисования
\param range_val[] - массив границ 'x' и 'y'
\param clip_y1 - максимальное значение по 'y' в поле рисования
\param zoom_x - параметр маштаба по оси x
\param zoom_y - параметр маштаба по оси y
*/
void adding_digits_x(cairo_t *cr, double range_val[], double clip_y1,
                     double zoom_x, double zoom_y);
/*!
Функция рассчета шага по длине отрезка
\param range - длина отрезка
*/
int calc_step(double range);

#endif  // SRC_FRONTEND_CALC_H