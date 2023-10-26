#include "model.h"

void credit_calculate(double sum, int term, double rate, int type_pay,
                      double* min_payment, double* max_payment,
                      double* total_payments, double* overpayment) {
  // ---------------- Аннуитетный ----------------- //
  if (type_pay == 0) {
    for (int i = 0; i < term; i++) {
      double month_percent_rate = rate / 100 / 12.0;
      *min_payment = (sum * month_percent_rate) /
                     (1 - pow(1 + month_percent_rate, (-term)));
      *total_payments += *min_payment;
    }
    *max_payment = *min_payment;
    *overpayment = *total_payments - sum;

    // ------------- Дифференцированный ------------- //
  } else if (type_pay) {
    int flag_max = 1;
    double balance_owed = sum;
    double fixed_debt = sum / term;

    for (int i = 0; i < term; i++) {
      double sum_percent = (balance_owed * rate / 100) / 12;
      *min_payment = sum_percent + fixed_debt;
      balance_owed -= fixed_debt;
      *total_payments += *min_payment;
      *overpayment += sum_percent;

      if (flag_max) {
        *max_payment = *min_payment;
        flag_max = 0;
      }
    }
  }
}
