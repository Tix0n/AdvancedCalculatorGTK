#ifndef SRC_BACKEND_DEPOSIT_H
#define SRC_BACKEND_DEPOSIT_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EPS 1e-7

/*!
  Структура содержащая результат вычислений депозитного калькулятора
*/
struct deposit_res {
  double accr_perc;   ///< начисленные проценты
  double tax_amount;  ///< налог
  double amount_by_end_deposit_period;  ///< сумма на счете к концу срока
};
/*!
  Структура содержащая даты, суммы и переоичности начала, пополнений и частичных
  снятий
*/
struct info_deposit {
  struct tm t_start;  ///< дата начала срока
  int freq_start;  ///< переодичность выплат процентов
  double sum_d;  ///< сумма первоночального депозита

  struct tm t_add_1;  ///< начальаня дата первого дополнительного пополнения(ий)
  int freq_add_1;  ///< переодичность первого пополнения(ий)
  double sum_add_1;  ///< сумма первого пополнения(ий)

  struct tm t_add_2;  ///< начальная дата второго дополнительного пополнения(ий)
  int freq_add_2;  ///< переодичность второго пополнения(ий)
  double sum_add_2;  ///< сумма второго пополнения(ий)

  struct tm t_withdr_1;  ///< начальная дата певого частичного снятия(ий)
  int freq_withdr_1;  ///< переодичность первого снятия(ий)
  double sum_withdr_1;  ///< сумма первого снятия(ий)

  struct tm t_withdr_2;  ///< начальная дата второго частичного снятия(ий)
  int freq_withdr_2;  ///< переодичность первого снятия(ий)
  double sum_withdr_2;  ///< сумма первого снятия(ий)
};

/*!
Функция для расчета депозита
\param term - срок депозита
\param info_d - структура содержащая даты необходимые для рассчетов
\param percent_deposit - процент по депозиту
\param capitalization - флаг капитализации(сложных процентов)
\return Структуру содержащую начисленные проценты, налог и сумма на счете к
концу срока
*/
struct deposit_res calculate_deposit(int term, struct info_deposit info_d,
                                     double percent_deposit,
                                     int capitalization);
/*!
Функция для вызова функций
*/
void call_func_need_to_add(struct info_deposit *info_d, struct tm t_now,
                           int *f_on_add_1, int *f_on_add_2, int *f_on_withdr_1,
                           int *f_on_withdr_2);
/*!
Функция рассчета налога
\param *res - указатель структуру содержащую текущую информацию о депозите
\param *incame_past - ранее накопленные проценты, с которых уже уплачен налог
\param flag - флаг для понимания где считается налог, в процессе депозита или в
последний раз
*/
void calc_taxes(struct deposit_res *res, double *incame_past, int flag);
/*!
Функция для инициализации необходимых дат
\param *t_end - указатель на структуру содержащую дату конца депозита
\param *t_now - указатель на структуру содержащую дату текущего времени
\param *t_pay - указатель на структуру содержащую дату времени платежа процентов
\param t_start - структура содержащая дату начала депозита
*/
void init_t_now_end(struct tm *t_end, struct tm *t_now, struct tm *t_pay,
                    struct tm t_start);
/*!
Функция для определения корректности начальной даты
\param t_start - дата начала депозита
\return 1 если корректна, 0 если нет
*/
int check_start_date(struct tm t_start);
/*!
Функция для проверки наличия сумм для пополнения и частичного снятия
\param info_d - структура содержая суммы для пополнения и частичного снятия
\param *f_on_add_1 - указатель на флаг необходимости первого пополнения
\param *f_on_add_2 - указатель на флаг необходимости второго пополнения
\param *f_on_withdr_1 - указатель на флаг необходимости первого частичного
снятия \param *f_on_withdr_2 - указатель на флаг необходимости второго
частичного снятия
*/
void checking_lists(struct info_deposit info_d, int *f_on_add_1,
                    int *f_on_add_2, int *f_on_withdr_1, int *f_on_withdr_2);
/*!
Функция проверяющая наступления дня пополнения или частичного снятия, которая
увеличивает накопленные проценты и при необходимости двигает даты платежей
дальше \param *sum_d - указатель на сумму депозита которая увеличивается с
пополнениями и уменьшается с частичными снятиями \param *t_add_or_withdrawal -
указатель на структуру содержащую дату пополнения или частичного снятия \param
t_now - структура содержащая текущую дату \param *flag_on - указатель на флаг,
обратится в 0, если пополнение/снятие разовое \param sum_add_or_withdrawal -
сумма для пополнения или частичного снятия \param freq_add_or_withdrawal -
переодичность платежей \param flag_plus_min - флаг говорящий пополнение это или
частичное снятие
*/
void need_to_add_or_withdrawal(double *sum_d, struct tm *t_add_or_withdrawal,
                               struct tm t_now, int *flag_on,
                               double sum_add_or_withdrawal,
                               int freq_add_or_withdrawal, int flag_plus_min);
/*!
Добавит день, месяц или год к теукщей дате в зависимости от аргументов
\param t_to_add - дата к который необходимо прибавить время
\param frequency - параметр по которому определяется прибавляемое время
\param flag_on - флаг для разовых пополнений/снятий
\param flag_pay - флаг указывающий, что работает с датой платежей
\return Значения флага разовых пополнений/снятий
*/
int add_day_mon_year(struct tm *t_to_add, int frequency, int flag_on,
                     int flag_pay);
/*!
Определеят количество дней в прошлом месяце относительно введенного
\param mon - месяц необходииой даты
\param year - год необходимой даты
\return Количесвто дней в предыдущем месяце
*/
int how_day_in_pred_month(int mon, int year);
/*!
Определеят высокосный год или нет
\param year - год который необходимо определить
\return 1 если год высокосный, 0 если нет
*/
int leap_year(int year);

#endif  // SRC_BACKEND_DEPOSIT_H