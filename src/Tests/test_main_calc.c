#include "../Model/model.h"
#include "test.h"

START_TEST(RPN_TEST_0) {
  char string[SIZE] = "13.01-1.09-6.0-((0.0000001*7)+6*(9-2.01))";
  double result = 0;
  double result_check = -36.0200007;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_1) {
  char string[SIZE] = "(-((0.0000001*7)+6*(9-2.01)/8.4+(0.32^5)))";
  double result = 0;
  double result_check = -4.9962132;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_2) {
  char string[SIZE] = "77M4-((3*(3^6))-700)/24*12-2";  // % заменить на MOD
  double result = 0;
  double result_check = -744.4999996;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_3) {
  char string[SIZE] = "(-569.0000987)*(99-6)";
  double result = 0;
  double result_check = -52917.0091791;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_4) {
  char string[SIZE] = "88+(2^2)*(-569.0000987)/(99-6)";
  double result = 0;
  double result_check = 63.5268775;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_5) {
  char string[SIZE] = "(-7.0)+(-3^(-3))";
  double result = 0;
  double result_check = -7.0370370;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_6) {
  char string[SIZE] = "(-cos(3))-(-cos(1))+4/2-(sin(1))*6.09/(-tan(2)/acos(-1)";
  double result = 0;
  double result_check = -3.8376599;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_7) {
  char string[SIZE] =
      "(-6696.5)+1/4/2/1.3*5.9+(-56)+(-sqrt(12))-99+1.4^(-6)-5+8^2";
  double result = 0;
  double result_check = -6795.2639839;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_8) {
  char string[SIZE] =
      "(-cos(3))-(-cos(1))+4/2-(sin(1))+1^2.0000007*6.09/(-tan(2))/acos(-1)";
  double result = 0;
  double result_check = 3.5759963;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_9) {
  char string[SIZE] = "(-1)+(-1)+(-1)-1.9-(-1)-1";
  double result = 0;
  double result_check = -4.9;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_10) {
  char string[SIZE] = "cos(sin(1))";
  double result = 0;
  double result_check = 0.6663667;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_11) {
  char string[SIZE] = "8^2^2";
  double result = 0;
  double result_check = 4096;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_12) {
  char string[SIZE] = "(+8-(-9))-(+9)";
  double result = 0;
  double result_check = 8;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_13) {
  char string[SIZE] = "(+8-9)";
  double result = 0;
  double result_check = -1;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_14) {
  char string[SIZE] =
      "3*(8.0987/8.0987)-65.02+13.01-6.0-(0.0000001*7)+6*(9-2.01)";
  double result = 0;
  double result_check = -13.0700007;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_15) {
  char string[SIZE] = "(-2)^2";
  double result_check = 4;
  double result = 0;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_16) {
  char string[SIZE] = "(-2)-2";
  double result = 0;
  double result_check = -4;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_17) {
  char string[SIZE] = "ln(5)";
  double result = 0;
  double result_check = 1.6094379;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  // printf("result       = %.10f\n", result);
  // printf("result_check = %.10f\n", result_check);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_18) {
  char string[SIZE] = "sin(25)";
  double result = 0;
  double result_check = -0.1323518;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_19) {
  char string[SIZE] = "cos(5)";
  double result = 0;
  double result_check = 0.2836622;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_20) {
  char string[SIZE] = "tan(5)";
  double result = 0;
  double result_check = -3.380515;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_21) {
  char string[SIZE] = "log(5)";
  double result = 0;
  double result_check = 0.69897;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_22) {
  char string[SIZE] = "ln(5)";
  double result = 0;
  double result_check = 1.6094379;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_23) {
  char string[SIZE] = "sqrt(5)";
  double result = 0;
  double result_check = 2.236068;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(RPN_TEST_24) {
  char string[SIZE] = "3.7^8";
  double result = 0;
  double result_check = 35124.7945392;
  int error_check = 0;
  int error = start_calculation(string, 0.0, &result);
  ck_assert_double_eq(result, result_check);
  ck_assert_int_eq(error, error_check);
}
END_TEST

Suite *Main_calc(void) {
  Suite *s = suite_create("\033[45m--- MAIN CALC ---\033[0m");
  TCase *tc1_1 = tcase_create("MAIN CALC: ");

  suite_add_tcase(s, tc1_1);

  tcase_add_test(tc1_1, RPN_TEST_0);
  tcase_add_test(tc1_1, RPN_TEST_1);
  tcase_add_test(tc1_1, RPN_TEST_2);
  tcase_add_test(tc1_1, RPN_TEST_3);
  tcase_add_test(tc1_1, RPN_TEST_4);
  tcase_add_test(tc1_1, RPN_TEST_5);
  tcase_add_test(tc1_1, RPN_TEST_6);
  tcase_add_test(tc1_1, RPN_TEST_7);
  tcase_add_test(tc1_1, RPN_TEST_8);
  tcase_add_test(tc1_1, RPN_TEST_9);
  tcase_add_test(tc1_1, RPN_TEST_10);
  tcase_add_test(tc1_1, RPN_TEST_11);
  tcase_add_test(tc1_1, RPN_TEST_12);
  tcase_add_test(tc1_1, RPN_TEST_13);
  tcase_add_test(tc1_1, RPN_TEST_14);
  tcase_add_test(tc1_1, RPN_TEST_15);
  tcase_add_test(tc1_1, RPN_TEST_16);
  tcase_add_test(tc1_1, RPN_TEST_17);
  tcase_add_test(tc1_1, RPN_TEST_18);
  tcase_add_test(tc1_1, RPN_TEST_19);
  tcase_add_test(tc1_1, RPN_TEST_20);
  tcase_add_test(tc1_1, RPN_TEST_21);
  tcase_add_test(tc1_1, RPN_TEST_22);
  tcase_add_test(tc1_1, RPN_TEST_23);
  tcase_add_test(tc1_1, RPN_TEST_24);

  return s;
}
