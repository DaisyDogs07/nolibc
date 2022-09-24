#include <stdint.h>
#include "math.h"

int nolibc_abs(int x) {
  return x < 0 ? -x : x;
}
long nolibc_labs(long x) {
  return x < 0 ? -x : x;
}
long long nolibc_llabs(long long x) {
  return x < 0 ? -x : x;
}
double nollibc_fabs(double x) {
  return x < 0 ? -x : x;
}
float nolibc_fabsf(float x) {
  return x < 0 ? -x : x;
}
long double nolibc_fabsl(long double x) {
  return x < 0 ? -x : x;
}
double nolibc_ceil(double x) {
  return __builtin_ceil(x);
}
float nolibc_ceilf(float x) {
  return __builtin_ceilf(x);
}
long double nolibc_ceill(long double x) {
  return __builtin_ceill(x);
}
double nolibc_copysign(double x, double y) {
  return y < 0 ? -x : x;
}
float nolibc_copysignf(float x, float y) {
  return y < 0 ? -x : x;
}
long double nolibc_copysignl(long double x, long double y) {
  return y < 0 ? -x : x;
}
div_t nolibc_div(int numer, int denom) {
  div_t ret;
  ret.quot = numer / denom;
  ret.rem = numer % denom;
  return ret;
}
ldiv_t nolibc_ldiv(long numer, long denom) {
  ldiv_t ret;
  ret.quot = numer / denom;
  ret.rem = numer % denom;
  return ret;
}
lldiv_t nolibc_lldiv(long long numer, long long denom) {
  lldiv_t ret;
  ret.quot = numer / denom;
  ret.rem = numer % denom;
  return ret;
}
double nolibc_fma(double x, double y, double z) {
  return x * y + z;
}
double nolibc_frexp(double x, int* exp) {
  *exp = 0;
  if (x == 0.0)
    return 0.0;
  if (x < 0.5) {
    do {
      x *= 2;
      *exp -= 1;
    } while (x < 0.5);
  } else if (x >= 1.0) {
    do {
      x /= 2;
      *exp += 1;
    } while (x >= 1.0);
  }
  return x;
}
float nolibc_frexpf(float x, int* exp) {
  *exp = 0;
  if (x == 0.0f)
    return 0.0f;
  if (x < 0.5f) {
    do {
      x *= 2;
      *exp -= 1;
    } while (x < 0.5f);
  } else if (x >= 1.0f) {
    do {
      x /= 2;
      *exp += 1;
    } while (x >= 1.0f);
  }
  return x;
}
long double nolibc_frexpl(long double x, int* exp) {
  *exp = 0;
  if (x == 0.0l)
    return 0.0l;
  if (x < 0.5l) {
    do {
      x *= 2;
      *exp -= 1;
    } while (x < 0.5l);
  } else if (x >= 1.0l) {
    do {
      x /= 2;
      *exp += 1;
    } while (x >= 1.0l);
  }
  return x;
}
bool nolibc_isinf(double x) {
  return nolibc_fabs(x) == 1.0 / 0.0;
}
bool nolibc_isnan(double x) {
  return x != x;
}
double nolibc_modf(double x, double* iptr) {
  *iptr = nolibc_trunc(x);
  return x - *iptr;
}
double nolibc_scalbn(double x, int n) {
  return x * (1 << n);
}
float nolibc_scalbnf(float x, int n) {
  return x * (1 << n);
}
long double nolibc_scalbnl(long double x, int n) {
  return x * (1 << n);
}
bool nolibc_signbit(double x) {
  return x < 0;
}
double nolibc_trunc(double x) {
  return __builtin_trunc(x);
}