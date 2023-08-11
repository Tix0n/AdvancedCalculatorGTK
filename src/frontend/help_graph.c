#include "calc.h"

void plotting_func(cairo_t *cr, struct calc *info_calc, double zoom_x,
                   double zoom_y) {
  double range =
      (sqrt(pow(info_calc->range_val[0] - info_calc->range_val[1], 2)) +
       sqrt(pow(info_calc->range_val[2] - info_calc->range_val[3], 2))) /
      2;
  int step = calc_step(range);
  double dx = step / 25000.0;
  int flag_prob = 0;
  cairo_save(cr);
  cairo_scale(cr, 1 / zoom_x, -1 / zoom_y);
  cairo_set_line_width(cr, 2);
  cairo_set_source_rgba(cr, 1, 0.2, 0.2, 0.6);
  double start = info_calc->range_val[1], end = info_calc->range_val[0];
  for (double i = start; (end - i + dx) >= EPS; i += dx) {
    double res = func(i, info_calc);
    if (isnan(res) == 1) {
      cairo_stroke(cr);
    } else {
      if (((info_calc->range_val[2] - res + dx) < EPS) ||
          (res - info_calc->range_val[3] + dx) < EPS) {
        flag_prob = 1;
      }
      if (flag_prob == 1 && isinf(res) == 0) {
        cairo_stroke(cr);
        cairo_move_to(cr, i * zoom_x, -res * zoom_y);
        flag_prob = 0;
      }
      if (flag_prob == 0 && isinf(res) == 0)
        cairo_line_to(cr, i * zoom_x, -res * zoom_y);
    }
    i += dx;
  }
  cairo_stroke(cr);
  cairo_restore(cr);
}

double func(double x, struct calc *info_calc) {
  double res = NAN;
  const char *text =
      gtk_entry_get_text(GTK_ENTRY((GtkWidget *)info_calc->entry_str));
  memset(info_calc->string, 0, sizeof(info_calc->string));
  strcat(info_calc->string, (char *)text);
  char with_x[1024] = "\0";
  char polskya[1024] = "\0";
  char out[2000] = "\0";
  int flag = 0;
  x_to_string(info_calc->string, with_x, x);
  int flag_ok = dijkstra(with_x, polskya);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag);
    }
  }
  if (flag_ok != 1 || flag == -1) {
    flag_ok = -1;
    res = NAN;
  }
  if (flag_ok != 1 || flag == -1) {
    sprintf(out, "%s", "ERROR\0");
    gtk_entry_set_text(GTK_ENTRY(info_calc->entry_str), out);
  }
  return res;
}

void found_centre_x(double min, double max, int *centr) {
  if (fabs(min) <= EPS) {
    *centr = 0;
  } else if (fabs(max) <= EPS) {
    *centr = 500;
  } else if ((fabs(fabs(max) - fabs(min))) <=
             EPS * fmax(fabs(max), fabs(min))) {
    *centr = 250;
  } else {
    double step = 500 / sqrt(pow(min - max, 2));
    if (min >= EPS && max >= EPS) {
      *centr = 0 - step * fabs(min);
    } else if (min <= EPS && max <= EPS) {
      *centr = 500 + step * fabs(max);
    } else {
      if (fabs(min) - fabs(max) >= EPS) {
        double middle = (min + max) / 2;
        *centr = 250 + fabs(middle) * step;
      } else {
        double middle = (min + max) / 2;
        *centr = 250 - fabs(middle) * step;
      }
    }
  }
}

void found_centre_y(double min, double max, int *centr) {
  if (fabs(max) <= EPS) {
    *centr = 0;
  } else if (fabs(min) <= EPS) {
    *centr = 500;
  } else if ((fabs(fabs(max) - fabs(min))) <=
             EPS * fmax(fabs(max), fabs(min))) {
    *centr = 250;
  } else {
    double step = (500) / (fabs(min) + fabs(max));
    if (min > EPS && max > EPS) {
      step = 500 / (max - min);
      *centr = 500 + step * fabs(min);
    } else if (min < EPS && max < EPS) {
      step = 500 / (fabs(min) - fabs(max));
      *centr = 0 - step * fabs(max);
    } else {
      if (fabs(min) - fabs(max) >= EPS) {
        double middle = (min + max) / 2;
        *centr = 250 - fabs(middle) * step;
      } else {
        double middle = (min + max) / 2;
        *centr = 250 + fabs(middle) * step;
      }
    }
  }
}

void plotting_axes(cairo_t *cr, double range_val[], double clip_y2,
                   double zoom_x, double zoom_y) {
  cairo_save(cr);
  cairo_scale(cr, 1 / zoom_x, -1 / zoom_y);
  cairo_set_line_width(cr, 1.5);
  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
  if (range_val[2] + 0.5 > EPS && range_val[3] + 0.5 < EPS) {
    cairo_move_to(cr, range_val[1] * zoom_x, 0.0);
    cairo_line_to(cr, range_val[0] * zoom_x, 0.0);
  }

  if (range_val[0] + 0.5 > EPS && range_val[1] + 0.5 < EPS) {
    cairo_move_to(cr, 0.0, -range_val[3] * zoom_y);
    cairo_line_to(cr, 0.0, -clip_y2 * zoom_y);
  }
  cairo_stroke(cr);
  cairo_restore(cr);
}

void plotting_grid(cairo_t *cr, double range_val[], double clip_y2,
                   double zoom_x, double zoom_y) {
  cairo_save(cr);
  cairo_scale(cr, 1 / zoom_x, -1 / zoom_y);
  cairo_set_source_rgb(cr, 0.0, 0.5, 0.0);
  double range = sqrt(pow(range_val[1] - range_val[0], 2));
  int step = calc_step(range);
  step = step;
  cairo_set_line_width(cr, 1);
  double start = ((int)range_val[1] / step +
                  1 * abs((int)range_val[1]) / (int)range_val[1]) *
                 step;
  if (fabs(range_val[1]) < EPS) start = 0.0;
  double end = range_val[0];
  for (double x = start; (end - x + 0.5) >= EPS; x += step) {
    if (fabs(x) > EPS && (int)x % step == 0) {
      cairo_move_to(cr, x * zoom_x, -(clip_y2)*zoom_y);
      cairo_line_to(cr, x * zoom_x, -(range_val[3]) * zoom_y);
    }
  }
  range = sqrt(pow(range_val[3] - range_val[2], 2));
  step = calc_step(range);
  start = ((int)clip_y2 / step + 1 * abs((int)clip_y2) / (int)clip_y2) * step;
  if (fabs(clip_y2) < EPS) start = 0.0;
  end = range_val[3];
  for (double x = start; (x - end + 0.5) >= EPS; x -= step) {
    if (fabs(x) > EPS && (int)x % step == 0) {
      cairo_move_to(cr, range_val[0] * zoom_x, -x * zoom_y);
      cairo_line_to(cr, range_val[1] * zoom_x, -x * zoom_y);
    }
  }
  cairo_stroke(cr);
  cairo_restore(cr);
}

void adding_digits_y(cairo_t *cr, double range_val[], double zoom_x,
                     double zoom_y) {
  cairo_save(cr);
  cairo_scale(cr, 1 / zoom_x, -1 / zoom_y);
  char tmp[100] = "\0";
  double offset_x = 0.1, offset_y = 0.15;
  double range_y = sqrt(pow(range_val[2] - range_val[3], 2));
  int step = calc_step(range_y);
  cairo_set_font_size(cr, 10);
  cairo_set_source_rgb(cr, 0.32, 0.32, 0.32);
  double y = ((int)range_val[3] / step +
              1 * abs((int)range_val[3]) / (int)range_val[3]) *
             step;
  if (fabs(range_val[3]) < EPS) y = 0.0;
  double y_max = round(range_val[2]);
  for (int i = 0; y < y_max + 0.5; i++) {
    if (y + 0.5 > y_max) offset_y += 0.25 * step;
    if (((int)y % step == 0 || y < EPS) && i != 0) {
      itoa((int)y, tmp);
      cairo_move_to(cr, (range_val[0] + offset_x) * zoom_x,
                    (-y + offset_y) * zoom_y);
      cairo_show_text(cr, tmp);
    }
    y = y + step;
  }
  cairo_stroke(cr);
  cairo_restore(cr);
}

void adding_digits_x(cairo_t *cr, double range_val[], double clip_y1,
                     double zoom_x, double zoom_y) {
  cairo_save(cr);
  cairo_scale(cr, 1 / zoom_x, -1 / zoom_y);
  char tmp[100] = "\0";
  double range_x = sqrt(pow(range_val[0] - range_val[1], 2));
  int step = calc_step(range_x);
  cairo_set_font_size(cr, 10);
  cairo_set_source_rgb(cr, 0.32, 0.32, 0.32);
  double x = ((int)range_val[1] / step +
              1 * abs((int)range_val[1]) / (int)range_val[1]) *
             step;
  if (fabs(range_val[1]) < EPS) x = 0.0;
  double x_max = round(range_val[0]);
  for (int i = 0; x < x_max + 0.5; i++) {
    if ((int)x % step == 0 && i != 0) {
      itoa((int)x, tmp);
      cairo_move_to(cr, (x)*zoom_x, -(clip_y1)*zoom_y);
      cairo_show_text(cr, tmp);
    }
    x = x + step;
  }
  cairo_stroke(cr);
  cairo_restore(cr);
}

int calc_step(double range) {
  int step = 1;
  if (range < 10.5) {
    step = 1;
  } else if (range < 20.5) {
    step = 2;
  } else if (range < 25.5) {
    step = 5;
  } else if (range < 50.5) {
    step = 10;
  } else if (range < 100.5) {
    step = 20;
  } else if (range < 250.5) {
    step = 50;
  } else if (range < 500.5) {
    step = 100;
  } else if (range < 1000.5) {
    step = 200;
  } else if (range < 2500.5) {
    step = 500;
  } else if (range < 5000.5) {
    step = 1000;
  } else if (range < 10000.5) {
    step = 2000;
  } else if (range < 40000.5) {
    step = 5000;
  } else if (range < 100000.5) {
    step = 10000;
  } else if (range < 200000.5) {
    step = 20000;
  } else if (range < 1000000.5) {
    step = 100000;
  } else if (range < 1500000.5) {
    step = 150000;
  } else {
    step = 200000;
  }
  return step;
}
