#include <check.h>

#include "../backend/credit.h"
#include "../backend/deposit.h"
#include "../backend/parsing_and_calc.h"
#define EPS 1e-7
#include <check.h>
#include <stdio.h>
#define EPS_1 1e-1
#define EPS_0 1e-0

void calc_testing(SRunner **sr);

START_TEST(calc_no_x_1) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "1+3\0";

  double res = 0.0, expected = 4.0;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  // printf("str=%s\n", polskya);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 1);
}
END_TEST

START_TEST(calc_no_x_2) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "1*5*9\0";

  double res = 0.0, expected = 45.0;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 1);
}
END_TEST

START_TEST(calc_no_x_3) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "cos(5+9*3)-21.2\0";

  double res = 0.0, expected = -20.3657766;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 1);
}
END_TEST

START_TEST(calc_no_x_4) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "cos(5-9/3) mod 21.2\0";

  double res = 0.0, expected = -0.4161468;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 1);
}
END_TEST

START_TEST(calc_no_x_5) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "sqrt(5.1^9,5*ln(4)) - log(21.2)\0";

  double res = 0.0, expected = 1778.4147980;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK_D=%d!!!!!!!!!!\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d!!!!!!!!!!\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      // printf("res=%f\n", res);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 1);
}
END_TEST

START_TEST(calc_no_x_6) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "acos(5)^asin(3)-4+atan(~2.1)\0";

  double res = 0.0, expected = NAN;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (isnanf(res)) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 1);
}
END_TEST

START_TEST(calc_no_x_7) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "acos(5)^asin(3)-4+atan(-2.1)\0";  //  err

  double res = 0.0, expected = 1778.4147980;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 0);
}
END_TEST

START_TEST(calc_no_x_8) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "-25\0";  //  err

  double res = 0.0, expected = 1778.4147980;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 0);
}
END_TEST

START_TEST(calc_no_x_9) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "`25\0";

  double res = 0.0, expected = 25.0000000;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 1);
}
END_TEST

START_TEST(calc_no_x_10) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "tan(2.1) + atan(2)\0";

  double res = 0.0, expected = -0.6026978;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 1);
}
END_TEST

START_TEST(calc_no_x_11) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "t(2.1) + atan(2)\0";  //  err

  double res = 0.0, expected = -0.6026978;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 0);
}
END_TEST

START_TEST(calc_no_x_12) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "sin(2.1)^atan(2.1)\0";

  double res = 0.0, expected = 0.8473107;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 1);
}
END_TEST

START_TEST(calc_no_x_13) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "sin(2.1)moa\0";  //  err

  double res = 0.0, expected = 0.8473107;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 0);
}
END_TEST

START_TEST(calc_no_x_14) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "sin)2.1\0";  //  err

  double res = 0.0, expected = 0.8473107;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 0);
}
END_TEST

START_TEST(calc_no_x_15) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "1+++2.1\0";  //  err

  double res = 0.0, expected = 0.8473107;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 0);
}
END_TEST

START_TEST(calc_no_x_16) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "1+2.1+\0";  //  err

  double res = 0.0, expected = 0.8473107;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 0);
}
END_TEST

START_TEST(calc_no_x_17) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "1+2.1~\0";  //  err

  double res = 0.0, expected = -1.1000000;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK1=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK2=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      // printf("flag_calc=%d\n", flag_calc);
      // printf("res-exp=%f\n", fabs(res - expected));
      // printf("res=%f\n", res);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  // printf("FLAG=%d\n", flag);
  ck_assert_uint_eq(flag, 0);
}
END_TEST

START_TEST(calc_no_x_18) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "fas\0";  //  err

  double res = 0.0, expected = 0.8473107;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 0);
}
END_TEST

START_TEST(calc_no_x_19) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "\0";  //  err

  double res = 0.0, expected = 0.8473107;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 0);
}
END_TEST

START_TEST(calc_no_x_20) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = ".1+23\0";  //  err

  double res = 0.0, expected = 0.8473107;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 0);
}
END_TEST

START_TEST(calc_no_x_21) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "2.1 cos()\0";  //  err

  double res = 0.0, expected = 0.0000000;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  // printf("%.7f\n", res);
  ck_assert_uint_eq(flag, 0);
}
END_TEST

START_TEST(calc_no_x_22) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "cos((\0";  //  err

  double res = 0.0, expected = 0.8473107;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 0);
}
END_TEST

START_TEST(calc_no_x_23) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "cos(()\0";  //  err

  double res = 0.0, expected = 0.8473107;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 0);
}
END_TEST

START_TEST(calc_no_x_24) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "55/(10*5+5)\0";  //  err

  double res = 0.0, expected = 0.8473107;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(entry_str1, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 0);
}
END_TEST

Suite *create_calc_no_x_suite(void) {
  Suite *s;
  TCase *tc_calc_no_x;
  s = suite_create("\n calc_no_x");
  tc_calc_no_x = tcase_create("calc_no_x");
  tcase_add_test(tc_calc_no_x, calc_no_x_1);
  tcase_add_test(tc_calc_no_x, calc_no_x_2);
  tcase_add_test(tc_calc_no_x, calc_no_x_3);
  tcase_add_test(tc_calc_no_x, calc_no_x_4);
  tcase_add_test(tc_calc_no_x, calc_no_x_5);
  tcase_add_test(tc_calc_no_x, calc_no_x_6);
  tcase_add_test(tc_calc_no_x, calc_no_x_7);
  tcase_add_test(tc_calc_no_x, calc_no_x_8);
  tcase_add_test(tc_calc_no_x, calc_no_x_9);
  tcase_add_test(tc_calc_no_x, calc_no_x_10);
  tcase_add_test(tc_calc_no_x, calc_no_x_11);
  tcase_add_test(tc_calc_no_x, calc_no_x_12);
  tcase_add_test(tc_calc_no_x, calc_no_x_13);
  tcase_add_test(tc_calc_no_x, calc_no_x_14);
  tcase_add_test(tc_calc_no_x, calc_no_x_15);
  tcase_add_test(tc_calc_no_x, calc_no_x_16);
  tcase_add_test(tc_calc_no_x, calc_no_x_17);
  tcase_add_test(tc_calc_no_x, calc_no_x_18);
  tcase_add_test(tc_calc_no_x, calc_no_x_19);
  tcase_add_test(tc_calc_no_x, calc_no_x_20);
  tcase_add_test(tc_calc_no_x, calc_no_x_21);
  tcase_add_test(tc_calc_no_x, calc_no_x_22);
  tcase_add_test(tc_calc_no_x, calc_no_x_23);
  tcase_add_test(tc_calc_no_x, calc_no_x_24);
  suite_add_tcase(s, tc_calc_no_x);
  return s;
}

START_TEST(calc_with_x_test_1) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "1+x\0";
  char str[2000] = "\0";

  double x = 3.0;

  x_to_string(entry_str1, str, x);

  double res = 0.0, expected = 4.0;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(str, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 1);
}
END_TEST

START_TEST(calc_with_x_test_2) {
  char polskya[1024] = "\0";
  char str[2000] = "\0";
  char out[2000] = "\0";
  char entry_str1[2000] = "1*5*x\0";

  double x = 9.0;
  x_to_string(entry_str1, str, x);

  double res = 0.0, expected = 45.0;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(str, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 1);
}
END_TEST

START_TEST(calc_with_x_test_3) {
  char polskya[1024] = "\0";
  char out[2000] = "\0";
  char entry_str1[2000] = "cos(5+9*3)-x\0";
  char str[2000] = "\0";
  double x = 21.2;

  x_to_string(entry_str1, str, x);

  double res = 0.0, expected = -20.3657766;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(str, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 1);
}
END_TEST

START_TEST(calc_with_x_test_4) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "cos(5-9/3) mod x\0";
  char str[2000] = "\0";
  double x = 21.2;

  x_to_string(entry_str1, str, x);

  double res = 0.0, expected = -0.4161468;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(str, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 1);
}
END_TEST

START_TEST(calc_with_x_test_5) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "sqrt(x^9,5*ln(4)) - log(21.2)\0";
  char str[2000] = "\0";
  double x = 5.1;

  x_to_string(entry_str1, str, x);

  double res = 0.0, expected = 1778.4147980;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(str, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 1);
}
END_TEST

START_TEST(calc_with_x_test_6) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "acos(5)^asin(3)-4+atan(~x)\0";
  char str[2000] = "\0";
  double x = 2.1;

  x_to_string(entry_str1, str, x);

  double res = 0.0, expected = NAN;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(str, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (isnanf(res)) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 1);
}
END_TEST

START_TEST(calc_with_x_test_7) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "acos(5)^asin(3)-4+atan(-x)\0";  //  err
  char str[2000] = "\0";
  double x = 2.1;

  x_to_string(entry_str1, str, x);

  double res = 0.0, expected = 1778.4147980;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(str, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 0);
}
END_TEST

START_TEST(calc_with_x_test_8) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "-x\0";  //  err
  char str[2000] = "\0";
  double x = 25;

  x_to_string(entry_str1, str, x);

  double res = 0.0, expected = 1778.4147980;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(str, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 0);
}
END_TEST

START_TEST(calc_with_x_test_9) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "`x\0";
  char str[2000] = "\0";
  double x = 25;

  x_to_string(entry_str1, str, x);

  double res = 0.0, expected = 25.0000000;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(str, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 1);
}
END_TEST

START_TEST(calc_with_x_test_10) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "tan(2.1) + atan(x)\0";
  char str[2000] = "\0";
  double x = 2;

  x_to_string(entry_str1, str, x);

  double res = 0.0, expected = -0.6026978;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(str, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 1);
}
END_TEST

START_TEST(calc_with_x_test_11) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "t(2.1) + atan(x)\0";  //  err
  char str[2000] = "\0";
  double x = 2;

  x_to_string(entry_str1, str, x);

  double res = 0.0, expected = -0.6026978;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(str, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 0);
}
END_TEST

START_TEST(calc_with_x_test_12) {  //  two x!!!!!!!!!!!!!!!

  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "sin(x)^atan(x)\0";
  char str[2000] = "\0";
  double x = 2.1;

  x_to_string(entry_str1, str, x);

  double res = 0.0, expected = 0.8473107;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(str, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 1);
}
END_TEST

START_TEST(calc_with_x_test_13) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "sin(x)moa\0";  //  err
  char str[2000] = "\0";
  double x = 2.1;

  x_to_string(entry_str1, str, x);

  double res = 0.0, expected = 0.8473107;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(str, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 0);
}
END_TEST

START_TEST(calc_with_x_test_14) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "sin)x\0";  //  err
  char str[2000] = "\0";
  double x = 2.1;

  x_to_string(entry_str1, str, x);

  double res = 0.0, expected = 0.8473107;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(str, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 0);
}
END_TEST

START_TEST(calc_with_x_test_15) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "x+++2.1\0";  //  err
  char str[2000] = "\0";
  double x = 1;

  x_to_string(entry_str1, str, x);

  double res = 0.0, expected = 0.8473107;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(str, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 0);
}
END_TEST

START_TEST(calc_with_x_test_16) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "x+2.1+\0";  //  err
  char str[2000] = "\0";
  double x = 1;

  x_to_string(entry_str1, str, x);

  double res = 0.0, expected = 0.8473107;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(str, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 0);
}
END_TEST

START_TEST(calc_with_x_test_17) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "x+2.1~\0";  //  err
  char str[2000] = "\0";
  double x = 1;

  x_to_string(entry_str1, str, x);

  double res = 0.0, expected = 0.8473107;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(str, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 0);
}
END_TEST

START_TEST(calc_with_x_test_18) {
  char polskya[1024] = "\0";

  char out[2000] = "\0";
  char entry_str1[2000] = "fasx\0";  //  err
  char str[2000] = "\0";
  double x = 1;

  x_to_string(entry_str1, str, x);

  double res = 0.0, expected = 0.8473107;
  int flag_calc = 0, flag_ok = 0, flag = 0;
  flag_ok = dijkstra(str, polskya);
  // printf("flag_OK=%d\n", flag_ok);
  if (flag_ok == 0) {
    flag_ok = is_correct(polskya);
    // printf("flag_OK=%d\n", flag_ok);
    if (flag_ok == 1) {
      res = calculate(polskya, &flag_calc);
      if (flag_calc == 0) {
        if (fabs(res - expected) < EPS) {
          flag = 1;
        }
      }
    }
  }
  ck_assert_uint_eq(flag, 0);
}
END_TEST

Suite *calc_with_x_suite(void) {
  Suite *s;
  TCase *tc_calc_with_x;
  s = suite_create("calc_with_x");
  tc_calc_with_x = tcase_create("calc_with_x");
  tcase_add_test(tc_calc_with_x, calc_with_x_test_1);
  tcase_add_test(tc_calc_with_x, calc_with_x_test_2);
  tcase_add_test(tc_calc_with_x, calc_with_x_test_3);
  tcase_add_test(tc_calc_with_x, calc_with_x_test_4);
  tcase_add_test(tc_calc_with_x, calc_with_x_test_5);
  tcase_add_test(tc_calc_with_x, calc_with_x_test_6);
  tcase_add_test(tc_calc_with_x, calc_with_x_test_7);
  tcase_add_test(tc_calc_with_x, calc_with_x_test_8);
  tcase_add_test(tc_calc_with_x, calc_with_x_test_9);
  tcase_add_test(tc_calc_with_x, calc_with_x_test_10);
  tcase_add_test(tc_calc_with_x, calc_with_x_test_11);
  tcase_add_test(tc_calc_with_x, calc_with_x_test_12);
  tcase_add_test(tc_calc_with_x, calc_with_x_test_13);
  tcase_add_test(tc_calc_with_x, calc_with_x_test_14);
  tcase_add_test(tc_calc_with_x, calc_with_x_test_15);
  tcase_add_test(tc_calc_with_x, calc_with_x_test_16);
  tcase_add_test(tc_calc_with_x, calc_with_x_test_17);
  tcase_add_test(tc_calc_with_x, calc_with_x_test_18);

  suite_add_tcase(s, tc_calc_with_x);
  return s;
}

START_TEST(calc_credit_ann_1) {
  int term = 5;
  double percent = 5.0;
  double sum_credit = 10000.0;

  double monthly = annuity_credit(sum_credit, term, percent);
  double tax = monthly * term - sum_credit;
  double debt_interest = monthly * term;

  double monthly_ex = 2025.07;
  double tax_ex = monthly_ex * term - sum_credit;
  double debt_interest_ex = monthly_ex * term;

  int flag_1 = 0;
  if (fabs(monthly_ex - monthly) < EPS_1) flag_1 = 1;
  ck_assert_int_eq(flag_1, 1);

  int flag_2 = 0;
  if (fabs(tax_ex - tax) < EPS_1) flag_2 = 1;
  ck_assert_int_eq(flag_2, 1);

  int flag_3 = 0;
  if (fabs(debt_interest_ex - debt_interest) < EPS_1) flag_3 = 1;
  ck_assert_int_eq(flag_3, 1);
}
END_TEST

START_TEST(calc_credit_ann_2) {
  int term = 55;
  double percent = 5.17;
  double sum_credit = 1335.7;

  double monthly = annuity_credit(sum_credit, term, percent);
  double tax = monthly * term - sum_credit;
  double debt_interest = monthly * term;

  double monthly_ex = 27.33;
  double tax_ex = monthly_ex * term - sum_credit;
  double debt_interest_ex = monthly_ex * term;

  int flag_1 = 0;
  if (fabs(monthly_ex - monthly) < EPS_1) flag_1 = 1;
  ck_assert_int_eq(flag_1, 1);

  int flag_2 = 0;
  if (fabs(tax_ex - tax) < EPS_1) flag_2 = 1;
  ck_assert_int_eq(flag_2, 1);

  int flag_3 = 0;
  if (fabs(debt_interest_ex - debt_interest) < EPS_1) flag_3 = 1;
  ck_assert_int_eq(flag_3, 1);
}
END_TEST

START_TEST(calc_credit_ann_3) {
  int term = 12;
  double percent = 34;
  double sum_credit = 875;

  double monthly = annuity_credit(sum_credit, term, percent);
  double tax = monthly * term - sum_credit;
  double debt_interest = monthly * term;

  double monthly_ex = 87.03;
  double tax_ex = monthly_ex * term - sum_credit;
  double debt_interest_ex = monthly_ex * term;

  int flag_1 = 0;
  if (fabs(monthly_ex - monthly) < EPS_1) flag_1 = 1;
  ck_assert_int_eq(flag_1, 1);

  int flag_2 = 0;
  if (fabs(tax_ex - tax) < EPS_1) flag_2 = 1;
  ck_assert_int_eq(flag_2, 1);

  int flag_3 = 0;
  if (fabs(debt_interest_ex - debt_interest) < EPS_1) flag_3 = 1;
  ck_assert_int_eq(flag_3, 1);
}
END_TEST

START_TEST(calc_credit_ann_4) {
  int term = 25;
  double percent = 15;
  double sum_credit = 965000.0;

  double monthly = annuity_credit(sum_credit, term, percent);
  double tax = monthly * term - sum_credit;
  double debt_interest = monthly * term;

  double monthly_ex = 45183.68;
  double tax_ex = monthly_ex * term - sum_credit;
  double debt_interest_ex = monthly_ex * term;

  int flag_1 = 0;
  if (fabs(monthly_ex - monthly) < EPS_1) flag_1 = 1;
  ck_assert_int_eq(flag_1, 1);

  int flag_2 = 0;
  if (fabs(tax_ex - tax) < EPS_1) flag_2 = 1;
  ck_assert_int_eq(flag_2, 1);

  int flag_3 = 0;
  if (fabs(debt_interest_ex - debt_interest) < EPS_1) flag_3 = 1;
  ck_assert_int_eq(flag_3, 1);
}
END_TEST

Suite *calc_credit_ann(void) {
  Suite *s;
  TCase *tc_calc_credit_ann;
  s = suite_create("calc_credit_ann");
  tc_calc_credit_ann = tcase_create("calc_credit_ann_");
  tcase_add_test(tc_calc_credit_ann, calc_credit_ann_1);
  tcase_add_test(tc_calc_credit_ann, calc_credit_ann_2);
  tcase_add_test(tc_calc_credit_ann, calc_credit_ann_3);
  tcase_add_test(tc_calc_credit_ann, calc_credit_ann_4);
  suite_add_tcase(s, tc_calc_credit_ann);
  return s;
}

START_TEST(calc_credit_diff_1) {
  int term = 5;
  double percent = 5.0;
  double sum_credit = 10000.0;
  double sum = 0.0;

  for (int i = 1; i <= term; i++)
    sum += differentiated_credit(sum_credit, term, i, percent);
  double monthly = differentiated_credit(sum_credit, term, 1, percent);
  double monthly_last = differentiated_credit(sum_credit, term, term, percent);
  double tax = sum - sum_credit;

  double monthly_ex = 2041.67;
  double monthly_last_ex = 2008.33;
  double tax_ex = 125.0;
  double sum_ex = 10125.0;

  int flag_1 = 0;
  if (fabs(sum - sum_ex) < EPS_1) flag_1 = 1;
  ck_assert_int_eq(flag_1, 1);

  int flag_2 = 0;
  if (fabs(monthly_ex - monthly) < EPS_1) flag_2 = 1;
  ck_assert_int_eq(flag_2, 1);

  int flag_3 = 0;
  if (fabs(monthly_last_ex - monthly_last) < EPS_1) flag_3 = 1;
  ck_assert_int_eq(flag_3, 1);

  int flag_4 = 0;
  if (fabs(tax_ex - tax) < EPS_1) flag_4 = 1;
  ck_assert_int_eq(flag_4, 1);
}
END_TEST

START_TEST(calc_credit_diff_2) {
  double sum = 0.0;
  int term = 55;
  double percent = 5.17;
  double sum_credit = 1335.7;

  for (int i = 1; i <= term; i++)
    sum += differentiated_credit(sum_credit, term, i, percent);
  double monthly = differentiated_credit(sum_credit, term, 1, percent);
  double monthly_last = differentiated_credit(sum_credit, term, term, percent);
  double tax = sum - sum_credit;

  double monthly_ex = 30.04;
  double monthly_last_ex = 24.39;
  double tax_ex = 161.13;
  double sum_ex = 1496.83;

  int flag_1 = 0;
  if (fabs(sum - sum_ex) < EPS_1) flag_1 = 1;
  ck_assert_int_eq(flag_1, 1);

  int flag_2 = 0;
  if (fabs(monthly_ex - monthly) < EPS_1) flag_2 = 1;
  ck_assert_int_eq(flag_2, 1);

  int flag_3 = 0;
  if (fabs(monthly_last_ex - monthly_last) < EPS_1) flag_3 = 1;
  ck_assert_int_eq(flag_3, 1);

  int flag_4 = 0;
  if (fabs(tax_ex - tax) < EPS_1) flag_4 = 1;
  ck_assert_int_eq(flag_4, 1);
}
END_TEST

START_TEST(calc_credit_diff_3) {
  double sum = 0.0;
  int term = 12;
  double percent = 34;
  double sum_credit = 875;

  for (int i = 1; i <= term; i++)
    sum += differentiated_credit(sum_credit, term, i, percent);
  double monthly = differentiated_credit(sum_credit, term, 1, percent);
  double monthly_last = differentiated_credit(sum_credit, term, term, percent);
  double tax = sum - sum_credit;

  double monthly_ex = 97.71;
  double monthly_last_ex = 74.98;
  double tax_ex = 161.15;
  double sum_ex = 1036.15;

  int flag_1 = 0;
  if (fabs(sum - sum_ex) < EPS_1) flag_1 = 1;
  ck_assert_int_eq(flag_1, 1);

  int flag_2 = 0;
  if (fabs(monthly_ex - monthly) < EPS_1) flag_2 = 1;
  ck_assert_int_eq(flag_2, 1);

  int flag_3 = 0;
  if (fabs(monthly_last_ex - monthly_last) < EPS_1) flag_3 = 1;
  ck_assert_int_eq(flag_3, 1);

  int flag_4 = 0;
  if (fabs(tax_ex - tax) < EPS_1) flag_4 = 1;
  ck_assert_int_eq(flag_4, 1);
}
END_TEST

START_TEST(calc_credit_diff_4) {
  double sum = 0.0;
  int term = 25;
  double percent = 15;
  double sum_credit = 965000.0;

  for (int i = 1; i <= term; i++)
    sum += differentiated_credit(sum_credit, term, i, percent);
  double monthly = differentiated_credit(sum_credit, term, 1, percent);
  double monthly_last = differentiated_credit(sum_credit, term, term, percent);
  double tax = sum - sum_credit;

  double monthly_ex = 50662.50;
  double monthly_last_ex = 39082.50;
  double tax_ex = 156812.50;
  double sum_ex = 1121812.50;

  int flag_1 = 0;
  if (fabs(sum - sum_ex) < EPS_1) flag_1 = 1;
  ck_assert_int_eq(flag_1, 1);

  int flag_2 = 0;
  if (fabs(monthly_ex - monthly) < EPS_1) flag_2 = 1;
  ck_assert_int_eq(flag_2, 1);

  int flag_3 = 0;
  if (fabs(monthly_last_ex - monthly_last) < EPS_1) flag_3 = 1;
  ck_assert_int_eq(flag_3, 1);

  int flag_4 = 0;
  if (fabs(tax_ex - tax) < EPS_1) flag_4 = 1;
  ck_assert_int_eq(flag_4, 1);
}
END_TEST

Suite *calc_credit_diff(void) {
  Suite *s;
  TCase *tc_calc_credit_diff;
  s = suite_create("calc_credit_diff");
  tc_calc_credit_diff = tcase_create("calc_credit_diff_");
  tcase_add_test(tc_calc_credit_diff, calc_credit_diff_1);
  tcase_add_test(tc_calc_credit_diff, calc_credit_diff_2);
  tcase_add_test(tc_calc_credit_diff, calc_credit_diff_3);
  tcase_add_test(tc_calc_credit_diff, calc_credit_diff_4);
  suite_add_tcase(s, tc_calc_credit_diff);
  return s;
}

START_TEST(calc_deposit_simple_1) {
  struct info_deposit deposit;

  deposit.t_start.tm_year = 123;
  deposit.t_start.tm_mon = 0;
  deposit.t_start.tm_mday = 1;
  deposit.freq_start = 1;
  deposit.sum_d = 10000.0;

  struct deposit_res result;

  int term = 12;
  double percent_deposit = 12.0;
  int capitalization = 0;

  result = calculate_deposit(term, deposit, percent_deposit, capitalization);

  double accr_perc_ex = 1200.84;
  double amount_by_end_deposit_period_ex = 10000.00;

  int flag_1 = 0;
  if (fabs(result.accr_perc - accr_perc_ex) < EPS_0) flag_1 = 1;
  ck_assert_int_eq(flag_1, 1);

  int flag_2 = 0;
  if (fabs(result.tax_amount - 0.0) < EPS_1) flag_2 = 1;
  ck_assert_int_eq(flag_2, 1);

  int flag_3 = 0;
  if (fabs(result.amount_by_end_deposit_period -
           amount_by_end_deposit_period_ex) < EPS_1)
    flag_3 = 1;
  ck_assert_int_eq(flag_3, 1);
}
END_TEST

START_TEST(calc_deposit_simple_2) {
  struct info_deposit deposit;

  deposit.t_start.tm_year = 123;
  deposit.t_start.tm_mon = 0;
  deposit.t_start.tm_mday = 1;
  deposit.freq_start = 1;
  deposit.sum_d = 1250000.0;

  deposit.freq_add_1 = 1;
  deposit.sum_add_1 = 100000.0;
  deposit.t_add_1.tm_year = 123;
  deposit.t_add_1.tm_mon = 5;
  deposit.t_add_1.tm_mday = 29;

  deposit.freq_add_2 = 2;
  deposit.sum_add_2 = 333.0;
  deposit.t_add_2.tm_year = 123;
  deposit.t_add_2.tm_mon = 1;
  deposit.t_add_2.tm_mday = 24;

  struct deposit_res result;

  int term = 24;
  double percent_deposit = 44.0;
  int capitalization = 0;

  result = calculate_deposit(term, deposit, percent_deposit, capitalization);

  double accr_perc_ex = 1169585.55;
  double amount_by_end_deposit_period_ex = 1357659.00;
  double tax_amount_ex = 132546.13;

  int flag_1 = 0;
  if (fabs(result.accr_perc - accr_perc_ex) < EPS_1) flag_1 = 1;
  ck_assert_int_eq(flag_1, 1);

  int flag_2 = 0;
  if (fabs(result.tax_amount - tax_amount_ex) < EPS_1) flag_2 = 1;
  ck_assert_int_eq(flag_2, 1);

  int flag_3 = 0;
  if (fabs(result.amount_by_end_deposit_period -
           amount_by_end_deposit_period_ex) < EPS_1)
    flag_3 = 1;
  ck_assert_int_eq(flag_3, 1);
}
END_TEST

START_TEST(calc_deposit_simple_3) {
  struct info_deposit deposit;

  deposit.t_start.tm_year = 123;
  deposit.t_start.tm_mon = 1;
  deposit.t_start.tm_mday = 24;
  deposit.freq_start = 1;
  deposit.sum_d = 555125.0;

  deposit.freq_add_1 = 3;
  deposit.sum_add_1 = 10000.0;
  deposit.t_add_1.tm_year = 123;
  deposit.t_add_1.tm_mon = 5;
  deposit.t_add_1.tm_mday = 29;

  deposit.freq_add_2 = 2;
  deposit.sum_add_2 = 333.0;
  deposit.t_add_2.tm_year = 123;
  deposit.t_add_2.tm_mon = 2;
  deposit.t_add_2.tm_mday = 1;

  deposit.freq_withdr_1 = 1;
  deposit.sum_withdr_1 = 50000.0;
  deposit.t_withdr_1.tm_year = 123;
  deposit.t_withdr_1.tm_mon = 1;
  deposit.t_withdr_1.tm_mday = 26;

  deposit.freq_withdr_2 = 2;
  deposit.sum_withdr_2 = 37.0;
  deposit.t_withdr_2.tm_year = 123;
  deposit.t_withdr_2.tm_mon = 1;
  deposit.t_withdr_2.tm_mday = 28;

  struct deposit_res result;

  int term = 11;
  double percent_deposit = 14.0;
  int capitalization = 0;

  result = calculate_deposit(term, deposit, percent_deposit, capitalization);

  double accr_perc_ex = 65757.60;
  double amount_by_end_deposit_period_ex = 518381.00;
  double tax_amount_ex = 0.0;
  int flag_1 = 0;
  if (fabs(result.accr_perc - accr_perc_ex) < 2) flag_1 = 1;
  ck_assert_int_eq(flag_1, 1);

  int flag_2 = 0;
  if (fabs(result.tax_amount - tax_amount_ex) < EPS_1) flag_2 = 1;
  ck_assert_int_eq(flag_2, 1);

  int flag_3 = 0;
  if (fabs(result.amount_by_end_deposit_period -
           amount_by_end_deposit_period_ex) < EPS_1)
    flag_3 = 1;
  ck_assert_int_eq(flag_3, 1);
}
END_TEST

Suite *calc_deposit_simple(void) {
  Suite *s;
  TCase *tc_calc_deposit_simple;
  s = suite_create("calc_deposit_simple");
  tc_calc_deposit_simple = tcase_create("calc_deposit_simple_");
  tcase_add_test(tc_calc_deposit_simple, calc_deposit_simple_1);
  tcase_add_test(tc_calc_deposit_simple, calc_deposit_simple_2);
  tcase_add_test(tc_calc_deposit_simple, calc_deposit_simple_3);
  suite_add_tcase(s, tc_calc_deposit_simple);
  return s;
}

START_TEST(calc_deposit_comp_perc_1) {
  struct info_deposit deposit;

  deposit.t_start.tm_year = 123;
  deposit.t_start.tm_mon = 0;
  deposit.t_start.tm_mday = 1;
  deposit.freq_start = 1;
  deposit.sum_d = 10000.0;

  struct deposit_res result;

  int term = 12;
  double percent_deposit = 12.0;
  int capitalization = 1;

  result = calculate_deposit(term, deposit, percent_deposit, capitalization);

  double accr_perc_ex = 1274.74;
  double amount_by_end_deposit_period_ex = 11274.74;

  int flag_1 = 0;
  if (fabs(result.accr_perc - accr_perc_ex) < EPS_0) flag_1 = 1;
  ck_assert_int_eq(flag_1, 1);

  int flag_2 = 0;
  if (fabs(result.tax_amount - 0.0) < EPS_1) flag_2 = 1;
  ck_assert_int_eq(flag_2, 1);

  int flag_3 = 0;
  if (fabs(result.amount_by_end_deposit_period -
           amount_by_end_deposit_period_ex) < EPS_1)
    flag_3 = 1;
  ck_assert_int_eq(flag_3, 1);
}
END_TEST

START_TEST(calc_deposit_comp_perc_2) {
  struct info_deposit deposit;

  deposit.t_start.tm_year = 123;
  deposit.t_start.tm_mon = 0;
  deposit.t_start.tm_mday = 1;
  deposit.freq_start = 2;
  deposit.sum_d = 1250000.0;

  deposit.freq_add_1 = 1;
  deposit.sum_add_1 = 10000.0;
  deposit.t_add_1.tm_year = 123;
  deposit.t_add_1.tm_mon = 5;
  deposit.t_add_1.tm_mday = 29;

  deposit.freq_add_2 = 2;
  deposit.sum_add_2 = 333.0;
  deposit.t_add_2.tm_year = 123;
  deposit.t_add_2.tm_mon = 1;
  deposit.t_add_2.tm_mday = 24;

  struct deposit_res result;

  int term = 24;
  double percent_deposit = 44.0;
  int capitalization = 1;

  result = calculate_deposit(term, deposit, percent_deposit, capitalization);

  double accr_perc_ex = 1729870.09;
  double amount_by_end_deposit_period_ex = 2997529.09;
  double tax_amount_ex = 205383.11;

  int flag_1 = 0;
  if (fabs(result.accr_perc - accr_perc_ex) < EPS_1) flag_1 = 1;
  ck_assert_int_eq(flag_1, 1);

  int flag_2 = 0;
  if (fabs(result.tax_amount - tax_amount_ex) < EPS_1) flag_2 = 1;
  ck_assert_int_eq(flag_2, 1);

  int flag_3 = 0;
  if (fabs(result.amount_by_end_deposit_period -
           amount_by_end_deposit_period_ex) < EPS_1)
    flag_3 = 1;
  ck_assert_int_eq(flag_3, 1);
}
END_TEST

START_TEST(calc_deposit_comp_perc_3) {
  struct info_deposit deposit;

  deposit.t_start.tm_year = 123;
  deposit.t_start.tm_mon = 2;
  deposit.t_start.tm_mday = 31;
  deposit.freq_start = 3;
  deposit.sum_d = 555125.0;

  deposit.freq_add_1 = 2;
  deposit.sum_add_1 = 10000.0;
  deposit.t_add_1.tm_year = 123;
  deposit.t_add_1.tm_mon = 3;
  deposit.t_add_1.tm_mday = 1;

  deposit.freq_add_2 = 3;
  deposit.sum_add_2 = 333.0;
  deposit.t_add_2.tm_year = 123;
  deposit.t_add_2.tm_mon = 5;
  deposit.t_add_2.tm_mday = 30;

  deposit.freq_withdr_1 = 1;
  deposit.sum_withdr_1 = 50000.0;
  deposit.t_withdr_1.tm_year = 124;
  deposit.t_withdr_1.tm_mon = 0;
  deposit.t_withdr_1.tm_mday = 1;

  deposit.freq_withdr_2 = 2;
  deposit.sum_withdr_2 = 555.0;
  deposit.t_withdr_2.tm_year = 123;
  deposit.t_withdr_2.tm_mon = 5;
  deposit.t_withdr_2.tm_mday = 24;

  struct deposit_res result;

  int term = 18;
  double percent_deposit = 14.0;
  int capitalization = 1;

  result = calculate_deposit(term, deposit, percent_deposit, capitalization);

  double accr_perc_ex = 136625.89;
  double amount_by_end_deposit_period_ex = 813536.89;
  double tax_amount_ex = 0.0;

  int flag_1 = 0;
  if (fabs(result.accr_perc - accr_perc_ex) < 2) flag_1 = 1;
  ck_assert_int_eq(flag_1, 1);

  int flag_2 = 0;
  if (fabs(result.tax_amount - tax_amount_ex) < EPS_1) flag_2 = 1;
  ck_assert_int_eq(flag_2, 1);

  int flag_3 = 0;
  if (fabs(result.amount_by_end_deposit_period -
           amount_by_end_deposit_period_ex) < 2)
    flag_3 = 1;
  ck_assert_int_eq(flag_3, 1);
}
END_TEST

Suite *calc_deposit_comp_perc(void) {
  Suite *s;
  TCase *tc_calc_deposit_comp_perc;
  s = suite_create("calc_deposit_comp_perc");
  tc_calc_deposit_comp_perc = tcase_create("calc_deposit_comp_perc_");
  tcase_add_test(tc_calc_deposit_comp_perc, calc_deposit_comp_perc_1);
  tcase_add_test(tc_calc_deposit_comp_perc, calc_deposit_comp_perc_2);
  tcase_add_test(tc_calc_deposit_comp_perc, calc_deposit_comp_perc_3);
  // tcase_add_test(tc_calc_deposit_comp_perc, calc_deposit_comp_perc_4);
  suite_add_tcase(s, tc_calc_deposit_comp_perc);
  return s;
}

void calc_testing(SRunner **sr) {
  *sr = srunner_create(create_calc_no_x_suite());
  srunner_add_suite(*sr, calc_with_x_suite());
  srunner_add_suite(*sr, calc_credit_ann());
  srunner_add_suite(*sr, calc_credit_diff());
  srunner_add_suite(*sr, calc_deposit_simple());
  srunner_add_suite(*sr, calc_deposit_comp_perc());
}

int main(void) {
  int number_failed;
  SRunner *sr = NULL;
  calc_testing(&sr);
  srunner_run_all(sr, CK_ENV);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}
