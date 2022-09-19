#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

char* nolibc_basename(const char* path);
char* nolibc_dirname(const char* path);
bool nolibc_isalnum(char c) {
  return __builtin_isdigit(c) || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
bool nolibc_isalpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
bool nolibc_isascii(char c) {
  return !(c & ~0x7F);
}
bool nolibc_isblank(char c) {
  return c == ' ' || c == '\t';
}
bool nolibc_iscntrl(char c) {
  return !(c & ~0x1F) || c == 0x7F;
}
bool nolibc_isdigit(char c) {
  return __builtin_isdigit(c);
}
bool nolibc_isgraph(char c) {
  return c >= 0x21 && c <= 0x7E;
}
bool nolibc_islower(char c) {
  return c >= 'a' && c <= 'z';
}
bool nolibc_isupper(char c) {
  return c >= 'A' && c <= 'Z';
}
bool nolibc_isprint(char c) {
  return c >= 0x20 && c <= 0x7E;
}
bool nolibc_ispunct(char c) {
  return (c >= 0x21 && c <= 0x2F) ||
    (c >= 0x3A && c <= 0x40) ||
    (c >= 0x5B && c <= 0x60) ||
    (c >= 0x7B && c <= 0x7E);
}
bool nolibc_isspace(char c) {
  return (c >= 0x09 && c <= 0x0D) || c == 0x20;
}
bool nolibc_isxdigit(char c) {
  return __builtin_isxdigit(c);
}
char nolibc_tolower(char c) {
  return c >= 'A' && c <= 'Z' ? c + 0x20 : c;
}
char nolibc_toupper(char c) {
  return c >= 'a' && c <= 'z' ? c - 0x20 : c;
}
char nolibc_toascii(char c) {
  return c & 0x7F;
}
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
int nolibc_strverscmp(const char* s1, const char* s2);