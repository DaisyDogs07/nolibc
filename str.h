#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

char* nolibc_basename(const char* path);
char* nolibc_dirname(const char* path);
bool nolibc_isalnum(char c);
bool nolibc_isalpha(char c);
bool nolibc_isascii(char c);
bool nolibc_isblank(char c);
bool nolibc_iscntrl(char c);
bool nolibc_isdigit(char c);
bool nolibc_isgraph(char c);
bool nolibc_islower(char c);
bool nolibc_isupper(char c);
bool nolibc_isprint(char c);
bool nolibc_ispunct(char c);
bool nolibc_isspace(char c);
bool nolibc_isxdigit(char c);
char nolibc_tolower(char c);
char nolibc_toupper(char c);
char nolibc_toascii(char c);
char* nolibc_strcat(char* dest, const char* src);
char* nolibc_strncat(char* dest, const char* src, size_t n);
char* nolibc_strchr(const char* str, char c);
char* nolibc_strrchr(const char* str, char c);
int nolibc_strcmp(const char* s1, const char* s2);
int nolibc_strncmp(const char* s1, const char* s2, size_t n);
char* nolibc_strcpy(char* dest, const char* src);
char* nolibc_strncpy(char* dest, const char* src, size_t n);
char* nolibc_strdup(const char* str);
char* nolibc_strndup(const char* str, size_t n);
size_t nolibc_strlen(const char* str);
size_t nolibc_strnlen(const char* str, size_t n);
char* nolibc_strpbrk(const char* str, const char* accept);
char* nolibc_strsep(char** str, const char* dilem);
size_t nolibc_strspn(const char* str, const char* accept);
size_t nolibc_strcspn(const char* str, const char* reject);
char* nolibc_strstr(const char* str, const char* substr);
char* nolibc_strtok_r(char* str, const char* delim, char** saveptr);
char* nolibc_strtok(char* str, const char* delim);
double nolibc_strtod(const char* str, char** endptr);
float nolibc_strtof(const char* str, char** endptr);
long double nolibc_strtold(const char* str, char** endptr);
long nolibc_strtol(const char* str, char** endptr, int base);
long long nolibc_strtoll(const char* str, char** endptr, int base);
unsigned long nolibc_strtoul(const char* str, char** endptr, int base);
unsigned long long nolibc_strtoull(const char* str, char** endptr, int base);
int nolibc_strverscmp(const char* s1, const char* s2);