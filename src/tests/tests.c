#include <check.h>
#include "../smart_calc_v1/smart_calc_v1.h"

START_TEST(test_smart_calc_1) {
  char *string =
      "15.0/(7.0-(1.0+1.0))*3.0-(2.0+(1.0+1.0))*15.0/"
      "(7.0-(200.0+1.0))*3.0-(2.0+(1.0+1.0))*(15.0/"
      "(7.0-(1.0+1.0))*3.0-(2.0+(1.0+1.0))+15.0/"
      "(7.0-(1.0+1.0))*3.0-(2.0+(1.0+1.0)))\0";
  double result = 15.0 / (7.0 - (1.0 + 1.0)) * 3.0 -
                  (2.0 + (1.0 + 1.0)) * 15.0 / (7.0 - (200.0 + 1.0)) * 3.0 -
                  (2.0 + (1.0 + 1.0)) *
                      (15.0 / (7.0 - (1.0 + 1.0)) * 3.0 - (2.0 + (1.0 + 1.0)) +
                       15.0 / (7.0 - (1.0 + 1.0)) * 3.0 - (2.0 + (1.0 + 1.0)));
  double resultPN = 1.0;
  calculatePN(string, &resultPN, 1.0);
  ck_assert_double_eq(resultPN, result);
}
END_TEST

START_TEST(test_smart_calc_2) {
  char *string = "sqrt(3)-1/2*sin(3^2-2)\0";
  double result = sqrt(3.0) - 1.0 / 2.0 * sin(pow(3.0, 2.0) - 2.0);
  double resultPN = 1.0;
  calculatePN(string, &resultPN, 1.0);
  ck_assert_double_eq(resultPN, result);
}
END_TEST

START_TEST(test_smart_calc_3) {
  char *string = "sqrt(3+2*(1-cos(77)^2))\0";
  double result = sqrt(3.0 + 2.0 * (1.0 - pow(cos(77.0), 2.0)));
  double resultPN = 1.0;
  calculatePN(string, &resultPN, 1.0);
  ck_assert_double_eq(resultPN, result);
}
END_TEST

START_TEST(test_smart_calc_4) {
  char *string = "tan(0.0)\0";
  double result = tan(0.0);
  double resultPN = 1.0;
  calculatePN(string, &resultPN, 1.0);
  ck_assert_double_eq(resultPN, result);
}
END_TEST

START_TEST(test_smart_calc_5) {
  char *string = "ln(-1.0)\0";
  double resultPN = 1.0;
  ck_assert_int_eq(ERROR, calculatePN(string, &resultPN, 1.0));
}
END_TEST

START_TEST(test_smart_calc_6) {
  char *string = "20/0\0";
  double resultPN = 1.0;
  ck_assert_int_eq(INFNTY, calculatePN(string, &resultPN, 1.0));
}
END_TEST

START_TEST(test_smart_calc_7) {
  char *string = "sqrt(-1.0)\0";
  double resultPN = 1.0;
  ck_assert_int_eq(ERROR, calculatePN(string, &resultPN, 1.0));
}
END_TEST

START_TEST(test_smart_calc_8) {
  char *string = "cos(3*pi*e)\0";
  double result = cos(3 * M_PI * M_E);
  double resultPN = 1.0;
  calculatePN(string, &resultPN, 1.0);
  ck_assert_double_eq(resultPN, result);
}
END_TEST

START_TEST(test_smart_calc_9) {
  char *string = "asin(3*x/pi)\0";
  double result = asin(3 * 0.85 / M_PI);
  double resultPN = 1.0;
  calculatePN(string, &resultPN, 0.85);
  ck_assert_double_eq(resultPN, result);
}
END_TEST

START_TEST(test_smart_calc_10) {
  char *string = "acos(3*x/pi)\0";
  double result = acos(3 * 0.85 / M_PI);
  double resultPN = 1.0;
  calculatePN(string, &resultPN, 0.85);
  ck_assert_double_eq(resultPN, result);
}
END_TEST

START_TEST(test_smart_calc_11) {
  char *string = "atan(3*x/pi)\0";
  double result = atan(3 * 0.85 / M_PI);
  double resultPN = 1.0;
  calculatePN(string, &resultPN, 0.85);
  ck_assert_double_eq(resultPN, result);
}
END_TEST

START_TEST(test_smart_calc_12) {
  char *string = "log(94%3.2321321)\0";
  double result = log10(fmod(94, 3.2321321));
  double resultPN = 1.0;
  calculatePN(string, &resultPN, 0.85);
  ck_assert_double_eq(resultPN, result);
}
END_TEST

START_TEST(test_smart_calc_13) {
  char *string = "tan(pi /2)\0";
  double result = tan(M_PI / 2);
  double resultPN = 1.0;
  calculatePN(string, &resultPN, 0.85);
  ck_assert_double_eq(resultPN, result);
}
END_TEST

Suite *smart_calc_v1(void) {
  Suite *s = suite_create("\033[0;1;36mSmartCalcV1.0\033[0m");
  TCase *tc = tcase_create("smart");
  tcase_add_test(tc, test_smart_calc_1);
  tcase_add_test(tc, test_smart_calc_2);
  tcase_add_test(tc, test_smart_calc_3);
  tcase_add_test(tc, test_smart_calc_4);
  tcase_add_test(tc, test_smart_calc_5);
  tcase_add_test(tc, test_smart_calc_6);
  tcase_add_test(tc, test_smart_calc_7);
  tcase_add_test(tc, test_smart_calc_8);
  tcase_add_test(tc, test_smart_calc_9);
  tcase_add_test(tc, test_smart_calc_10);
  tcase_add_test(tc, test_smart_calc_11);
  tcase_add_test(tc, test_smart_calc_12);
  tcase_add_test(tc, test_smart_calc_13);
  suite_add_tcase(s, tc);
  return s;
}

int main() {
  int failed = 0;
  Suite *suites_list[] = {smart_calc_v1(), NULL};
  for (int i = 0; suites_list[i] != NULL; i++) {
    SRunner *sr = srunner_create(suites_list[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("\n");
  }
  printf("\033[0;1;31mFAILED: %d\033[0m\n", failed);
  return failed == 0 ? 0 : 1;
}
