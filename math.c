#include <stdint.h>
#include "math.h"

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