#include <stdbool.h>
#include <stdlib.h>

int nolibc_abs(int x);
long nolibc_labs(long x);
long long nolibc_llabs(long long x);
double nolibc_fabs(double x);
float nolibc_fabsf(float x);
long double nolibc_fabsl(long double x);
double nolibc_copysign(double x, double y);
float nolibc_copysignf(float x, float y);
long double nolibc_copysignl(long double x, long double y);
div_t nolibc_div(int numer, int denom);
ldiv_t nolibc_ldiv(long numer, long denom);
lldiv_t nolibc_lldiv(long long numer, long long denom);
double nolibc_fma(double x, double y, double z);
double nolibc_fmod(double x, double y);
double nolibc_frexp(double x, int* exp);
float nolibc_frexpf(float x, int* exp);
long double nolibc_frexpl(long double x, int* exp);
bool nolibc_isinf(double x);
bool nolibc_isnan(double x);
double nolibc_scalbn(double x, int n);
float nolibc_scalbnf(float x, int n);
long double nolibc_scalbnl(long double x, int n);
int nolibc_signbit(double x);
int nolibc_signbitf(float x);
int nolibc_signbitl(long double x);