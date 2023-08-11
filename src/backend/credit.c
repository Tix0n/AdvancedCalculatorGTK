#include "credit.h"

double annuity_credit(double loan_amount, int term, double percent) {
  percent /= 1200;
  return loan_amount * percent * pow((1 + percent), term) /
         (pow((1 + percent), term) - 1);
}

double differentiated_credit(double loan_amount, int term, int term_found,
                             double percent) {
  percent /= 1200;
  return loan_amount / term +
         percent * (loan_amount - (loan_amount * (term_found - 1) / term));
}
