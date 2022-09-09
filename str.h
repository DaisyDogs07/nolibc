#include <stdbool.h>
#include <stddef.h>

bool nolibc_isalnum(char);
bool nolibc_isalpha(char);
bool nolibc_isascii(char);
bool nolibc_isblank(char);
bool nolibc_isdigit(char);
bool nolibc_isspace(char);
char nolibc_toascii(char);
char* nolibc_strcat(char*, const char*);
char* nolibc_strncat(char*, const char*, size_t);
char* nolibc_strchr(const char*, char);
int nolibc_strcmp(const char*, const char*);
int nolibc_strncmp(const char*, const char*, size_t);
char* nolibc_strcpy(char*, const char*);
char* nolibc_strncpy(char*, const char*, size_t);
size_t nolibc_strlen(const char*);
size_t nolibc_strnlen(const char*, size_t);
char* nolibc_strdup(const char*);