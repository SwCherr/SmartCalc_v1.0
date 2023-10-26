#include "test.h"

START_TEST(CREDIT_ANNUITY_01) {
  double credit_sum = 3000000;
  int credit_term = 96;
  double credit_rate = 12;
  int repayment_procedure = 0;

  double min_payment = 0;
  double max_payment = 0;
  double total_payments = 0;
  double overpayment = 0;

  credit_calculate(credit_sum, credit_term, credit_rate, repayment_procedure,
                   &min_payment, &max_payment, &total_payments, &overpayment);
  ck_assert_double_eq_tol(min_payment, 48758.52, 1e-2);
  ck_assert_double_eq_tol(max_payment, 48758.52, 1e-2);
  ck_assert_double_eq_tol(total_payments, 4680818.33, 1e-2);
  ck_assert_double_eq_tol(overpayment, 1680818.33, 1e-2);
}
END_TEST

START_TEST(CREDIT_DIFFERENTIATED_01) {
  double credit_sum = 3000000;
  int credit_term = 96;
  double credit_rate = 12;
  int repayment_procedure = 1;

  double min_payment = 0;
  double max_payment = 0;
  double total_payments = 0;
  double overpayment = 0;

  credit_calculate(credit_sum, credit_term, credit_rate, repayment_procedure,
                   &min_payment, &max_payment, &total_payments, &overpayment);
  ck_assert_double_eq_tol(min_payment, 31562.50, 1e-2);
  ck_assert_double_eq_tol(max_payment, 61250, 1e-2);
  ck_assert_double_eq_tol(total_payments, 4455000, 1e-2);
  ck_assert_double_eq_tol(overpayment, 1455000, 1e-2);
}
END_TEST

Suite *Credit_calc(void) {
  Suite *s = suite_create("\033[45m--- CREDIT CALC ---\033[0m");
  TCase *tc1_1 = tcase_create("CREDIT CALC: ");

  suite_add_tcase(s, tc1_1);

  tcase_add_test(tc1_1, CREDIT_ANNUITY_01);
  tcase_add_test(tc1_1, CREDIT_DIFFERENTIATED_01);

  return s;
}