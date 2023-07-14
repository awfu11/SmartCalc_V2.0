#ifndef _CREDIT_H_
#define _CREDIT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdlib.h>

void annuityCredit(double loan, double percent, double month,
                   double *totalPayment, double *monthlyPayment,
                   double *overPayment);
void diffCredit(double loan, double percent, double month, double *totalPayment,
                double *monthlyPaymentFirst, double *monthlyPaymentLast,
                double *overPayment);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // _CREDIT_H_
