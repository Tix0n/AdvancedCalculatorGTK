#include "deposit.h"

int leap_year(int year) {
  return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

int how_day_in_pred_month(int mon, int year) {
  int res = 0;
  if (mon == 11 || mon == 9 || mon == 6 || mon == 4) {
    res = 30;
  } else if (mon == 10 || mon == 8 || mon == 7 || mon == 5 || mon == 3 ||
             mon == 1 || mon == 0) {
    res = 31;
  } else if (mon == 2) {
    if (leap_year(year + 1900) == 1) {
      res = 29;
    } else {
      res = 28;
    }
  }
  return res;
}

int add_day_mon_year(struct tm *t_to_add, int frequency, int flag_on,
                     int flag_pay) {
  if (frequency == 1 && flag_pay == 0) {
    flag_on = 0;
  } else {
    if (frequency == 1) {
      if (t_to_add->tm_mon != 11 &&
          t_to_add->tm_mday == how_day_in_pred_month((t_to_add->tm_mon + 1),
                                                     t_to_add->tm_year)) {
        t_to_add->tm_mon += 1;
        t_to_add->tm_mday = 1;
      } else if (t_to_add->tm_mon == 11 &&
                 t_to_add->tm_mday ==
                     how_day_in_pred_month(0, t_to_add->tm_year + 1)) {
        t_to_add->tm_year += 1;
        t_to_add->tm_mon = 0;
        t_to_add->tm_mday = 1;
      }
      t_to_add->tm_mday += 1;
    } else if (frequency == 2) {
      if (t_to_add->tm_mon == 11) {
        t_to_add->tm_year += 1;
        t_to_add->tm_mon = 0;
      } else {
        if (t_to_add->tm_mday == 31 &&
            (t_to_add->tm_mon == 2 || t_to_add->tm_mon == 4 ||
             t_to_add->tm_mon == 6 || t_to_add->tm_mon == 7 ||
             t_to_add->tm_mon == 9)) {
          t_to_add->tm_mday = 30;
          t_to_add->tm_mon += 1;
        } else {
          t_to_add->tm_mon += 1;
        }
      }
    } else if (frequency == 3) {
      if (t_to_add->tm_mon == 1 && t_to_add->tm_mday == 29)
        t_to_add->tm_mday = 28;
      t_to_add->tm_year += 1;
    }
  }
  return flag_on;
}

void need_to_add_or_withdrawal(double *sum_d, struct tm *t_add_or_withdrawal,
                               struct tm t_now, int *flag_on,
                               double sum_add_or_withdrawal,
                               int freq_add_or_withdrawal, int flag_plus_min) {
  int day_in_pred_month = how_day_in_pred_month(t_add_or_withdrawal->tm_mon,
                                                t_add_or_withdrawal->tm_year),
      flag = 0;
  if ((t_add_or_withdrawal->tm_year == t_now.tm_year &&
       t_add_or_withdrawal->tm_mon == t_now.tm_mon &&
       t_add_or_withdrawal->tm_mday - 1 == t_now.tm_mday) ||
      (t_add_or_withdrawal->tm_mday == 1 &&
       t_now.tm_mday == day_in_pred_month &&
       t_now.tm_mon == t_add_or_withdrawal->tm_mon - 1 &&
       t_add_or_withdrawal->tm_year == t_now.tm_year) ||
      (t_add_or_withdrawal->tm_mday == 1 &&
       t_now.tm_mday == day_in_pred_month && t_now.tm_mon == 11 &&
       t_add_or_withdrawal->tm_year == t_now.tm_year + 1))
    flag = 1;
  if (flag == 1 && *flag_on == 1) {
    if (*sum_d + sum_add_or_withdrawal * flag_plus_min > EPS) {
      *sum_d += sum_add_or_withdrawal * flag_plus_min;
    }
    *flag_on = add_day_mon_year(t_add_or_withdrawal, freq_add_or_withdrawal,
                                *flag_on, 0);
  }
}

void checking_lists(struct info_deposit info_d, int *f_on_add_1,
                    int *f_on_add_2, int *f_on_withdr_1, int *f_on_withdr_2) {
  if (info_d.sum_add_1 > EPS) *f_on_add_1 = 1;
  if (info_d.sum_add_2 > EPS) *f_on_add_2 = 1;
  if (info_d.sum_withdr_1 > EPS) *f_on_withdr_1 = 1;
  if (info_d.sum_withdr_2 > EPS) *f_on_withdr_2 = 1;
}

int check_start_date(struct tm t_start) {
  int res = 0;
  if (t_start.tm_year >= 0 && t_start.tm_year <= 10000 && t_start.tm_mon >= 0 &&
      t_start.tm_mon <= 11 && t_start.tm_mday >= 1 && t_start.tm_mday <= 31)
    res = 1;
  return res;
}

void init_t_now_end(struct tm *t_end, struct tm *t_now, struct tm *t_pay,
                    struct tm t_start) {
  t_end->tm_year = t_start.tm_year;
  t_end->tm_mon = t_start.tm_mon;
  t_end->tm_mday = t_start.tm_mday;
  t_now->tm_year = t_start.tm_year;
  t_now->tm_mon = t_start.tm_mon;
  t_now->tm_mday = t_start.tm_mday;
  t_pay->tm_year = t_start.tm_year;
  t_pay->tm_mon = t_start.tm_mon;
  t_pay->tm_mday = t_start.tm_mday;
}

void calc_taxes(struct deposit_res *res, double *incame_past, int flag) {
  if (flag == 0) {
    if ((res->accr_perc - *incame_past - 75000.0) * 0.13 > EPS)
      res->tax_amount += (res->accr_perc - *incame_past - 75000.0) * 0.13;
    *incame_past = res->accr_perc;
  } else if (flag == 1) {
    if ((res->accr_perc - *incame_past - 75000.0) * 0.13 > EPS)
      res->tax_amount += (res->accr_perc - *incame_past - 75000.0) * 0.13;
    if (res->tax_amount < EPS) res->tax_amount = 0.0;
  }
}

void call_func_need_to_add(struct info_deposit *info_d, struct tm t_now,
                           int *f_on_add_1, int *f_on_add_2, int *f_on_withdr_1,
                           int *f_on_withdr_2) {
  need_to_add_or_withdrawal(&info_d->sum_d, &info_d->t_add_1, t_now, f_on_add_1,
                            info_d->sum_add_1, info_d->freq_add_1, 1);
  need_to_add_or_withdrawal(&info_d->sum_d, &info_d->t_add_2, t_now, f_on_add_2,
                            info_d->sum_add_2, info_d->freq_add_2, 1);
  need_to_add_or_withdrawal(&info_d->sum_d, &info_d->t_withdr_1, t_now,
                            f_on_withdr_1, info_d->sum_withdr_1,
                            info_d->freq_withdr_1, -1);
  need_to_add_or_withdrawal(&info_d->sum_d, &info_d->t_withdr_2, t_now,
                            f_on_withdr_2, info_d->sum_withdr_2,
                            info_d->freq_withdr_2, -1);
}

struct deposit_res calculate_deposit(int term, struct info_deposit info_d,
                                     double percent_d, int capit) {
  struct deposit_res res = {0};
  if (info_d.sum_d > EPS && term > 0 && percent_d > EPS) {
    res.accr_perc = 0.0;
    res.tax_amount = 0.0;
    res.amount_by_end_deposit_period = 0.0;
    int flag_on = check_start_date(info_d.t_start);
    if (flag_on == 1) {
      struct tm t_end = {0}, t_now = {0}, t_pay = {0};
      init_t_now_end(&t_end, &t_now, &t_pay, info_d.t_start);
      for (int i = 0; i < term; i++) add_day_mon_year(&t_end, 2, 0, 0);
      add_day_mon_year(&t_pay, info_d.freq_start, 0, 1);
      time_t t_1;
      int f_on_add_1 = 0, f_on_add_2 = 0, f_on_withdr_1 = 0, f_on_withdr_2 = 0;
      checking_lists(info_d, &f_on_add_1, &f_on_add_2, &f_on_withdr_1,
                     &f_on_withdr_2);
      double temp = 0.0, accum_perc = 0.0, incame_past = 0.0000000;
      for (; t_now.tm_year != t_end.tm_year || t_now.tm_mon != t_end.tm_mon ||
             t_now.tm_mday != t_end.tm_mday;) {
        if (capit == 1) {
          if (t_pay.tm_year == t_now.tm_year && t_pay.tm_mon == t_now.tm_mon &&
              t_pay.tm_mday == t_now.tm_mday) {
            info_d.sum_d += accum_perc;
            accum_perc = 0.0;
            add_day_mon_year(&t_pay, info_d.freq_start, 0, 1);
          }
        }
        temp =
            info_d.sum_d * percent_d / 100 / (365 + leap_year(t_now.tm_year));
        res.accr_perc += temp;
        accum_perc += temp;
        call_func_need_to_add(&info_d, t_now, &f_on_add_1, &f_on_add_2,
                              &f_on_withdr_1, &f_on_withdr_2);
        t_1 = mktime(&t_now);
        t_1 += 86400;
        t_now = *localtime(&t_1);
        if (t_now.tm_mday == 1 && t_now.tm_mon == 0)
          calc_taxes(&res, &incame_past, 0);
      }
      res.amount_by_end_deposit_period = info_d.sum_d + capit * accum_perc;
      calc_taxes(&res, &incame_past, 1);
    }
  }
  return res;
}
