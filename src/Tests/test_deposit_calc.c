#include "test.h"

START_TEST(DEPOSIT_WHITHOUT_CAPITALIZATION_01) {
  double deposit = 1000000;
  int placement_period = 365;
  double percent_rate = 12;
  double tax_rate = 13;
  int pay_period = 30;
  int capitalization = 0;
  double percent_sum = 0.0;
  double tax_sum = 0.0;
  double deposit_end_sum = 0.0;

  deposit_calculate(deposit, placement_period, percent_rate, tax_rate,
                    pay_period, capitalization, &percent_sum, &tax_sum,
                    &deposit_end_sum);
  ck_assert_double_eq_tol(percent_sum, 119999.08, 1e-0);
  ck_assert_double_eq_tol(tax_sum, 0.0, 1e-2);
  ck_assert_double_eq_tol(deposit_end_sum, 1000000, 1e-0);
}
END_TEST

START_TEST(DEPOSIT_WHITHOUT_CAPITALIZATION_02) {
  double deposit = 1000000;
  int placement_period = 731;
  double percent_rate = 28;
  double tax_rate = 13;
  int pay_period = 365;
  int capitalization = 0;
  double percent_sum = 0.0;
  double tax_sum = 0.0;
  double deposit_end_sum = 0.0;

  deposit_calculate(deposit, placement_period, percent_rate, tax_rate,
                    pay_period, capitalization, &percent_sum, &tax_sum,
                    &deposit_end_sum);
  ck_assert_double_eq_tol(percent_sum, 560000.01, 1e+0);
  ck_assert_double_eq_tol(tax_sum, 39000, 1e+0);
  ck_assert_double_eq_tol(deposit_end_sum, 1000000, 1e+0);
}
END_TEST

START_TEST(DEPOSIT_WHITHOUT_CAPITALIZATION_03) {
  double deposit = 1000000;
  int placement_period = 243;
  double percent_rate = 28;
  double tax_rate = 13;
  int pay_period = 365;
  int capitalization = 0;
  double percent_sum = 0.0;
  double tax_sum = 0.0;
  double deposit_end_sum = 0.0;

  deposit_calculate(deposit, placement_period, percent_rate, tax_rate,
                    pay_period, capitalization, &percent_sum, &tax_sum,
                    &deposit_end_sum);
  ck_assert_double_eq_tol(percent_sum, 186410.96, 1e+0);
  ck_assert_double_eq_tol(tax_sum, 7333.42, 1e+0);
  ck_assert_double_eq_tol(deposit_end_sum, 1000000, 1e+0);
}
END_TEST

START_TEST(DEPOSIT_WHITH_CAPITALIZATION_01) {
  double deposit = 1000000;
  int placement_period = 243;
  double percent_rate = 28;
  double tax_rate = 13;
  int pay_period = 365;
  int capitalization = 1;
  double percent_sum = 0.0;
  double tax_sum = 0.0;
  double deposit_end_sum = 0.0;

  deposit_calculate(deposit, placement_period, percent_rate, tax_rate,
                    pay_period, capitalization, &percent_sum, &tax_sum,
                    &deposit_end_sum);
  ck_assert_double_eq_tol(percent_sum, 186410.96, 1e+0);
  ck_assert_double_eq_tol(tax_sum, 7333.42, 1e+0);
  ck_assert_double_eq_tol(deposit_end_sum, 1186410.96, 1e+0);
}
END_TEST

Suite *Deposit_calc(void) {
  Suite *s = suite_create("\033[45m--- DEPOSIT CALC ---\033[0m");
  TCase *tc1_1 = tcase_create("DEPOSIT CALC: ");

  suite_add_tcase(s, tc1_1);

  tcase_add_test(tc1_1, DEPOSIT_WHITHOUT_CAPITALIZATION_01);
  tcase_add_test(tc1_1, DEPOSIT_WHITHOUT_CAPITALIZATION_02);
  tcase_add_test(tc1_1, DEPOSIT_WHITHOUT_CAPITALIZATION_03);
  tcase_add_test(tc1_1, DEPOSIT_WHITH_CAPITALIZATION_01);

  return s;
}