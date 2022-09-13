#include <stdbool.h>
#include <stddef.h>

bool nolibc_isalnum(char c);
bool nolibc_isalpha(char c);
bool nolibc_isascii(char c);
bool nolibc_isblank(char c);
bool nolibc_isdigit(char c);
bool nolibc_isspace(char c);
char nolibc_toascii(char c);
char* nolibc_strcat(char* dest, const char* src);
char* nolibc_strncat(char* dest, const char* src, size_t n);
char* nolibc_strchr(const char* str, char c);
int nolibc_strcmp(const char* s1, const char* s2);
int nolibc_strncmp(const char* s1, const char* s2, size_t n);
char* nolibc_strcpy(char* dest, const char* src);
char* nolibc_strncpy(char* dest, const char* src, size_t n);
size_t nolibc_strlen(const char* str);
size_t nolibc_strnlen(const char* str, size_t n);
char* nolibc_strdup(const char* str);