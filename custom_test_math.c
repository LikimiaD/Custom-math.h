#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "custom_math.h"

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define NAME_TEST(X)                                                          \
  printf("%sTesting custom.math.c func called: %scustom_%s%s\n", ANSI_COLOR_YELLOW, \
         ANSI_COLOR_GREEN, X, ANSI_COLOR_RESET);

START_TEST(test_abs) {
  for (int i = -1000; i <= 1000; i++) {
    ck_assert_int_eq(custom_abs(i), abs(i));
  }
  ck_assert_int_eq(custom_abs((int)INFINITY), abs((int)INFINITY));
  ck_assert_int_eq(custom_abs((int)NAN), abs((int)NAN));
  ck_assert_int_eq(custom_abs((int)-INFINITY), abs((int)-INFINITY));
}
END_TEST

START_TEST(test_fabs) {
  for (long double i = -1000.0; i <= 1000.0; i += 0.25) {
    ck_assert_ldouble_eq_tol(custom_fabs(i), fabsl(i), CUSTOM_PRC);
  }
  ck_assert_double_eq(custom_fabs(INFINITY), fabs(INFINITY));
  ck_assert_double_nan(custom_fabs(NAN));
  ck_assert_double_eq(custom_fabs(-INFINITY), fabs(-INFINITY));
}
END_TEST

START_TEST(test_floor) {
  for (double i = -1000.0; i <= 1000.0; i += 0.25) {
    ck_assert_ldouble_eq_tol(custom_floor(i), floor(i), CUSTOM_PRC);
  }
  ck_assert_double_eq(custom_floor(INFINITY), floor(INFINITY));
  ck_assert_double_nan(custom_floor(NAN));
  ck_assert_double_eq(custom_floor(-INFINITY), floor(-INFINITY));
}
END_TEST

START_TEST(test_ceil) {
  for (double i = -1000.0; i <= 1000.0; i += 0.25) {
    ck_assert_ldouble_eq_tol(custom_ceil(i), ceil(i), CUSTOM_PRC);
  }
  ck_assert_double_eq(custom_ceil(INFINITY), ceil(INFINITY));
  ck_assert_double_nan(custom_ceil(NAN));
  ck_assert_double_eq(custom_ceil(-INFINITY), ceil(-INFINITY));
}
END_TEST

START_TEST(test_fmod) {
  for (double i = -100.0; i <= 100.0; i += 0.25) {
    for (double j = -50.0; j <= 50.0; j += 0.25) {
      long double result_custom = custom_fmod(i, j);
      long double result_std = fmod(i, j);

      if (isnan(result_std)) {
        ck_assert(isnan(result_custom));
      } else {
        ck_assert_ldouble_eq_tol(result_custom, result_std, CUSTOM_PRC);
      }
    }
  }
}
END_TEST

START_TEST(test_log) {
  for (double i = -85.0; i <= 85.0; i += 0.25) {
    ck_assert_msg(fabsl(custom_exp(i) - exp(i)) <= CUSTOM_PRC, "Error on base %f", i);
    ;
  }
  ck_assert_double_nan(custom_log(-INFINITY));
  ck_assert_double_nan(custom_log(NAN));
  ck_assert_double_eq(custom_log(INFINITY), log(INFINITY));
}
END_TEST

START_TEST(test_exp) {
  ck_assert_double_eq(custom_exp(INFINITY), exp(INFINITY));
  ck_assert_double_nan(custom_exp(NAN));
  ck_assert_double_nan(exp(NAN));
  ck_assert_double_eq(custom_exp(-INFINITY), exp(-INFINITY));
  for (double i = -75.0; i <= 75.0; i += 0.25) {
    ck_assert_msg(fabsl(custom_exp(i) - exp(i)) <= 0.000001, "Error on base %f",
                  i);
  }
}
END_TEST

START_TEST(test_factorial) {
  ck_assert_ldouble_eq(custom_factorial(0), 1.0);
  ck_assert_ldouble_eq(custom_factorial(1), 1.0);
  ck_assert_ldouble_eq(custom_factorial(5), 120.0);
  ck_assert_ldouble_eq(custom_factorial(10), 3628800.0);
  ck_assert_ldouble_nan(custom_factorial(-1));
  ck_assert_ldouble_nan(custom_factorial(-5));
  ck_assert_ldouble_nan(custom_factorial(-10));
}
END_TEST

START_TEST(test_pow) {
  double bases[] = {2.0, -2.0, 0.0, 1.0, -1.0, 0.5};
  const double exponents[] = {2.0, 3.0, 0.0, -1.0, -2.0, 0.5};
  int num_tests = sizeof(bases) / sizeof(bases[0]);

  for (int i = 0; i < num_tests; i++) {
    double base = bases[i];
    double exponent = exponents[i];
    double expected = pow(base, exponent);
    double result = custom_pow(base, exponent);

    ck_assert_msg(fabsl(result - expected) <= CUSTOM_LDBL_EPSILON,
                  "Error on base %.2f exponent %.2f: custom_pow result %f != "
                  "expected pow result %f",
                  base, exponent, result, expected);
  }
  ck_assert_double_eq(custom_pow(INFINITY, INFINITY), pow(INFINITY, INFINITY));
  ck_assert_double_eq(custom_pow(-INFINITY, -INFINITY), pow(-INFINITY, -INFINITY));
  ck_assert_double_nan(custom_pow(NAN, NAN));
  ck_assert_double_nan(custom_pow(INFINITY, NAN));
  ck_assert_double_nan(custom_pow(NAN, INFINITY));
  ck_assert_double_nan(custom_pow(-INFINITY, NAN));
  ck_assert_double_nan(custom_pow(NAN, -INFINITY));
  ck_assert_double_eq(custom_pow(-INFINITY, INFINITY), pow(-INFINITY, INFINITY));
  ck_assert_double_eq(custom_pow(INFINITY, -INFINITY), pow(INFINITY, -INFINITY));
  ck_assert_double_eq_tol(custom_pow(-INFINITY, 0), pow(-INFINITY, 0), 0.000001);
  ck_assert_double_eq_tol(custom_pow(INFINITY, 0), pow(INFINITY, 0), 0.000001);
  ck_assert_double_eq_tol(custom_pow(NAN, 0), pow(NAN, 0), 0.000001);
  ck_assert_double_eq(custom_pow(0, -INFINITY), pow(0, -INFINITY));
  ck_assert_double_eq_tol(custom_pow(0, INFINITY), pow(0, INFINITY), 0.000001);
  ck_assert_double_nan(custom_pow(0, NAN));
}
END_TEST

START_TEST(test_tan) {
  ck_assert_double_eq_tol(custom_tan(6987000), tan(6987000), 0.000001);
  ck_assert_double_eq_tol(custom_tan(-14.96), tan(-14.96), 0.000001);
  ck_assert_double_nan(custom_tan(INFINITY));
  ck_assert_double_nan(custom_tan(NAN));
  ck_assert_double_nan(custom_tan(-INFINITY));
  ck_assert_double_eq_tol(custom_tan(0), tan(0), 0.000001);
  ck_assert_double_eq_tol(custom_tan(CUSTOM_PI), tan(CUSTOM_PI), 0.000001);
}
END_TEST

START_TEST(test_atan) {
  double test_values[] = {-1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4,
                          -0.3, -0.2, -0.1, 0,    0.1,  0.2,  0.3,
                          0.4,  0.5,  0.6,  0.7,  0.8,  0.9,  1.0};
  int num_tests = sizeof(test_values) / sizeof(test_values[0]);

  for (int i = 0; i < num_tests; i++) {
    long double expected = 0, result = 0;
    double x = test_values[i];
    expected = atan(x);
    result = custom_atan(x);

    ck_assert_msg(fabsl(result - expected) <= CUSTOM_TRG_PRC,
                  "Error on atan(%.2f): custom_atan result %.16Lf != expected "
                  "atan result %.16Lf",
                  x, result, expected);
  }
  ck_assert_double_eq(custom_atan(INFINITY), atan(INFINITY));
  ck_assert_double_nan(custom_atan(NAN));
  ck_assert_double_eq(custom_atan(-INFINITY), atan(-INFINITY));
}
END_TEST

START_TEST(test_acos) {
  double test_values[] = {-1.0, -0.5,    0.0,         0.5,
                          1.0,  CUSTOM_NAN, CUSTOM_INF_NEG, CUSTOM_INF_POS};
  size_t num_values = sizeof(test_values) / sizeof(test_values[0]);
  for (size_t i = 0; i < num_values; i++) {
    double x = test_values[i];
    if (!isnan(x) && x >= -1.0 && x <= 1.0) {
      long double expected = acos(x);
      long double result = custom_acos(x);
      ck_assert_msg(fabsl(result - expected) <= CUSTOM_TRG_PRC,
                    "Error on acos(%.2f): custom_acos result %.10Lf != expected "
                    "acos result %.10Lf",
                    x, result, expected);
    } else if (isnan(x)) {
      ck_assert(isnan(custom_acos(x)));
    } else {
      ck_assert(isnan(custom_acos(x)));
    }
  }
  ck_assert_double_nan(custom_acos(INFINITY));
  ck_assert_double_nan(custom_acos(NAN));
  ck_assert_double_nan(custom_acos(-INFINITY));
}
END_TEST

START_TEST(test_asin) {
  double test_values[] = {-1.0, -0.5,    0.0,         0.5,
                          1.0,  CUSTOM_NAN, CUSTOM_INF_NEG, CUSTOM_INF_POS};
  size_t num_values = sizeof(test_values) / sizeof(test_values[0]);
  for (size_t i = 0; i < num_values; i++) {
    double x = test_values[i];
    if (!isnan(x) && x >= -1.0 && x <= 1.0) {
      long double expected = asin(x);
      long double result = custom_asin(x);
      ck_assert_msg(fabsl(result - expected) <= CUSTOM_TRG_PRC,
                    "Error on asin(%.2f): custom_asin result %.10Lf != expected "
                    "asin result %.10Lf",
                    x, result, expected);
    } else if (isnan(x)) {
      ck_assert(isnan(custom_asin(x)));
    } else {
      ck_assert(isnan(custom_asin(x)));
    }
  }
  ck_assert_double_nan(custom_asin(INFINITY));
  ck_assert_double_nan(custom_asin(NAN));
  ck_assert_double_nan(custom_asin(-INFINITY));
}
END_TEST

START_TEST(test_cos) {
  double test_values[] = {0.0,     CUSTOM_PI / 4,  CUSTOM_PI / 2, CUSTOM_PI,
                          CUSTOM_NAN, CUSTOM_INF_NEG, CUSTOM_INF_POS};
  size_t num_values = sizeof(test_values) / sizeof(test_values[0]);
  for (size_t i = 0; i < num_values; i++) {
    double x = test_values[i];
    if (!isnan(x) && !isinf(x)) {
      long double expected = cos(x);
      long double result = custom_cos(x);
      ck_assert_msg(fabsl(result - expected) <= CUSTOM_TRG_PRC,
                    "Error on cos(%.2f): custom_cos result %.10Lf != expected cos "
                    "result %.10Lf",
                    x, result, expected);
    } else {
      ck_assert(isnan(custom_cos(x)));
    }
  }
  ck_assert_double_eq_tol(custom_cos(1200000), cos(1200000), 0.000001);
  ck_assert_double_eq_tol(custom_cos(-14.96), cos(-14.96), 0.000001);
  ck_assert_double_nan(custom_cos(INFINITY));
  ck_assert_double_nan(custom_cos(NAN));
  ck_assert_double_nan(custom_cos(-INFINITY));
  ck_assert_double_eq_tol(custom_cos(0), cos(0), 0.000001);
  ck_assert_double_eq_tol(custom_cos(CUSTOM_PI), cos(CUSTOM_PI), 0.000001);
  ck_assert_double_eq_tol(custom_cos(-CUSTOM_PI), cos(-CUSTOM_PI), 0.000001);
  ck_assert_double_eq_tol(custom_cos(CUSTOM_PI), cos(CUSTOM_PI), 0.000001);
}
END_TEST

START_TEST(test_sin) {
  double test_values[] = {0.0,     CUSTOM_PI / 4,  CUSTOM_PI / 2, CUSTOM_PI,
                          CUSTOM_NAN, CUSTOM_INF_NEG, CUSTOM_INF_POS};
  size_t num_values = sizeof(test_values) / sizeof(test_values[0]);
  for (size_t i = 0; i < num_values; i++) {
    double x = test_values[i];
    if (!isnan(x) && !isinf(x)) {
      long double expected = sin(x);
      long double result = custom_sin(x);
      ck_assert_msg(fabsl(result - expected) <= CUSTOM_TRG_PRC,
                    "Error on sin(%.2f): custom_sin result %.10Lf != expected sin "
                    "result %.10Lf",
                    x, result, expected);
    } else {
      ck_assert(isnan(custom_sin(x)));
    }
  }
  ck_assert_double_nan(custom_asin(INFINITY));
  ck_assert_double_nan(custom_asin(NAN));
  ck_assert_double_nan(custom_asin(-INFINITY));
}
END_TEST

START_TEST(test_sqrt) {
  double test_values[] = {0.0,  0.5,      1.0, 2.0,       4.0,
                          16.0, INFINITY, NAN, -INFINITY, -231.41};
  size_t num_values = sizeof(test_values) / sizeof(test_values[0]);
  for (size_t i = 0; i < num_values; i++) {
    double x = test_values[i];
    if (!isnan(x) && x >= 0.0 && x != CUSTOM_INF_POS) {
      long double expected = sqrt(x);
      long double result = custom_sqrt(x);
      ck_assert_msg(fabsl(result - expected) <= CUSTOM_TRG_PRC,
                    "Error on sqrt(%.2f): custom_sqrt result %.10Lf != expected "
                    "sqrt result %.10Lf",
                    x, result, expected);
    } else if (isnan(x) || x < 0.0) {
      ck_assert(isnan(custom_sqrt(x)));
    } else if (x == CUSTOM_INF_POS) {
      ck_assert(custom_sqrt(x) == CUSTOM_INF_POS);
    }
  }
  ck_assert_double_eq(custom_sqrt(INFINITY), sqrt(INFINITY));
  ck_assert_double_nan(custom_sqrt(NAN));
  ck_assert_double_nan(custom_sqrt(-INFINITY));
}
END_TEST

Suite *math_suite(void) {
  Suite *s;
  TCase *tc_abs = NULL, *tc_fabs = NULL, *tc_floor = NULL, *tc_ceil = NULL,
        *tc_fmod = NULL, *tc_log = NULL, *tc_exp = NULL, *tc_factorial = NULL,
        *tc_pow = NULL, *tc_atan = NULL, *tc_acos = NULL, *tc_asin = NULL,
        *tc_cos = NULL, *tc_sin = NULL, *tc_sqrt = NULL, *tc_tan = NULL;

  s = suite_create("custom_math");

  NAME_TEST("abs");
  tc_abs = tcase_create("abs");
  tcase_add_test(tc_abs, test_abs);
  suite_add_tcase(s, tc_abs);

  NAME_TEST("fabs");
  tc_fabs = tcase_create("fabs");
  tcase_add_test(tc_fabs, test_fabs);
  suite_add_tcase(s, tc_fabs);

  NAME_TEST("floor");
  tc_floor = tcase_create("floor");
  tcase_add_test(tc_floor, test_floor);
  suite_add_tcase(s, tc_floor);

  NAME_TEST("ceil");
  tc_ceil = tcase_create("ceil");
  tcase_add_test(tc_ceil, test_ceil);
  suite_add_tcase(s, tc_ceil);

  NAME_TEST("fmod");
  tc_fmod = tcase_create("fmod");
  tcase_add_test(tc_fmod, test_fmod);
  suite_add_tcase(s, tc_fmod);

  NAME_TEST("exp");
  tc_exp = tcase_create("exp");
  tcase_add_test(tc_exp, test_exp);
  suite_add_tcase(s, tc_exp);

  NAME_TEST("log");
  tc_log = tcase_create("log");
  tcase_add_test(tc_log, test_log);
  suite_add_tcase(s, tc_log);

  NAME_TEST("factorial");
  tc_factorial = tcase_create("factorial");
  tcase_add_test(tc_factorial, test_factorial);
  suite_add_tcase(s, tc_factorial);

  NAME_TEST("pow");
  tc_pow = tcase_create("pow");
  tcase_add_test(tc_pow, test_pow);
  suite_add_tcase(s, tc_pow);

  NAME_TEST("atan");
  tc_atan = tcase_create("atan");
  tcase_add_test(tc_atan, test_atan);
  suite_add_tcase(s, tc_atan);

  NAME_TEST("acos");
  tc_acos = tcase_create("acos");
  tcase_add_test(tc_acos, test_acos);
  suite_add_tcase(s, tc_acos);

  NAME_TEST("asin");
  tc_asin = tcase_create("asin");
  tcase_add_test(tc_asin, test_asin);
  suite_add_tcase(s, tc_asin);

  NAME_TEST("cos");
  tc_cos = tcase_create("cos");
  tcase_add_test(tc_cos, test_cos);
  suite_add_tcase(s, tc_cos);

  NAME_TEST("sin");
  tc_sin = tcase_create("sin");
  tcase_add_test(tc_sin, test_sin);
  suite_add_tcase(s, tc_sin);

  NAME_TEST("sqrt");
  tc_sqrt = tcase_create("sqrt");
  tcase_add_test(tc_sqrt, test_sqrt);
  suite_add_tcase(s, tc_sqrt);

  NAME_TEST("tan");
  tc_tan = tcase_create("tan");
  tcase_add_test(tc_tan, test_tan);
  suite_add_tcase(s, tc_tan);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = math_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}