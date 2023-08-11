#include "calc.h"

void add_graph_and_entry(GtkWidget *vbox, struct calc *info_calc) {
  info_calc->count_range_v = 0;
  info_calc->d_area = gtk_drawing_area_new();
  info_calc->entry_str = gtk_entry_new();
  GtkWidget *hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *button_draw = gtk_button_new_with_label("Нарисовать");
  gtk_box_pack_start(GTK_BOX(hbox1), info_calc->entry_str, TRUE, TRUE, 1);
  gtk_box_pack_start(GTK_BOX(hbox1), button_draw, TRUE, TRUE, 1);
  info_calc->butt_range_v1 =
      gtk_spin_button_new_with_range(-1000000, 1000000, 5);
  info_calc->butt_range_v2 =
      gtk_spin_button_new_with_range(-1000000, 1000000, 5);
  info_calc->butt_range_v3 =
      gtk_spin_button_new_with_range(-1000000, 1000000, 5);
  info_calc->butt_range_v4 =
      gtk_spin_button_new_with_range(-1000000, 1000000, 5);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(info_calc->butt_range_v1), 10);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(info_calc->butt_range_v2), -10);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(info_calc->butt_range_v3), 10);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(info_calc->butt_range_v4), -10);
  GtkWidget *label1 = gtk_label_new("max x");
  GtkWidget *label2 = gtk_label_new("min x");
  GtkWidget *label3 = gtk_label_new("max y");
  GtkWidget *label4 = gtk_label_new("min y");
  gtk_container_add(GTK_CONTAINER(hbox2), label2);
  gtk_container_add(GTK_CONTAINER(hbox2), info_calc->butt_range_v2);
  gtk_container_add(GTK_CONTAINER(hbox2), label1);
  gtk_container_add(GTK_CONTAINER(hbox2), info_calc->butt_range_v1);
  gtk_container_add(GTK_CONTAINER(hbox3), label4);
  gtk_container_add(GTK_CONTAINER(hbox3), info_calc->butt_range_v4);
  gtk_container_add(GTK_CONTAINER(hbox3), label3);
  gtk_container_add(GTK_CONTAINER(hbox3), info_calc->butt_range_v3);
  gtk_box_pack_start(GTK_BOX(vbox), info_calc->d_area, TRUE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(vbox), hbox1, FALSE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(vbox), hbox2, FALSE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(vbox), hbox3, FALSE, TRUE, 3);
  g_signal_connect(G_OBJECT(button_draw), "clicked", G_CALLBACK(take_value),
                   info_calc);
  g_signal_connect(G_OBJECT(button_draw), "clicked", G_CALLBACK(take_value),
                   info_calc);
  g_signal_connect(G_OBJECT(button_draw), "clicked", G_CALLBACK(take_value),
                   info_calc);
  g_signal_connect(G_OBJECT(button_draw), "clicked", G_CALLBACK(take_value),
                   info_calc);
  g_signal_connect(G_OBJECT(button_draw), "clicked", G_CALLBACK(redrawing),
                   info_calc);
  g_signal_connect(G_OBJECT(info_calc->d_area), "draw", G_CALLBACK(drawing),
                   info_calc);
}

void take_value(GtkSpinButton *button, gpointer data) {
  gtk_widget_map((GtkWidget *)button);  //  need to use button
  struct calc *info_calc = (struct calc *)data;
  gdouble val = 0.0;
  if (info_calc->count_range_v == 0) {
    val = (gdouble)gtk_spin_button_get_value(
        (GtkSpinButton *)info_calc->butt_range_v1);
  } else if (info_calc->count_range_v == 1) {
    val = (gdouble)gtk_spin_button_get_value(
        (GtkSpinButton *)info_calc->butt_range_v2);
  } else if (info_calc->count_range_v == 2) {
    val = (gdouble)gtk_spin_button_get_value(
        (GtkSpinButton *)info_calc->butt_range_v3);
  } else if (info_calc->count_range_v == 3) {
    val = (gdouble)gtk_spin_button_get_value(
        (GtkSpinButton *)info_calc->butt_range_v4);
  }
  info_calc->range_val[info_calc->count_range_v] = (double)val;
  info_calc->count_range_v++;
  if (info_calc->count_range_v >= 4) info_calc->count_range_v = 0;
}

void drawing(GtkWidget *widget, cairo_t *cr, gpointer data) {
  struct calc *info_calc = (struct calc *)data;
  if (info_calc->d_num == 0) {
    draw_empty(widget, cr);
  } else {
    draw_func(widget, cr, info_calc);
  }
}

void redrawing(GtkWidget *widget, gpointer data) {
  gtk_widget_map(widget);  //  need to use widget
  struct calc *info_calc = (struct calc *)data;
  info_calc->d_num++;
  gtk_widget_queue_draw((GtkWidget *)info_calc->d_area);
}

void draw_empty(GtkWidget *widget, cairo_t *cr) {
  GdkRectangle da;
  GdkWindow *window = gtk_widget_get_window(widget);
  gdk_window_get_geometry(window, &da.x, &da.y, &da.width, &da.height);
  cairo_translate(cr, da.width / 2, da.height / 2);
  cairo_scale(cr, ZOOM_X, -ZOOM_Y);
  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
  cairo_set_line_width(cr, 0.02);
  cairo_move_to(cr, -100.0, 0.0);
  cairo_line_to(cr, 100.0, 0.0);
  cairo_move_to(cr, 0.0, -100.0);
  cairo_line_to(cr, 0.0, 100.0);
  cairo_stroke(cr);
}

void draw_func(GtkWidget *widget, cairo_t *cr, struct calc *info_calc) {
  if (info_calc->range_val[0] - info_calc->range_val[1] > EPS &&
      info_calc->range_val[2] - info_calc->range_val[3] > EPS) {
    double zoom_x = 25.0, zoom_y = 25.0;
    int centre_x = 0, centre_y = 0;
    GdkRectangle da;
    gdouble clip_x1 = 0.0, clip_y1 = 0.0, clip_x2 = 0.0, clip_y2 = 0.0,
            dy = 2.0, dx = 2.0;
    GdkWindow *window = gtk_widget_get_window(widget);
    gdk_window_get_geometry(window, &da.x, &da.y, &da.width, &da.height);

    zoom_x /=
        sqrt(pow(info_calc->range_val[0] - info_calc->range_val[1], 2)) / 20.0;
    zoom_y /=
        sqrt(pow(info_calc->range_val[2] - info_calc->range_val[3], 2)) / 20.0;

    found_centre_x(info_calc->range_val[1], info_calc->range_val[0], &centre_x);
    found_centre_y(info_calc->range_val[3], info_calc->range_val[2], &centre_y);

    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_set_line_width(cr, 2);
    cairo_rectangle(cr, 0, 0, 500, 500);

    cairo_stroke(cr);

    cairo_translate(cr, centre_x, centre_y);
    cairo_scale(cr, zoom_x, -zoom_y);

    cairo_device_to_user_distance(cr, &dx, &dy);
    cairo_clip_extents(cr, &clip_x1, &clip_y1, &clip_x2, &clip_y2);

    plotting_grid(cr, info_calc->range_val, clip_y2, zoom_x, zoom_y);
    plotting_axes(cr, info_calc->range_val, clip_y2, zoom_x, zoom_y);
    adding_digits_y(cr, info_calc->range_val, zoom_x, zoom_y);
    adding_digits_x(cr, info_calc->range_val, clip_y1, zoom_x, zoom_y);
    plotting_func(cr, info_calc, zoom_x, zoom_y);
  }
}
