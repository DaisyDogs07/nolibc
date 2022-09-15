#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

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
int nolibc_strverscmp(const char* s1, const char* s2);
void nolibc_swab(const void* src, void* dest, ssize_t n);