#ifndef SRC_BACKEND_CREDIT_H
#define SRC_BACKEND_CREDIT_H

#include <math.h>

/*!
Находит аннуитетный ежемесячный платеж
\param loan_amout - сумма займа
\param term - срок займа
\param percent - процент
\return Аннуитетный ежемесячный платеж
*/
double annuity_credit(double loan_amount, int term, double percent);
/*!
Находит дифференцированный ежемесячный платеж по указанному месяцу
\param loan_amout - сумма займа
\param term - срок займа
\param term_found - искомый месяц
\param percent - процент
\return Дифференцированный платеж за указнный месяц
*/
double differentiated_credit(double loan_amount, int term, int term_found,
                             double percent);

#endif  // SRC_BACKEND_CREDIT_H