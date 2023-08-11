#include "calc.h"

void print_in_entry(GtkButton *button, gpointer data) {
  struct calc *info_calc = (struct calc *)data;

  if (gtk_entry_get_text(GTK_ENTRY((GtkWidget *)info_calc->entry_str)) !=
      NULL) {
    const char *text_prev =
        gtk_entry_get_text(GTK_ENTRY((GtkWidget *)info_calc->entry_str));
    memset(info_calc->string, 0, sizeof(info_calc->string));
    strcat(info_calc->string, text_prev);
  }
  strcat(info_calc->string, gtk_button_get_label(button));
  if (strcmp(gtk_button_get_label(button), "sqrt") == 0 ||
      strcmp(gtk_button_get_label(button), "cos") == 0 ||
      strcmp(gtk_button_get_label(button), "acos") == 0 ||
      strcmp(gtk_button_get_label(button), "sin") == 0 ||
      strcmp(gtk_button_get_label(button), "asin") == 0 ||
      strcmp(gtk_button_get_label(button), "tan") == 0 ||
      strcmp(gtk_button_get_label(button), "atan") == 0 ||
      strcmp(gtk_button_get_label(button), "log") == 0 ||
      strcmp(gtk_button_get_label(button), "ln") == 0) {
    strcat(info_calc->string, "(\0");
  }
  gtk_entry_set_text(GTK_ENTRY((GtkWidget *)info_calc->entry_str),
                     info_calc->string);
}

void all_clear(GtkButton *button, gpointer data) {
  struct calc *info_calc = (struct calc *)data;

  gtk_widget_map((GtkWidget *)button);  //  need to use button
  memset(info_calc->string, 0, sizeof(info_calc->string));
  gtk_entry_set_text(GTK_ENTRY(info_calc->entry_str), info_calc->string);
}

void butt_of_eq(GtkButton *button, gpointer data) {
  struct calc *info_calc = (struct calc *)data;

  int flag_ok = -1;
  if (gtk_button_get_label(button) != 0) {  //  button need to use
  }
  const char *button_text =
      gtk_entry_get_text(GTK_ENTRY((GtkWidget *)info_calc->entry_str));
  memset(info_calc->string, 0, sizeof(info_calc->string));
  strcat(info_calc->string, (char *)button_text);
  char polskya[1024] = "\0";
  memset(polskya, 0, sizeof(polskya));
  char out[2000] = "\0";
  char entry_str1[2000] = "\0";
  gboolean active =
      gtk_toggle_button_get_active((GtkToggleButton *)info_calc->checkbutton);
  int flag = 0;
  if (active == TRUE) {
    x_to_string(info_calc->string, entry_str1, info_calc->x);
    flag_ok = dijkstra(entry_str1, polskya);
  } else {
    flag_ok = dijkstra(info_calc->string, polskya);
  }
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    if (flag_ok == 1) {
      double res = calculate(polskya, &flag);
      if (flag == 0) {
        sprintf(out, "%.7f", res);
        gtk_entry_set_text(GTK_ENTRY(info_calc->entry_str), out);
        strcat(info_calc->string, out);
      }
    }
  }
  if (flag_ok != 1 || flag == -1) {
    flag_ok = -1;
  }
  if (flag_ok != 1 || flag == -1) {
    sprintf(out, "%s", "ERROR\0");
    gtk_entry_set_text(GTK_ENTRY(info_calc->entry_str), out);
  }
}

void take_x(GtkSpinButton *button, gpointer data) {
  struct calc *info_calc = (struct calc *)data;
  gtk_widget_map((GtkWidget *)button);  //  need to use button
  gdouble val =
      (gdouble)gtk_spin_button_get_value((GtkSpinButton *)info_calc->spin_x);
  info_calc->x = (double)val;
}

void add_buttons_and_entry(GtkWidget *vbox, struct calc *info_calc) {
  info_calc->checkbutton = gtk_check_button_new();
  GtkAdjustment *adjustment1 =
      gtk_adjustment_new(0.0, -1000000.0, 1000000.0, 1, 0.0, 0.0);
  info_calc->spin_x = gtk_spin_button_new(adjustment1, 0.1, 7);
  info_calc->entry_str = gtk_entry_new();
  GtkWidget *hbox0, *hbox01, *hbox02;
  GtkWidget *label = gtk_label_new("x=\0");
  hbox0 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
  hbox01 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  hbox02 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

  gtk_box_pack_start(GTK_BOX(hbox01), info_calc->entry_str, TRUE, TRUE, 1);

  gtk_box_pack_start(GTK_BOX(hbox02), label, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox02), info_calc->spin_x, TRUE, TRUE, 1);
  gtk_box_pack_start(GTK_BOX(hbox02), info_calc->checkbutton, TRUE, TRUE, 1);

  gtk_box_pack_start(GTK_BOX(hbox0), hbox01, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox0), hbox02, TRUE, TRUE, 0);

  gtk_box_pack_start(GTK_BOX(vbox), hbox0, FALSE, FALSE, 5);
  char *label_buttons_ordinary[] = {
      "mod", "=",    "0", ".",    "cos", "acos", "/",   "3",    "2", "1",
      "sin", "asin", "+", "6",    "5",   "4",    "tan", "atan", "-", "9",
      "8",   "7",    "^", "sqrt", "*",   "AC",   "log", "ln",   ")", "("};
  for (int ind = 29; ind >= 0; ind--) {
    GtkWidget *button = gtk_button_new_with_label(label_buttons_ordinary[ind]);
    gtk_widget_set_size_request(button, 75, 25);
    GtkWidget *hbox;
    if (ind == 29 || (ind + 1) % 6 == 0) {
      hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
      gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 1);
    } else {
      gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 1);
    }
    if (ind == 1) {
      g_signal_connect(button, "clicked", G_CALLBACK(take_x), info_calc);
      g_signal_connect(button, "clicked", G_CALLBACK(butt_of_eq), info_calc);
    } else if (ind == 25) {
      g_signal_connect(button, "clicked", G_CALLBACK(all_clear), info_calc);
    } else {
      g_signal_connect(button, "clicked", G_CALLBACK(print_in_entry),
                       info_calc);
    }
    if (ind != 0 && (ind + 1) % 6 == 0)
      gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 1);
  }
}
