#include "calc.h"

void crete_new_wind_ordinary(GtkButton *button, gpointer widget) {
  struct calc *info_calc = (struct calc *)widget;
  gtk_widget_map((GtkWidget *)button);  //  need to use button
  strcpy(info_calc->label_menu[0], "Обычный режим");
  strcpy(info_calc->label_menu[1], "Построение графика");
  strcpy(info_calc->label_menu[2], "Кредитный калькулятор");
  strcpy(info_calc->label_menu[3], "Депозитный калькулятор");
  gtk_widget_hide(info_calc->main_window);
  make_window(1, info_calc);
}

void crete_new_wind_graph(GtkButton *button, gpointer widget) {
  struct calc *info_calc = (struct calc *)widget;
  gtk_widget_map((GtkWidget *)button);  //  need to use button
  strcpy(info_calc->label_menu[1], "Обычный режим");
  strcpy(info_calc->label_menu[0], "Построение графика");
  strcpy(info_calc->label_menu[2], "Кредитный калькулятор");
  strcpy(info_calc->label_menu[3], "Депозитный калькулятор");
  gtk_widget_hide(info_calc->main_window);
  make_window(2, info_calc);
}

void crete_new_wind_credit(GtkButton *button, gpointer widget) {
  struct calc *info_calc = (struct calc *)widget;
  gtk_widget_map((GtkWidget *)button);  //  need to use button
  strcpy(info_calc->label_menu[1], "Обычный режим");
  strcpy(info_calc->label_menu[2], "Построение графика");
  strcpy(info_calc->label_menu[0], "Кредитный калькулятор");
  strcpy(info_calc->label_menu[3], "Депозитный калькулятор");
  gtk_widget_hide(info_calc->main_window);
  make_window(3, info_calc);
}

void crete_new_wind_deposit(GtkButton *button, gpointer widget) {
  struct calc *info_calc = (struct calc *)widget;
  gtk_widget_map((GtkWidget *)button);  //  need to use button
  strcpy(info_calc->label_menu[1], "Обычный режим");
  strcpy(info_calc->label_menu[2], "Построение графика");
  strcpy(info_calc->label_menu[3], "Кредитный калькулятор");
  strcpy(info_calc->label_menu[0], "Депозитный калькулятор");
  gtk_widget_hide(info_calc->main_window);
  make_window(4, info_calc);
}

void add_menu(GtkWidget *vbox, struct calc *info_calc) {
  GtkWidget *menu_bar = gtk_menu_bar_new();
  GtkWidget *menu = gtk_menu_new();
  for (int ind = 0; ind < 4; ind++) {
    GtkWidget *item = gtk_menu_item_new_with_label(info_calc->label_menu[ind]);
    if (ind == 0) {
      gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), item);
      gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), menu);
    } else {
      gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
      if (strcmp(info_calc->label_menu[ind], "Обычный режим") == 0)
        g_signal_connect(GTK_WIDGET(item), "activate",
                         G_CALLBACK(crete_new_wind_ordinary),
                         (gpointer)info_calc);
      if (strcmp(info_calc->label_menu[ind], "Построение графика") == 0)
        g_signal_connect(GTK_WIDGET(item), "activate",
                         G_CALLBACK(crete_new_wind_graph), (gpointer)info_calc);
      if (strcmp(info_calc->label_menu[ind], "Кредитный калькулятор") == 0)
        g_signal_connect(GTK_WIDGET(item), "activate",
                         G_CALLBACK(crete_new_wind_credit),
                         (gpointer)info_calc);
      if (strcmp(info_calc->label_menu[ind], "Депозитный калькулятор") == 0)
        g_signal_connect(GTK_WIDGET(item), "activate",
                         G_CALLBACK(crete_new_wind_deposit),
                         (gpointer)info_calc);
    }
  }
  gtk_container_add(GTK_CONTAINER(vbox), menu_bar);
}