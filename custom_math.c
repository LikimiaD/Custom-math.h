#include "custom_math.h"

int custom_abs(int x) { return x < 0 ? -x : x; }

long double custom_fabs(double x) {
  long double long_x = (long double)x;
  if (long_x < 0.0) {
    long_x *= -1;
  }
  return long_x;
}

long double custom_fabsl(long double x) {
  long double long_x = (long double)x;
  if (long_x < 0.0) {
    long_x *= -1;
  }
  return long_x;
}

long double custom_factorial(int x) {
  if (x < 0) {
    return CUSTOM_NAN;
  }
  long double result = 1;
  for (int i = 2; i <= x; ++i) {
    result *= i;
  }
  return result;
}

long double custom_floor(double x) {
  if (CUSTOM_IS_NAN(x) || x == CUSTOM_INF_NEG || x == CUSTOM_INF_POS) return x;
  long double answer = 0.0;
  if (x >= 0 || (long)x == x) {
    answer = (long)x;
  } else {
    answer = (long)(x - 1);
  }
  return answer;
}

long double custom_ceil(double x) {
  if (CUSTOM_IS_NAN(x) || x == CUSTOM_INF_NEG || x == CUSTOM_INF_POS) return x;
  long double answer = 0.0;
  if (x <= 0 || (long)x == x) {
    answer = (long)x;
  } else {
    answer = (long)x + 1;
  }
  return answer;
}

long double custom_fmod(double x, double y) {
  long double answer = CUSTOM_NAN;
  if (y != 0.0) {
    long double trash = x / y;
    trash = (trash > 0.0) ? custom_floor(trash) : custom_ceil(trash);
    answer = x - trash * y;
  }
  return answer;
}

long double custom_pow(double base, double exp) {
  if (!exp) return 1;
  if (base == CUSTOM_INF_NEG && exp == CUSTOM_INF_NEG) return 0;
  if (base == CUSTOM_INF_NEG && exp == CUSTOM_INF_POS) return CUSTOM_INF_POS;
  if (base < 0 && exp != (long long int)exp) return CUSTOM_NAN;
  long double lbase = (long double)base, lexp = (long double)exp;
  long double res = 1.0;
  if (lexp == 0 || lbase == 1) {
    res = 1.0;
  } else if (lbase == -1 && (lexp == CUSTOM_INF_POS || lexp == CUSTOM_INF_NEG)) {
    res = 1.0;
  } else if ((long long)lexp == lexp) {
    if (lexp < 0) {
      lbase = 1.0 / lbase;
      lexp = -lexp;
    }
    while (lexp > 0) {
      if ((int)custom_fmod(lexp, 2) == 1) {
        res *= lbase;
      }
      lbase *= lbase;
      lexp /= 2;
    }
  } else if (base < 0) {
    res = CUSTOM_NAN;
  } else {
    res = custom_exp(custom_log(lbase) * lexp);
  }
  return res;
}

long double custom_acos(double x) {
  if (x < -1.0 || x > 1.0) {
    return CUSTOM_NAN;
  }
  if (x == 1.0) {
    return 0.0;
  }
  if (x == -1.0) {
    return CUSTOM_PI;
  }
  long double current_sum = CUSTOM_PI / 2;
  long double tmp = x;
  long double fact_numerator = 1;
  long double fact_denominator = 1;
  int iter = 0;
  int max_iter = 1000;
  do {
    if (iter > 0) {
      fact_numerator *= (2 * iter) * (2 * iter - 1);
      fact_denominator *= iter * iter * 4;
      tmp = custom_pow(x, 2 * iter + 1) / (2 * iter + 1);
      tmp *= fact_numerator / fact_denominator;
    }
    current_sum -= tmp;
    iter++;
  } while (custom_fabs(tmp) > CUSTOM_TRG_PRC && iter < max_iter);
  return current_sum;
}

long double custom_asin(double x) {
  if (x < -1.0 || x > 1.0) {
    return CUSTOM_NAN;
  }
  if (x == -1.0) {
    return -CUSTOM_PI / 2;
  }
  if (x == 1.0) {
    return CUSTOM_PI / 2;
  }
  int terms = 50;
  long double asin_result = 0.0;
  for (int i = 0; i < terms; i++) {
    long double factorial_i_squared;
    factorial_i_squared = custom_factorial(i) * custom_factorial(i);
    asin_result +=
        (custom_factorial(2 * i) / (custom_pow(4, i) * factorial_i_squared)) *
        (custom_pow(x, 2 * i + 1) / (2 * i + 1));
  }
  return asin_result;
}

long double custom_atan(double x) {
  if (x == CUSTOM_INF_POS) return CUSTOM_PI / 2;
  if (x == CUSTOM_INF_NEG) return -CUSTOM_PI / 2;
  if (x != x) return x;
  if (x == 1) return CUSTOM_ATAN_ONE_PLUS;
  if (x == -1) return CUSTOM_ATAN_ONE_MINUS;
  int is_in_range = (x > -1 && x < 1);
  long double res = is_in_range ? x : 1.0 / x;
  long double x_pow = x;
  long double term = CUSTOM_INF_POS;
  int sign = -1;
  for (int i = 3; custom_fabsl(term) > CUSTOM_PRC || i == 3; i += 2) {
    x_pow *= x * x;
    term = x_pow / i;
    res += sign * term;
    sign = -sign;
  }

  if (!is_in_range) {
    res = (CUSTOM_PI / 2) * (x / custom_fabs(x)) - res;
  }

  return res;
}

long double custom_cos(double x) {
  const int terms = 50;
  long double cos = 1.0;
  long double term = 1.0;
  x = custom_fmod(x, CUSTOM_PI * 2);

  if (x < 0) {
    x += CUSTOM_PI * 2;
  }

  for (int i = 1; i < terms; i++) {
    term *= (-1) * x * x / ((2 * i - 1) * (2 * i));
    cos += term;
  }
  return cos;
}

long double custom_sin(const double x) {
  long double base = (long double)x;
  int shifted = custom_trg_norm(&base);
  long double res = base;
  long double term = base;
  for (int i = 2; custom_fabs(term) > CUSTOM_TRG_PRC; i += 2) {
    term *= (base * -base) / (i * i + i);
    res += term;
  }
  if (shifted) res *= -1;
  return res;
}

long double custom_exp(double x) {
  long double exp_res = 1;
  long double add = 1;
  long double i = 1;
  int flag = 0;
  int iters = 0;
  if (x < 0) {
    x = custom_fabs(x);
    flag = 1;
  }
  while (custom_fabsl(add) > 1e-17 && iters != 300) {
    add *= x / i;
    i++;
    exp_res += add;
    iters++;
  }
  if (flag == 1) {
    exp_res = (long double)1 / exp_res;
  }
  double exp_fix = (double)exp_res;
  exp_res = (long double)exp_fix;
  return exp_res;
}

long double custom_log(double x) {
  if (x < 0) return CUSTOM_NAN;
  if (x == 0) return CUSTOM_INF_NEG;
  if (x == CUSTOM_INF_POS) return CUSTOM_INF_POS;
  if (x == 1) return 0;
  long double base = (long double)x;
  long double res = 0.0;
  int power = 0;
  while (base >= CUSTOM_E) {
    base /= CUSTOM_E;
    power++;
  }
  while (base < 1 / CUSTOM_E) {
    base *= CUSTOM_E;
    power--;
  }
  for (int i = 0; i < 100; i++) {
    long double exp_res = custom_exp(res);
    res += 2 * (base - exp_res) / (base + exp_res);
  }

  return res + power;
}

long double custom_sqrt(double x) {
  if (CUSTOM_IS_NAN(x)) return CUSTOM_NAN;
  if (x < 0) return CUSTOM_NAN;
  if ((x == CUSTOM_INF_POS || x == CUSTOM_INF_NEG) && x > 0) return CUSTOM_INF_POS;
  if (x == 0) return 0;

  long double xn = x;
  long double xn1 = (x + 1) / 2.0;
  while (custom_fabsl(xn1 - xn) > CUSTOM_LDBL_EPSILON) {
    xn = xn1;
    xn1 = (xn + x / xn) / 2.0;
  }
  return xn1;
}

long double custom_tan(double x) {
  x = custom_fmod(x, CUSTOM_PI);
  return (custom_cos(x) == 0) ? CUSTOM_NAN : custom_sin(x) / custom_cos(x);
}

int custom_trg_norm(long double *phi) {
  int shifted = 0;
  *phi = custom_fmod(*phi, 2 * CUSTOM_PI);
  if (*phi > CUSTOM_PI) {
    *phi -= CUSTOM_PI;
    shifted = 1;
  }
  return shifted;
}