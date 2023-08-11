#include "calc.h"

void set_label_credit(GtkSpinButton *button, gpointer data) {
  gtk_widget_map((GtkWidget *)button);  //  need to use button
  struct calc *info_calc = (struct calc *)data;
  gboolean active =
      gtk_toggle_button_get_active((GtkToggleButton *)info_calc->radiobutton1);
  double loan_amount =
      (double)gtk_spin_button_get_value((GtkSpinButton *)info_calc->spin_x_3);
  int term = (int)gtk_spin_button_get_value((GtkSpinButton *)info_calc->spin_x);
  double percent =
      (double)gtk_spin_button_get_value((GtkSpinButton *)info_calc->spin_x_2);
  if (active == TRUE && loan_amount > EPS && term >= 1 && percent > EPS) {
    double monthly = annuity_credit(loan_amount, term, percent);
    char str1[1000] = "x\0";
    char str2[1000] = "\0";
    x_to_string(str1, str2, monthly);
    gtk_label_set_text((GtkLabel *)info_calc->label_1, str2);
    memset(str2, 0, sizeof(str2));
    x_to_string(str1, str2, monthly * term - loan_amount);
    gtk_label_set_text((GtkLabel *)info_calc->label_2, str2);
    memset(str2, 0, sizeof(str2));
    x_to_string(str1, str2, monthly * term);
    gtk_label_set_text((GtkLabel *)info_calc->label_3, str2);
  }
  active =
      gtk_toggle_button_get_active((GtkToggleButton *)info_calc->radiobutton2);
  if (active == TRUE && loan_amount > EPS && term >= 1 && percent > EPS) {
    double sum = 0.0;
    for (int i = 1; i <= term; i++)
      sum += differentiated_credit(loan_amount, term, i, percent);
    char str1[1000] = "x\0";
    char str3[1000] = "\0";
    char str2[1000] = "\0";
    double monthly = differentiated_credit(loan_amount, term, 1, percent);
    x_to_string(str1, str2, monthly);
    strcat(str2, "... x\0");
    monthly = differentiated_credit(loan_amount, term, term, percent);
    x_to_string(str2, str3, monthly);
    gtk_label_set_text((GtkLabel *)info_calc->label_1, str3);
    memset(str2, 0, sizeof(str2));
    x_to_string(str1, str2, sum - loan_amount);
    gtk_label_set_text((GtkLabel *)info_calc->label_2, str2);
    memset(str2, 0, sizeof(str2));
    x_to_string(str1, str2, sum);
    gtk_label_set_text((GtkLabel *)info_calc->label_3, str2);
  }
}

void add_spin_and_radio(GtkWidget *sum_credit_hbox, GtkWidget *term_credit_hbox,
                        GtkWidget *percent_credit_hbox,
                        GtkWidget *credit_mode_switch_hbox,
                        struct calc *info_calc) {
  GtkAdjustment *adjustment0 =
      gtk_adjustment_new(0.0, 0, 100000000, 1000, 0.0, 0.0);
  info_calc->spin_x_3 = gtk_spin_button_new(adjustment0, 1, 1);
  GtkWidget *sum_credit_label = gtk_label_new("Сумма кредита:");
  gtk_box_pack_start(GTK_BOX(sum_credit_hbox), sum_credit_label, FALSE, TRUE,
                     1);
  gtk_box_pack_start(GTK_BOX(sum_credit_hbox), info_calc->spin_x_3, TRUE, TRUE,
                     1);

  info_calc->spin_x = gtk_spin_button_new_with_range(0, 600, 1);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(info_calc->spin_x), 0);
  GtkWidget *term_credit_label = gtk_label_new("Срок кредита(месяцы):");
  gtk_box_pack_start(GTK_BOX(term_credit_hbox), term_credit_label, FALSE, TRUE,
                     1);
  gtk_box_pack_start(GTK_BOX(term_credit_hbox), info_calc->spin_x, TRUE, TRUE,
                     1);

  GtkAdjustment *adjustment2 = gtk_adjustment_new(0.0, 0, 999, 1, 1.0, 0.0);
  info_calc->spin_x_2 = gtk_spin_button_new(adjustment2, 1, 1);
  GtkWidget *percent_credit_label = gtk_label_new("Процентная ставка:");
  gtk_box_pack_start(GTK_BOX(percent_credit_hbox), percent_credit_label, FALSE,
                     TRUE, 1);
  gtk_box_pack_start(GTK_BOX(percent_credit_hbox), info_calc->spin_x_2, TRUE,
                     TRUE, 1);

  info_calc->radiobutton1 = gtk_radio_button_new(NULL);
  info_calc->radiobutton2 = gtk_radio_button_new_from_widget(
      GTK_RADIO_BUTTON(info_calc->radiobutton1));
  GtkWidget *annuity_mode_label = gtk_label_new("аннуитетный");
  GtkWidget *differentiated_mode_label = gtk_label_new("дифференцированный");
  gtk_box_pack_start(GTK_BOX(credit_mode_switch_hbox), annuity_mode_label,
                     FALSE, TRUE, 1);
  gtk_box_pack_start(GTK_BOX(credit_mode_switch_hbox), info_calc->radiobutton1,
                     TRUE, TRUE, 1);
  gtk_box_pack_start(GTK_BOX(credit_mode_switch_hbox),
                     differentiated_mode_label, FALSE, TRUE, 1);
  gtk_box_pack_start(GTK_BOX(credit_mode_switch_hbox), info_calc->radiobutton2,
                     TRUE, TRUE, 1);
}

void add_credit(GtkWidget *vbox, struct calc *info_calc) {
  GtkWidget *sum_credit_hbox, *term_credit_hbox, *percent_credit_hbox,
      *credit_mode_switch_hbox;
  sum_credit_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  term_credit_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  percent_credit_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  credit_mode_switch_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *monthly_pay_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *accrued_percentage_hbox =
      gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *total_payout_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *calculate_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

  add_spin_and_radio(sum_credit_hbox, term_credit_hbox, percent_credit_hbox,
                     credit_mode_switch_hbox, info_calc);

  GtkWidget *monthly_pay_label = gtk_label_new("Ежемесячный платеж:");
  info_calc->label_1 = gtk_label_new("");
  gtk_box_pack_start(GTK_BOX(monthly_pay_hbox), monthly_pay_label, FALSE, TRUE,
                     1);
  gtk_box_pack_start(GTK_BOX(monthly_pay_hbox), info_calc->label_1, FALSE, TRUE,
                     1);

  GtkWidget *accrued_percentage_label = gtk_label_new("Начисленные проценты:");
  info_calc->label_2 = gtk_label_new("");
  gtk_box_pack_start(GTK_BOX(accrued_percentage_hbox), accrued_percentage_label,
                     FALSE, TRUE, 1);
  gtk_box_pack_start(GTK_BOX(accrued_percentage_hbox), info_calc->label_2,
                     FALSE, TRUE, 1);

  GtkWidget *total_payout_label = gtk_label_new("Общая выплата:");
  info_calc->label_3 = gtk_label_new("");
  gtk_box_pack_start(GTK_BOX(total_payout_hbox), total_payout_label, FALSE,
                     TRUE, 1);
  gtk_box_pack_start(GTK_BOX(total_payout_hbox), info_calc->label_3, FALSE,
                     TRUE, 1);

  GtkWidget *button = gtk_button_new_with_label("Рассчитать");
  gtk_box_pack_start(GTK_BOX(calculate_hbox), button, TRUE, TRUE, 1);
  g_signal_connect(button, "clicked", G_CALLBACK(set_label_credit), info_calc);

  gtk_box_pack_start(GTK_BOX(vbox), sum_credit_hbox, TRUE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(vbox), term_credit_hbox, TRUE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(vbox), percent_credit_hbox, TRUE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(vbox), credit_mode_switch_hbox, TRUE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(vbox), monthly_pay_hbox, TRUE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(vbox), accrued_percentage_hbox, TRUE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(vbox), total_payout_hbox, TRUE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(vbox), calculate_hbox, TRUE, TRUE, 3);
}
