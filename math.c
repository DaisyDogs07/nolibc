#include <stdint.h>
#include "math.h"

int nolibc_abs(int n) {
  return __builtin_abs(n);
}
long int nolibc_labs(long int n) {
  return __builtin_labs(n);
}
long long int nolibc_llabs(long long int n) {
  return __builtin_llabs(n);
}
double nolibc_fabs(double n) {
  return __builtin_fabs(n);
}
float nolibc_fabsf(float n) {
  return __builtin_fabsf(n);
}
long double nolibc_fabsl(long double n) {
  return __builtin_fabsl(n);
}
double nolibc_fmax(double x, double y) {
  return y < x ? x : y;
}
float nolibc_fmaxf(float x, float y) {
  return y < x ? x : y;
}
long double nolibc_fmaxl(long double x, long double y) {
  return y < x ? x : y;
}
double nolibc_fmin(double x, double y) {
  return x < y ? x : y;
}
float nolibc_fminf(float x, float y) {
  return x < y ? x : y;
}
long double nolibc_fminl(long double x, long double y) {
  return x < y ? x : y;
}
bool nolibc_isinf(double x) {
  return __builtin_isinf(x);
}
bool nolibc_isinff(float x) {
  return __builtin_isinff(x);
}
bool nolibc_isinfl(long double x) {
  return __builtin_isinfl(x);
}
bool nolibc_isnan(double x) {
  return __builtin_isnan(x);
}
bool nolibc_isnanf(float x) {
  return __builtin_isnanf(x);
}
bool nolibc_isnanl(long double x) {
  return __builtin_isnanl(x);
}
double nolibc_sqrt(double x) {
  return __builtin_sqrt(x);
}
float nolibc_sqrtf(float x) {
  return __builtin_sqrtf(x);
}
long double nolibc_sqrtl(long double x) {
  return __builtin_sqrtl(x);
}
long int nolibc_atol(const char* s) {
  long int ret = 0;
  bool neg = *s == '-';
  if (neg || *s == '+')
    ++s;
  char d;
  while ((d = *s++ - '0') <= 9)
    ret = (ret * 10) + d;
  return neg ? -ret : ret;
}
int nolibc_atoi(const char* s) {
  return nolibc_atol(s);
}
double nolibc_floor(double x) {
  bool neg = x < 0.0;
  if (neg)
    x = -x;
  int64_t i0 = *(int64_t*)&x;
  int64_t j0 = ((i0 >> 52) & 0x7ff) - 0x3ff;
  if (j0 < 52) {
    if (j0 < 0) {
      if (i0 >= 0)
        i0 = 0;
      else if ((i0 & 0x7fffffffffffffffl) != 0)
        i0 = 0xbff0000000000000l;
    } else {
      uint64_t i = 0x000fffffffffffffl >> j0;
      if ((i0 & i) == 0)
        return x;
      if (i0 < 0)
        i0 += 0x0010000000000000l >> j0;
      i0 &= ~i;
    }
    if (neg)
      return -*(double*)&i0;
    return *(double*)&i0;
  } else if (j0 == 0x400)
    return x + x;
  return x;
}
float nolibc_floorf(float x) {
  bool neg = x < 0.0f;
  if (neg)
    x = -x;
  int32_t i0 = *(int32_t*)&x;
  int32_t j0 = ((i0 >> 23) & 0xff) - 0x7f;
  if (j0 < 23) {
    if (j0 < 0) {
      if (i0 >= 0)
        i0 = 0;
      else if ((i0 & 0x7fffffff) != 0)
        i0 = 0xbf800000;
    } else {
      uint32_t i = 0x007fffff >> j0;
      if ((i0 & i) == 0)
        return x;
      if (i0 < 0)
        i0 += 0x00800000 >> j0;
      i0 &= ~i;
    }
  } else {
    if (j0 == 0x80)
      return x + x;
    return x;
  }
  if (neg)
    return -*(float*)&i0;
  return *(float*)&i0;
}
double nolibc_frexp(double x, int* eptr) {
  int64_t ix = *(int64_t*)&x;
  int32_t ex = 0x7ff & (ix >> 52);
  int e = 0;
  if (ex != 0x7ff && x != 0.0) {
    e = ex - 1022;
    if (ex == 0) {
      x *= 0x1p54;
      ix = *(int64_t*)&x;
      ex = 0x7ff & (ix >> 52);
      e = ex - 1022 - 54;
    }
    ix = (ix & 0x800fffffffffffffl) | 0x3fe0000000000000l;
    x = *(double*)&ix;
  } else x += x;
  *eptr = e;
  return x;
}
double nolibc_modf(double x, double* iptr) {
  int64_t i0 = *(int64_t*)&x;
  int32_t j0 = ((i0 >> 52) & 0x7ff) - 0x3ff;
  if (j0 < 52) {
    if (j0 < 0) {
      int64_t tmp = i0 & 0x8000000000000000ul;
      *iptr = *(double*)&tmp;
      return x;
    } else {
      uint64_t i = 0x000ffffffffffffful >> j0;
      if ((i0 & i) == 0) {
        *iptr = x;
        int64_t tmp = i0 & 0x8000000000000000ul;
        return *(double*)&tmp;
      } else {
        int64_t tmp = i0 & (~i);
        *iptr = *(double*)&tmp;
        return x - *iptr;
      }
    }
  } else {
    *iptr = x * 1.0;
    if (j0 == 0x400 && (i0 & 0xffffffffffffful))
      return x * 1.0;
    int64_t tmp = i0 & 0x8000000000000000ul;
    return *(double*)&tmp;
  }
}