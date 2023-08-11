#include "calc.h"

void make_window(int mode, struct calc *info_calc) {
  GtkWidget *vbox;
  info_calc->main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  g_signal_connect(G_OBJECT(info_calc->main_window), "destroy", gtk_main_quit,
                   NULL);

  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

  add_menu(vbox, info_calc);

  if (mode == 1) {
    gtk_window_set_title(GTK_WINDOW(info_calc->main_window), "Обычный режим");
    gtk_window_set_position(GTK_WINDOW(info_calc->main_window),
                            GTK_WIN_POS_CENTER);
    add_buttons_and_entry(vbox, info_calc);
  } else if (mode == 2) {
    info_calc->d_num = 0;
    gtk_window_set_title(GTK_WINDOW(info_calc->main_window),
                         "Построение графика");
    gtk_window_set_resizable(GTK_WINDOW(info_calc->main_window), FALSE);
    gtk_window_set_position(GTK_WINDOW(info_calc->main_window),
                            GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(info_calc->main_window), WIDTH,
                                HEIGHT);
    gtk_container_set_border_width(GTK_CONTAINER(info_calc->main_window), 10);
    add_graph_and_entry(vbox, info_calc);
  } else if (mode == 3) {
    gtk_window_set_title(GTK_WINDOW(info_calc->main_window),
                         "Кредитный калькулятор");
    gtk_window_set_resizable(GTK_WINDOW(info_calc->main_window), FALSE);
    gtk_window_set_position(GTK_WINDOW(info_calc->main_window),
                            GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(info_calc->main_window), 400, 300);
    add_credit(vbox, info_calc);
  } else if (mode == 4) {
    gtk_window_set_title(GTK_WINDOW(info_calc->main_window),
                         "Депозитный калькулятор");
    gtk_window_set_resizable(GTK_WINDOW(info_calc->main_window), FALSE);
    gtk_window_set_position(GTK_WINDOW(info_calc->main_window),
                            GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(info_calc->main_window), 400, 300);
    add_deposit(vbox, info_calc);
  }
  gtk_container_add(GTK_CONTAINER(info_calc->main_window), vbox);

  gtk_widget_show_all(info_calc->main_window);
}

int main(int argc, char **argv) {
  gtk_init(&argc, &argv);

  struct calc *info_calc;
  info_calc = malloc(sizeof(struct calc));
  info_calc->x = 0.0;

  strcpy(info_calc->label_menu[0], "Обычный режим");
  strcpy(info_calc->label_menu[1], "Построение графика");
  strcpy(info_calc->label_menu[2], "Кредитный калькулятор");
  strcpy(info_calc->label_menu[3], "Депозитный калькулятор");

  make_window(1, info_calc);
  gtk_main();

  free(info_calc);
  return 0;
}
