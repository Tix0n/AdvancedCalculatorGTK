#include "parsing_and_calc.h"

int dijkstra(char *string, char *output_string) {
  stack_sym *head = create_sym();
  int res = 0, count = 0, flag_start = 0;
  if ((int)strlen(string) <= 0) {
    res = -1;
  } else {
    for (int i = 0; string[i] != '\0'; i++) {
      char sym = string[i];
      int info = what_is_it(sym);
      if (info != -11) flag_start += 1;
      if (info == -4 && flag_start == 1) res = -1;
      if ((sym == '-' || sym == '+') && flag_start == 1) res = -1;
      if (info == -3) proc_numbers(string, output_string, &count, &i, &res);
      if (info == 7) proc_trig(head, string, &i, &res);
      if (info == 8) push_sym(head, string[i]);
      if (info >= 1 && info <= 6 && info != 3) {
        if (sym == 'm') if_mod(string, &i, &res);
        if (what_is_it(peek_stack_sym(head)) < info || head == NULL) {
          push_sym(head, string[i]);
        } else {
          while (what_is_it(peek_stack_sym(head)) >= info &&
                 peek_stack_sym(head) != '(') {
            output_string[count++] = peek_stack_sym(head);
            if (peek_stack_sym(head) != '\0') pop_sym(head);
          }
          push_sym(head, string[i]);
        }
      }
      if (info == 9) {
        while (peek_stack_sym(head) != '(' && peek_stack_sym(head) != '\0') {
          output_string[count++] = peek_stack_sym(head);
          pop_sym(head);
        }
        if (peek_stack_sym(head) != '\0') pop_sym(head);
      }
    }
  }
  while (head != NULL && peek_stack_sym(head) != '\0') {
    output_string[count++] = peek_stack_sym(head);
    if (peek_stack_sym(head) != '\0') pop_sym(head);
  }
  destroy_sym(head);
  return res;
}

void proc_numbers(char *string, char *output_string, int *count, int *i,
                  int *res) {
  int flag_tchk = 0;
  for (; what_is_it(string[(*i)]) == -3 || what_is_it(string[(*i)]) == -4;
       (*i)++) {
    if (what_is_it(string[(*i)]) == -4) flag_tchk += 1;
    output_string[(*count)++] = string[(*i)];
  }
  output_string[(*count)++] = ' ';
  (*i)--;
  if (flag_tchk > 1) (*res) = -1;
}

void proc_trig(stack_sym *head, char *string, int *i, int *res) {
  char sym_trig = ' ';
  int result = check_post_func(string, &sym_trig, *i);
  if (result == 0 || result == 1 || result == 2 || result == 3) {
    push_sym(head, sym_trig);
    (*i) += result;
  } else {
    (*res) = -1;
  }
}

void if_mod(char *string, int *i, int *res) {
  char sym_trig = ' ';
  int result = check_mod(string, &sym_trig, *i);
  if (result == 2) {
    string[(*i) + 2] = 'm';
    (*i) += 2;
  } else {
    (*res) = -1;
  }
}

int check_mod(char *string, char *sym_trig, int i) {
  int res = -1;
  int count = (int)strlen(string) - i;
  if (count < 4) {
    res = ERROR;
  } else {
    if (string[i] == 'm' && count >= 3 && string[i + 1] == 'o' &&
        string[i + 2] == 'd') {
      res = 2;
      *sym_trig = 'm';
    }
  }
  return res;
}

void x_to_string(char *str1, char *str2, double x) {
  int len_1 = strlen(str1), info_1 = -10, info_2 = -10;
  int len_2 = 0, flag = -1;
  char tmp[100];
  sprintf(tmp, "%f", x);
  if (tmp[0] == '-') flag = 1;
  for (int i = 0; i < len_1; i++) {
    if (i + 1 <= len_1) {
      info_2 = what_is_it(str1[i + 1]);
    }
    if (i > 0) {
      info_1 = what_is_it(str1[i - 1]);
    }
    if ((i == 0 && str1[i] == 'x' && info_2 != -3 && info_2 != -4) ||
        (i > 0 && str1[i] == 'x' && info_1 != -3 && info_1 != -4)) {
      char num_str[100];
      if (flag == 1)
        sprintf(num_str, "(~%.7f", x * -1);
      else
        sprintf(num_str, "%.7f", x);
      if (flag == 1) strcat(num_str, ")\0");
      int numLen = strlen(num_str);
      strcpy(&str2[len_2], num_str);
      len_2 += numLen;
    } else {
      str2[len_2++] = str1[i];
    }
  }
  str2[len_2] = '\0';
}

int is_correct(char *string) {
  int res = -1, count_num = 0, count_post = 0, count_bin = 0;
  int flag_post = -1;
  for (int i = 0; string[i] != '\0'; i++) {
    char sym = string[i];
    int info = what_is_it(sym);
    if (info == -3) {
      count_num++;
      for (int k = 0;
           (what_is_it(string[i]) == -3) || (what_is_it(string[i]) == -4);
           k++) {
        i++;
      }
    }
    if (info == 7 || info == 3) {
      count_post++;
      if (count_num > 0) count_post--;
    }
    if (info > 1 && info < 7 && info != 3) {
      count_bin++;
      if (count_num >= 2) {
        count_bin--;
        count_num--;
      }
      if (flag_post) res = -1;
    }
  }
  if (count_num == 1 && count_bin == 0 && count_post == 0) res = 1;
  return res;
}

double calculate(char *string, int *flag) {
  double res = 0.0;
  stack_num *head = create_num();
  int flag_double = 0, flag_peek = 0;
  for (int i = 0; string[i] != '\0' && *flag == 0; i++) {
    flag_double = 0;
    char sym = string[i];
    int info = what_is_it(sym);
    char temp[100] = "\0";
    if (info == -3) {
      for (int k = 0;
           (what_is_it(string[i]) == -3) || (what_is_it(string[i]) == -4);
           k++, i++) {
        if (what_is_it(string[i]) == -4) flag_double = 1;
        temp[k] = string[i];
      }
      double num = str_to_double(temp, flag_double);
      push_num(head, num);
      memset(temp, 0, sizeof(temp));
    }
    if (info > 0 && info < 8) {
      double num_1 = 0.0, num_2 = 0.0, oper = 0.0;
      num_1 = peek_stack_num(head, &flag_peek);
      if (flag_peek == -1)
        *flag = -1;
      else
        pop_num(head);
      if (info == 7) {
        if (sym == 'q' && num_1 < EPS) *flag = -1;
        oper = operation(num_1, num_2, string[i]);
        push_num(head, oper);
      } else if (info > 0 && info < 7 && info != 3) {
        num_2 = peek_stack_num(head, &flag_peek);
        if (info == 4 && fabs(num_1) < EPS) *flag = -1;
        if (flag_peek == -1)
          *flag = -1;
        else
          pop_num(head);
        oper = operation(num_1, num_2, string[i]);
        push_num(head, oper);
      }
    }
  }
  res = peek_stack_num(head, &flag_peek);
  if (flag_peek == -1)
    *flag = -1;
  else
    pop_num(head);
  destroy_num(head);
  return res;
}

int what_is_it(char symbol) {
  int result = -11;
  if (symbol > 47 && symbol < 58) {
    result = -3;
  } else {
    switch (symbol) {
      case ')':
        result = 9;
        break;
      case '(':
        result = 8;
        break;
      case 'm':
        result = 4;
        break;
      case '^':
        result = 6;
        break;
      case '*':
        result = 5;
        break;
      case '/':
        result = 4;
        break;
      case '+':
      case '-':
        result = 2;
        break;
      case '\0':
        result = -1;
        break;
      case '.':
      case ',':
        result = -4;
        break;
      case 'x':
        result = -5;
        break;
      default:
        result = symbol == '~' || symbol == '`' || symbol == 'l' ||
                         symbol == 'L' || symbol == 'a' || symbol == 's' ||
                         symbol == 'S' || symbol == 'c' || symbol == 'C' ||
                         symbol == 't' || symbol == 'T' || symbol == 'q'
                     ? 7
                     : result;
    }
  }
  return result;
}

int check_post_func(char *string, char *sym_trig, int i) {
  int res = ERROR;
  int count = (int)strlen(string) - i;
  if (count < 5 && string[i] != '~' && string[i] != '`') {
    res = ERROR;
  } else {
    if (string[i] == 'l' && count >= 5 && string[i + 1] == 'n') {
      res = 1;
      *sym_trig = 'L';
    } else if (string[i] == '~') {
      if (count == 0) {
        res = 0;
        *sym_trig = '~';
      } else if (count >= 1 && (what_is_it(string[i + 1]) == -3 ||
                                what_is_it(string[i + 1]) == 7 ||
                                what_is_it(string[i + 1]) == 8)) {
        res = 0;
        *sym_trig = '~';
      }
    } else if (string[i] == '`') {
      if (count == 0) {
        res = 0;
      } else if (count >= 1 && (what_is_it(string[i + 1]) == -3 ||
                                what_is_it(string[i + 1]) == 7 ||
                                what_is_it(string[i + 1]) == 8)) {
        res = 0;
      }
    }
    if (res == ERROR) res = check_long_trig(string, &(*sym_trig), i, count);
    if (res == ERROR) res = check_short_trig(string, &(*sym_trig), i, count);
  }
  return res;
}

int check_short_trig(char *string, char *sym_trig, int i, int count) {
  int res = ERROR;
  if (string[i] == 's' && count >= 6 && string[i + 1] == 'i' &&
      string[i + 2] == 'n') {
    res = 2;
    *sym_trig = 's';
  } else if (string[i] == 'c' && count >= 6 && string[i + 1] == 'o' &&
             string[i + 2] == 's') {
    res = 2;
    *sym_trig = 'c';
  } else if (string[i] == 't' && count >= 6 && string[i + 1] == 'a' &&
             string[i + 2] == 'n') {
    res = 2;
    *sym_trig = 't';
  } else if (string[i] == 'l' && count >= 6 && string[i + 1] == 'o' &&
             string[i + 2] == 'g') {
    res = 2;
    *sym_trig = 'l';
  }
  return res;
}

int check_long_trig(char *string, char *sym_trig, int i, int count) {
  int res = ERROR;
  if (string[i] == 'a' && count >= 7 && string[i + 1] == 'c' &&
      string[i + 2] == 'o' && string[i + 3] == 's') {
    res = 3;
    *sym_trig = 'S';
  } else if (string[i] == 'a' && count >= 7 && string[i + 1] == 's' &&
             string[i + 2] == 'i' && string[i + 3] == 'n') {
    res = 3;
    *sym_trig = 'C';
  } else if (string[i] == 'a' && count >= 7 && string[i + 1] == 't' &&
             string[i + 2] == 'a' && string[i + 3] == 'n') {
    res = 3;
    *sym_trig = 'T';
  } else if (string[i] == 's' && count >= 7 && string[i + 1] == 'q' &&
             string[i + 2] == 'r' && string[i + 3] == 't') {
    res = 3;
    *sym_trig = 'q';
  }
  return res;
}

double operation(double num_1, double num_2, char oper) {
  double result = 0.0;
  if (oper == 'S') {
    result = asin(num_1);
  } else if (oper == 'C') {
    result = acos(num_1);
  } else if (oper == 'T') {
    result = atan(num_1);
  } else if (oper == 's') {
    result = sin(num_1);
  } else if (oper == 'c') {
    result = cos(num_1);
  } else if (oper == 't') {
    result = tan(num_1);
  } else if (oper == 'q') {
    result = sqrt(num_1);
  } else if (oper == 'l') {
    result = log(num_1);
  } else if (oper == 'L') {
    result = log10(num_1);
  } else if (oper == '^') {
    result = pow(num_2, num_1);
  } else if (oper == '*') {
    result = num_2 * num_1;
  } else if (oper == '~') {
    result = -num_1;
  } else if (oper == '/') {
    result = num_2 / num_1;
  } else if (oper == 'm') {
    result = fmod(num_2, num_1);
  } else if (oper == '+') {
    result = num_2 + num_1;
  } else if (oper == '-') {
    result = num_2 - num_1;
  } else if (oper == '\0') {
    result = -1;
  }
  return result;
}

double str_to_double(char *str, int flag_double) {
  double num = 0.0;
  char int_part[100] = "\0";
  char frac_part[100] = "\0";

  if (flag_double == 1) {
    int i = 0;
    while (what_is_it(str[i]) != -4) {
      int_part[i] = str[i];
      i++;
    }
    int l = 0;
    i++;
    for (; i < (int)strlen(str); i++) {
      frac_part[l] = str[i];
      l++;
    }
    num = (double)atoi(int_part) + (double)atoi(frac_part) * pow(10, -l);

  } else {
    num = (double)atoi(str);
  }
  return num;
}

void itoa(int n, char *s) {
  int i, sign;

  if ((sign = n) < 0) n = -n;
  i = 0;
  do {
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);
  if (sign < 0) s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

void reverse(char *s) {
  int i, j;
  char c;

  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}
