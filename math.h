#include <stdbool.h>

int nolibc_abs(int);
long int nolibc_labs(long int);
long long int nolibc_llabs(long long int);
double nolibc_fabs(double);
float nolibc_fabsf(float);
long double nolibc_fabsl(long double);
double nolibc_fmax(double, double);
float nolibc_fmaxf(float, float);
long double nolibc_fmaxl(long double, long double);
double nolibc_fmin(double, double);
float nolibc_fminf(float, float);
long double nolibc_fminl(long double, long double);
bool nolibc_isinf(double);
bool nolibc_isinff(float);
bool nolibc_isinfl(long double);
bool nolibc_isnan(double);
bool nolibc_isnanf(float);
bool nolibc_isnanl(long double);
double nolibc_sqrt(double);
float nolibc_sqrtf(float);
long double nolibc_sqrtl(long double);
long int nolibc_atol(const char*);
int nolibc_atoi(const char*);
double nolibc_floor(double);
float nolibc_floorf(float);
double nolibc_frexp(double, int*);
double nolibc_modf(double, double*);