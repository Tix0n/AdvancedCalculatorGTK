#include "calc.h"

void neutral_earthing_date(struct info_deposit *info_d) {
  info_d->t_start.tm_year = 0;
  info_d->t_start.tm_mon = 0;
  info_d->t_start.tm_mday = 0;
  info_d->sum_d = 0.0;
  info_d->freq_start = 0;

  info_d->t_add_1.tm_year = 0;
  info_d->t_add_1.tm_mon = 0;
  info_d->t_add_1.tm_mday = 0;
  info_d->sum_add_1 = 0.0;
  info_d->freq_add_1 = 0;

  info_d->t_add_2.tm_year = 0;
  info_d->t_add_2.tm_mon = 0;
  info_d->t_add_2.tm_mday = 0;
  info_d->sum_add_2 = 0.0;
  info_d->freq_add_2 = 0;

  info_d->t_withdr_1.tm_mday = 0;
  info_d->t_withdr_1.tm_mon = 0;
  info_d->t_withdr_1.tm_year = 0;
  info_d->sum_withdr_1 = 0.0;
  info_d->freq_withdr_1 = 0;

  info_d->t_withdr_2.tm_mon = 0;
  info_d->t_withdr_2.tm_year = 0;
  info_d->t_withdr_2.tm_mday = 0;
  info_d->sum_withdr_2 = 0.0;
  info_d->freq_withdr_2 = 0;
}

int take_frequency_lists(GtkWidget *data) {
  int frequency = 0;
  if (strcmp(
          (char *)gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(data)),
          "Разовое") == 0) {
    frequency = 1;
  } else if (strcmp((char *)gtk_combo_box_text_get_active_text(
                        GTK_COMBO_BOX_TEXT(data)),
                    "Раз в месяц") == 0) {
    frequency = 2;
  } else if (strcmp((char *)gtk_combo_box_text_get_active_text(
                        GTK_COMBO_BOX_TEXT(data)),
                    "Раз в год") == 0) {
    frequency = 3;
  }
  return frequency;
}
int take_frequency_payments(GtkWidget *data) {
  int frequency = 0;
  if (strcmp(
          (char *)gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(data)),
          "Каждый день") == 0) {
    frequency = 1;
  } else if (strcmp((char *)gtk_combo_box_text_get_active_text(
                        GTK_COMBO_BOX_TEXT(data)),
                    "Раз в месяц") == 0) {
    frequency = 2;
  } else if (strcmp((char *)gtk_combo_box_text_get_active_text(
                        GTK_COMBO_BOX_TEXT(data)),
                    "Раз в год") == 0) {
    frequency = 3;
  } else if (strcmp((char *)gtk_combo_box_text_get_active_text(
                        GTK_COMBO_BOX_TEXT(data)),
                    "В конце срока") == 0) {
    frequency = 4;
  }
  return frequency;
}

void set_label_deposit(GtkSpinButton *button, gpointer data) {
  gtk_widget_map((GtkWidget *)button);  //  need to use button
  struct calc *info_calc = (struct calc *)data;
  int capitalization = 0;
  struct deposit_res result;
  info_calc->info_d.sum_d =
      (double)gtk_spin_button_get_value((GtkSpinButton *)info_calc->spin_x_3);
  int term =
      (double)gtk_spin_button_get_value((GtkSpinButton *)info_calc->spin_x);
  double percent_deposit =
      (double)gtk_spin_button_get_value((GtkSpinButton *)info_calc->spin_x_2);
  info_calc->info_d.freq_start =
      take_frequency_payments(info_calc->periodicity_of_payments_combobox);
  info_calc->info_d.sum_add_1 =
      (double)gtk_spin_button_get_value((GtkSpinButton *)info_calc->spin_add_1);
  info_calc->info_d.sum_add_2 =
      (double)gtk_spin_button_get_value((GtkSpinButton *)info_calc->spin_add_2);
  info_calc->info_d.sum_withdr_1 = (double)gtk_spin_button_get_value(
      (GtkSpinButton *)info_calc->spin_withdrawal_1);
  info_calc->info_d.sum_withdr_2 = (double)gtk_spin_button_get_value(
      (GtkSpinButton *)info_calc->spin_withdrawal_2);
  info_calc->info_d.freq_add_1 =
      take_frequency_lists(info_calc->deposit_combobox_1);
  info_calc->info_d.freq_add_2 =
      take_frequency_lists(info_calc->deposit_combobox_2);
  info_calc->info_d.freq_withdr_1 =
      take_frequency_lists(info_calc->withdrawal_combobox_1);
  info_calc->info_d.freq_withdr_2 =
      take_frequency_lists(info_calc->withdrawal_combobox_2);
  gboolean active =
      gtk_toggle_button_get_active((GtkToggleButton *)info_calc->radiobutton1);
  if (active == TRUE) capitalization = 1;
  result = calculate_deposit(term, info_calc->info_d, percent_deposit,
                             capitalization);
  if (info_calc->info_d.sum_d > EPS && term > 0) {
    char str1[1000] = "x\0";
    char str2[1000] = "\0";
    x_to_string(str1, str2, result.accr_perc);
    gtk_label_set_text((GtkLabel *)info_calc->label_2, str2);
    if (result.tax_amount > EPS) {
      memset(str2, 0, sizeof(str2));
      x_to_string(str1, str2, result.tax_amount);
      gtk_label_set_text((GtkLabel *)info_calc->label_1, str2);
    } else {
      gtk_label_set_text((GtkLabel *)info_calc->label_1, "0.0\0");
    }
    memset(str2, 0, sizeof(str2));
    x_to_string(str1, str2, result.amount_by_end_deposit_period);
    gtk_label_set_text((GtkLabel *)info_calc->label_3, str2);
  }
}

void check_label_and_set_date(GtkWidget *widget, guint year, guint month,
                              guint day, char *tmp, struct calc *info_calc) {
  if (strncmp((char *)gtk_button_get_label((GtkButton *)widget),
              "Выбрать начало\n", 14) == 0) {
    info_calc->info_d.t_start.tm_year = (int)year - 1900;
    info_calc->info_d.t_start.tm_mon = (int)month;
    info_calc->info_d.t_start.tm_mday = (int)day;
    sprintf(tmp, "Выбрать начало\n%04u-%02u-%02u", year, month + 1, day);
    gtk_button_set_label((GtkButton *)widget, tmp);
  } else if (strncmp((char *)gtk_button_get_label((GtkButton *)widget),
                     "Дата первого\nпополнения:\n", 25) == 0) {
    info_calc->info_d.t_add_1.tm_year = (int)year - 1900;
    info_calc->info_d.t_add_1.tm_mon = (int)month;
    info_calc->info_d.t_add_1.tm_mday = (int)day;
    sprintf(tmp, "Дата первого\nпополнения:\n%04u-%02u-%02u", year, month + 1,
            day);
    gtk_button_set_label((GtkButton *)widget, tmp);
  } else if (strncmp((char *)gtk_button_get_label((GtkButton *)widget),
                     "Дата второго\nпополнения:\n", 25) == 0) {
    info_calc->info_d.t_add_2.tm_year = (int)year - 1900;
    info_calc->info_d.t_add_2.tm_mon = (int)month;
    info_calc->info_d.t_add_2.tm_mday = (int)day;
    sprintf(tmp, "Дата второго\nпополнения:\n%04u-%02u-%02u", year, month + 1,
            day);
    gtk_button_set_label((GtkButton *)widget, tmp);
  } else if (strncmp((char *)gtk_button_get_label((GtkButton *)widget),
                     "Дата первого\nснятия:\n", 21) == 0) {
    info_calc->info_d.t_withdr_1.tm_year = (int)year - 1900;
    info_calc->info_d.t_withdr_1.tm_mon = (int)month;
    info_calc->info_d.t_withdr_1.tm_mday = (int)day;
    sprintf(tmp, "Дата первого\nснятия:\n%04u-%02u-%02u", year, month + 1, day);
    gtk_button_set_label((GtkButton *)widget, tmp);
  } else if (strncmp((char *)gtk_button_get_label((GtkButton *)widget),
                     "Дата второго\nснятия:\n", 21) == 0) {
    info_calc->info_d.t_withdr_2.tm_year = (int)year - 1900;
    info_calc->info_d.t_withdr_2.tm_mon = (int)month;
    info_calc->info_d.t_withdr_2.tm_mday = (int)day;
    sprintf(tmp, "Дата второго\nснятия:\n%04u-%02u-%02u", year, month + 1, day);
    gtk_button_set_label((GtkButton *)widget, tmp);
  }
}

void dialog_calendar_effect(GtkWidget *widget, gpointer data) {
  struct calc *info_calc = (struct calc *)data;
  GtkWidget *dialog = gtk_dialog_new_with_buttons(
      "Calendar", GTK_WINDOW(info_calc->main_window),
      GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, "_OK",
      GTK_RESPONSE_ACCEPT, "_Cancel", GTK_RESPONSE_REJECT, NULL);
  GtkWidget *calendar = gtk_calendar_new();
  gtk_container_add(
      GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), calendar);
  gtk_widget_show_all(dialog);
  if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
    GtkCalendar *cal;
    guint year, month, day;
    cal = GTK_CALENDAR(calendar);
    gtk_calendar_get_date(cal, &year, &month, &day);
    char tmp[100] = "\0";
    memset(tmp, 0, sizeof(tmp));
    check_label_and_set_date(widget, year, month, day, tmp, info_calc);
  }
  gtk_widget_destroy(dialog);
}

void add_sum_term_start(GtkWidget *sum_deposit_hbox,
                        GtkWidget *term_deposit_hbox,
                        GtkWidget *start_deposit_date_hbox,
                        struct calc *info_calc) {
  GtkAdjustment *adjustment0 =
      gtk_adjustment_new(0.0, 0, 100000000, 1000, 0.0, 0.0);
  info_calc->spin_x_3 = gtk_spin_button_new(adjustment0, 1, 1);
  GtkWidget *sum_deposit_label = gtk_label_new("Сумма депозита:");
  gtk_box_pack_start(GTK_BOX(sum_deposit_hbox), sum_deposit_label, FALSE, TRUE,
                     3);
  gtk_box_pack_start(GTK_BOX(sum_deposit_hbox), info_calc->spin_x_3, TRUE, TRUE,
                     3);

  info_calc->spin_x = gtk_spin_button_new_with_range(0, 600, 1);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(info_calc->spin_x), 0);
  GtkWidget *term_deposit_label = gtk_label_new("Срок депозита(месяцы):");
  gtk_box_pack_start(GTK_BOX(term_deposit_hbox), term_deposit_label, FALSE,
                     TRUE, 3);
  gtk_box_pack_start(GTK_BOX(term_deposit_hbox), info_calc->spin_x, TRUE, TRUE,
                     3);

  GtkWidget *begin_term_label = gtk_label_new("Начало срока:");
  GtkWidget *begin_term_butt = gtk_button_new_with_label("Выбрать начало");
  gtk_box_pack_start(GTK_BOX(start_deposit_date_hbox), begin_term_label, FALSE,
                     TRUE, 3);
  gtk_box_pack_start(GTK_BOX(start_deposit_date_hbox), begin_term_butt, FALSE,
                     TRUE, 3);
  g_signal_connect(begin_term_butt, "clicked",
                   G_CALLBACK(dialog_calendar_effect), info_calc);
}

void add_percent_periodicity_capitalization(
    GtkWidget *percent_deposit_hbox, GtkWidget *periodicity_of_payments_hbox,
    GtkWidget *capitalization_of_interests_hbox, struct calc *info_calc) {
  GtkAdjustment *adjustment2 = gtk_adjustment_new(0.0, 0, 100, 1, 1.0, 0.0);
  info_calc->spin_x_2 = gtk_spin_button_new(adjustment2, 1, 1);
  GtkWidget *percent_deposit_label = gtk_label_new("Процентная ставка:");
  gtk_box_pack_start(GTK_BOX(percent_deposit_hbox), percent_deposit_label,
                     FALSE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(percent_deposit_hbox), info_calc->spin_x_2, TRUE,
                     TRUE, 3);

  GtkWidget *periodicity_of_payments_label =
      gtk_label_new("Периодичность выплат:");
  info_calc->periodicity_of_payments_combobox = gtk_combo_box_text_new();
  gtk_combo_box_text_append(
      GTK_COMBO_BOX_TEXT(info_calc->periodicity_of_payments_combobox), "0",
      "Каждый день");
  gtk_combo_box_text_append(
      GTK_COMBO_BOX_TEXT(info_calc->periodicity_of_payments_combobox), "1",
      "Раз в месяц");
  gtk_combo_box_text_append(
      GTK_COMBO_BOX_TEXT(info_calc->periodicity_of_payments_combobox), "2",
      "Раз в год");
  gtk_combo_box_text_append(
      GTK_COMBO_BOX_TEXT(info_calc->periodicity_of_payments_combobox), "3",
      "В конце срока");
  gtk_combo_box_set_active(
      GTK_COMBO_BOX(info_calc->periodicity_of_payments_combobox), 1);
  gtk_box_pack_start(GTK_BOX(periodicity_of_payments_hbox),
                     periodicity_of_payments_label, FALSE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(periodicity_of_payments_hbox),
                     info_calc->periodicity_of_payments_combobox, FALSE, TRUE,
                     3);

  GtkWidget *capitalization_of_interests_label =
      gtk_label_new("Капитализация процентов:");
  info_calc->radiobutton1 = gtk_check_button_new();
  gtk_box_pack_start(GTK_BOX(capitalization_of_interests_hbox),
                     capitalization_of_interests_label, FALSE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(capitalization_of_interests_hbox),
                     info_calc->radiobutton1, FALSE, TRUE, 3);
}

void add_accrued_tax_amount_by_end(GtkWidget *accrued_percentage_hbox,
                                   GtkWidget *tax_amount_hbox,
                                   GtkWidget *amount_by_end_deposit_period_hbox,
                                   struct calc *info_calc) {
  GtkWidget *accrued_percentage_label = gtk_label_new("Начисленные проценты:");
  info_calc->label_2 = gtk_label_new("");
  gtk_box_pack_start(GTK_BOX(accrued_percentage_hbox), accrued_percentage_label,
                     FALSE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(accrued_percentage_hbox), info_calc->label_2,
                     FALSE, TRUE, 3);

  GtkWidget *tax_amount_label = gtk_label_new("Сумма налога:");
  info_calc->label_1 = gtk_label_new("");
  gtk_box_pack_start(GTK_BOX(tax_amount_hbox), tax_amount_label, FALSE, TRUE,
                     3);
  gtk_box_pack_start(GTK_BOX(tax_amount_hbox), info_calc->label_1, FALSE, TRUE,
                     3);

  GtkWidget *amount_by_end_deposit_period_label =
      gtk_label_new("Сумма на вкладе к концу срока:");
  info_calc->label_3 = gtk_label_new("");
  gtk_box_pack_start(GTK_BOX(amount_by_end_deposit_period_hbox),
                     amount_by_end_deposit_period_label, FALSE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(amount_by_end_deposit_period_hbox),
                     info_calc->label_3, FALSE, TRUE, 3);
}

void add_deposit(GtkWidget *vbox, struct calc *info_calc) {
  neutral_earthing_date(&info_calc->info_d);
  GtkWidget *sum_deposit_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *term_deposit_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *start_deposit_date_hbox =
      gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *percent_deposit_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *periodicity_of_payments_hbox =
      gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *capitalization_of_interests_hbox =
      gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *add_deposit_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *add_withdrawal_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *accrued_percentage_hbox =
      gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *amount_by_end_deposit_period_hbox =
      gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *tax_amount_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *calculate_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

  add_sum_term_start(sum_deposit_hbox, term_deposit_hbox,
                     start_deposit_date_hbox, info_calc);
  add_percent_periodicity_capitalization(
      percent_deposit_hbox, periodicity_of_payments_hbox,
      capitalization_of_interests_hbox, info_calc);
  add_deposits_and_withdrawal(add_deposit_hbox, add_withdrawal_hbox, info_calc);
  add_accrued_tax_amount_by_end(accrued_percentage_hbox, tax_amount_hbox,
                                amount_by_end_deposit_period_hbox, info_calc);

  GtkWidget *calculate_button = gtk_button_new_with_label("Рассчитать");
  gtk_box_pack_start(GTK_BOX(calculate_hbox), calculate_button, TRUE, TRUE, 3);
  g_signal_connect(calculate_button, "clicked", G_CALLBACK(set_label_deposit),
                   info_calc);

  gtk_box_pack_start(GTK_BOX(vbox), sum_deposit_hbox, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(vbox), term_deposit_hbox, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(vbox), start_deposit_date_hbox, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(vbox), percent_deposit_hbox, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(vbox), periodicity_of_payments_hbox, TRUE, TRUE,
                     5);
  gtk_box_pack_start(GTK_BOX(vbox), capitalization_of_interests_hbox, TRUE,
                     TRUE, 5);
  gtk_box_pack_start(GTK_BOX(vbox), add_deposit_hbox, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(vbox), add_withdrawal_hbox, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(vbox), accrued_percentage_hbox, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(vbox), tax_amount_hbox, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(vbox), amount_by_end_deposit_period_hbox, TRUE,
                     TRUE, 5);
  gtk_box_pack_start(GTK_BOX(vbox), calculate_hbox, TRUE, TRUE, 5);
}

void add_deposits_and_withdrawal(GtkWidget *add_deposit_hbox,
                                 GtkWidget *add_withdrawal_hbox,
                                 struct calc *info_calc) {
  GtkWidget *add_deposit_label = gtk_label_new("Добавить пополнение:");
  GtkWidget *deposits_list_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_start(GTK_BOX(add_deposit_hbox), add_deposit_label, TRUE, TRUE,
                     5);
  gtk_container_add(GTK_CONTAINER(add_deposit_hbox), deposits_list_vbox);

  GtkWidget *add_withdrawal_label = gtk_label_new("Добавить снятие:");
  GtkWidget *withdrawal_list_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_start(GTK_BOX(add_withdrawal_hbox), add_withdrawal_label, TRUE,
                     TRUE, 5);
  gtk_container_add(GTK_CONTAINER(add_withdrawal_hbox), withdrawal_list_vbox);

  add_deposit_list(info_calc, deposits_list_vbox);
  add_withdrawal_list(info_calc, withdrawal_list_vbox);
}

void add_deposit_list(struct calc *info_calc, GtkWidget *deposit_list_vbox) {
  GtkWidget *hbox_1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *hbox_2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  info_calc->deposit_combobox_1 = gtk_combo_box_text_new();
  info_calc->deposit_combobox_2 = gtk_combo_box_text_new();
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(info_calc->deposit_combobox_1),
                            "0", "Разовое");
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(info_calc->deposit_combobox_1),
                            "1", "Раз в месяц");
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(info_calc->deposit_combobox_1),
                            "2", "Раз в год");
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(info_calc->deposit_combobox_2),
                            "0", "Разовое");
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(info_calc->deposit_combobox_2),
                            "1", "Раз в месяц");
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(info_calc->deposit_combobox_2),
                            "2", "Раз в год");
  gtk_combo_box_set_active(GTK_COMBO_BOX(info_calc->deposit_combobox_1), 0);
  gtk_combo_box_set_active(GTK_COMBO_BOX(info_calc->deposit_combobox_2), 0);
  gtk_box_pack_start(GTK_BOX(hbox_1), info_calc->deposit_combobox_1, TRUE, TRUE,
                     3);
  gtk_box_pack_start(GTK_BOX(hbox_2), info_calc->deposit_combobox_2, TRUE, TRUE,
                     3);
  info_calc->calendar_add_1 =
      gtk_button_new_with_label("Дата первого\nпополнения:");
  g_signal_connect(info_calc->calendar_add_1, "clicked",
                   G_CALLBACK(dialog_calendar_effect), info_calc);
  info_calc->calendar_add_2 =
      gtk_button_new_with_label("Дата второго\nпополнения:");
  g_signal_connect(info_calc->calendar_add_2, "clicked",
                   G_CALLBACK(dialog_calendar_effect), info_calc);
  gtk_box_pack_start(GTK_BOX(hbox_1), info_calc->calendar_add_1, TRUE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(hbox_2), info_calc->calendar_add_2, TRUE, TRUE, 3);
  GtkAdjustment *adjustment_1 =
      gtk_adjustment_new(0.0, 0, 100000000, 100, 0.0, 0.0);
  info_calc->spin_add_1 = gtk_spin_button_new(adjustment_1, 1, 1);
  GtkAdjustment *adjustment_2 =
      gtk_adjustment_new(0.0, 0, 100000000, 100, 0.0, 0.0);
  info_calc->spin_add_2 = gtk_spin_button_new(adjustment_2, 1, 1);
  gtk_box_pack_start(GTK_BOX(hbox_1), info_calc->spin_add_1, TRUE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(hbox_2), info_calc->spin_add_2, TRUE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(deposit_list_vbox), hbox_1, TRUE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(deposit_list_vbox), hbox_2, TRUE, TRUE, 3);
}

void add_withdrawal_list(struct calc *info_calc,
                         GtkWidget *withdrawal_list_vbox) {
  GtkWidget *hbox_3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *hbox_4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  info_calc->withdrawal_combobox_1 = gtk_combo_box_text_new();
  info_calc->withdrawal_combobox_2 = gtk_combo_box_text_new();
  gtk_combo_box_text_append(
      GTK_COMBO_BOX_TEXT(info_calc->withdrawal_combobox_1), "0", "Разовое");
  gtk_combo_box_text_append(
      GTK_COMBO_BOX_TEXT(info_calc->withdrawal_combobox_1), "1", "Раз в месяц");
  gtk_combo_box_text_append(
      GTK_COMBO_BOX_TEXT(info_calc->withdrawal_combobox_1), "2", "Раз в год");
  gtk_combo_box_text_append(
      GTK_COMBO_BOX_TEXT(info_calc->withdrawal_combobox_2), "0", "Разовое");
  gtk_combo_box_text_append(
      GTK_COMBO_BOX_TEXT(info_calc->withdrawal_combobox_2), "1", "Раз в месяц");
  gtk_combo_box_text_append(
      GTK_COMBO_BOX_TEXT(info_calc->withdrawal_combobox_2), "2", "Раз в год");
  gtk_combo_box_set_active(GTK_COMBO_BOX(info_calc->withdrawal_combobox_1), 0);
  gtk_combo_box_set_active(GTK_COMBO_BOX(info_calc->withdrawal_combobox_2), 0);
  gtk_box_pack_start(GTK_BOX(hbox_3), info_calc->withdrawal_combobox_1, TRUE,
                     TRUE, 3);
  gtk_box_pack_start(GTK_BOX(hbox_4), info_calc->withdrawal_combobox_2, TRUE,
                     TRUE, 3);
  info_calc->calendar_withdrawal_1 =
      gtk_button_new_with_label("Дата первого\nснятия:");
  g_signal_connect(info_calc->calendar_withdrawal_1, "clicked",
                   G_CALLBACK(dialog_calendar_effect), info_calc);
  info_calc->calendar_withdrawal_2 =
      gtk_button_new_with_label("Дата второго\nснятия:");
  g_signal_connect(info_calc->calendar_withdrawal_2, "clicked",
                   G_CALLBACK(dialog_calendar_effect), info_calc);
  gtk_box_pack_start(GTK_BOX(hbox_3), info_calc->calendar_withdrawal_1, TRUE,
                     TRUE, 3);
  gtk_box_pack_start(GTK_BOX(hbox_4), info_calc->calendar_withdrawal_2, TRUE,
                     TRUE, 3);
  GtkAdjustment *adjustment_4 =
      gtk_adjustment_new(0.0, 0, 100000000, 100, 0.0, 0.0);
  info_calc->spin_withdrawal_1 = gtk_spin_button_new(adjustment_4, 1, 1);
  GtkAdjustment *adjustment_5 =
      gtk_adjustment_new(0.0, 0, 100000000, 100, 0.0, 0.0);
  info_calc->spin_withdrawal_2 = gtk_spin_button_new(adjustment_5, 1, 1);
  gtk_box_pack_start(GTK_BOX(hbox_3), info_calc->spin_withdrawal_1, TRUE, TRUE,
                     3);
  gtk_box_pack_start(GTK_BOX(hbox_4), info_calc->spin_withdrawal_2, TRUE, TRUE,
                     3);
  gtk_box_pack_start(GTK_BOX(withdrawal_list_vbox), hbox_3, TRUE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(withdrawal_list_vbox), hbox_4, TRUE, TRUE, 3);
}