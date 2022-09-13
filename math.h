#include <stdbool.h>

int nolibc_abs(int n);
long int nolibc_labs(long int n);
long long int nolibc_llabs(long long int n);
double nolibc_fabs(double n);
float nolibc_fabsf(float n);
long double nolibc_fabsl(long double n);
double nolibc_fmax(double x, double y);
float nolibc_fmaxf(float x, float y);
long double nolibc_fmaxl(long double x, long double y);
double nolibc_fmin(double x, double y);
float nolibc_fminf(float x, float y);
long double nolibc_fminl(long double x, long double y);
bool nolibc_isinf(double x);
bool nolibc_isinff(float x);
bool nolibc_isinfl(long double x);
bool nolibc_isnan(double x);
bool nolibc_isnanf(float x);
bool nolibc_isnanl(long double x);
double nolibc_sqrt(double x);
float nolibc_sqrtf(float x);
long double nolibc_sqrtl(long double x);
long int nolibc_atol(const char* s);
int nolibc_atoi(const char* s);
double nolibc_floor(double x);
float nolibc_floorf(float x);
double nolibc_frexp(double x, int* eptr);
double nolibc_modf(double x, double* iptr);