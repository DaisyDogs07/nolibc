#include <stdbool.h>
#include <stdlib.h>

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
long int nolibc_atol(const char* s);
int nolibc_atoi(const char* s) {
  return nolibc_atol(s);
}
double nolibc_copysign(double x, double y) {
  return __builtin_copysign(x, y);
}
float nolibc_copysignf(float x, float y) {
  return __builtin_copysignf(x, y);
}
long double nolibc_copysignl(long double x, long double y) {
  return __builtin_copysignl(x, y);
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
div_t nolibc_div(int numer, int denom) {
  div_t ret;
  ret.quot = numer / denom;
  ret.rem = numer % denom;
  return ret;
}
ldiv_t nolibc_ldiv(long int numer, long int denom) {
  ldiv_t ret;
  ret.quot = numer / denom;
  ret.rem = numer % denom;
  return ret;
}
lldiv_t nolibc_lldiv(long long int numer, long long int denom) {
  lldiv_t ret;
  ret.quot = numer / denom;
  ret.rem = numer % denom;
  return ret;
}
double nolibc_floor(double x) {
  return __builtin_floor(x);
}
float nolibc_floorf(float x) {
  return __builtin_floorf(x);
}
long double nolibc_floorl(long double x) {
  return __builtin_floorl(x);
}
double nolibc_frexp(double x, int* eptr);
double nolibc_modf(double x, double* iptr);