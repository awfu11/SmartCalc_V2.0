#include "credit.h"

void annuityCredit(double loan, double percent, double month,
                   double *totalPayment, double *monthlyPayment,
                   double *overPayment) {
  double m = percent / 12.0 / 100.0;
  double coef = (m * pow(1.0 + m, month)) / (pow(1.0 + m, month) - 1.0);
  *monthlyPayment = loan * coef;
  *totalPayment = *monthlyPayment * month;
  *overPayment = *totalPayment - loan;
}

void diffCredit(double loan, double percent, double month, double *totalPayment,
                double *monthlyPaymentFirst, double *monthlyPaymentLast,
                double *overPayment) {
  percent /= 100.0;
  double sd = loan / month;
  double sp = 1.0;
  double all = loan;
  double days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int i = 0;
  *totalPayment = 0.0;
  *monthlyPaymentFirst = loan * percent * days[0] / 365.0 + sd;
  while (loan > 0) {
    sp = loan * percent * days[i] / 365.0;
    loan -= sd;
    *totalPayment += sd + sp;
    if (i == 11) {
      i = 0;
    } else {
      i++;
    }
  }
  *monthlyPaymentLast = sp + sd;
  *overPayment = *totalPayment - all;
}
