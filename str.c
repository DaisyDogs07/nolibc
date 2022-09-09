#include "str.h"
#include "mem.h"

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
bool nolibc_isdigit(char c) {
  return __builtin_isdigit(c);
}
bool nolibc_isspace(char c) {
  return c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f' || c == '\r';
}
char nolibc_toascii(char c) {
  return c & 0x7F;
}
char* nolibc_strcat(char* dest, const char* src) {
  char* ret = dest;
  dest += nolibc_strlen(dest);
  while ((*dest++ = *src++));
  return ret;
}
char* nolibc_strncat(char* dest, const char* src, size_t n) {
  char* ret = dest;
  dest += nolibc_strlen(dest);
  while (n-- && (*dest++ = *src++));
  return ret;
}
char* nolibc_strchr(const char* str, char c) {
  while (*str) {
    if (*str == c)
      return (char*)str;
    str++;
  }
  return (char*)0;
}
int nolibc_strcmp(const char* s1, const char* s2) {
  while (true) {
    char c1 = *s1++;
    char c2 = *s2++;
    if (c1 != c2)
      return c1 < c2 ? -1 : 1;
    if (c1 == '\0')
      break;
  }
  return 0;
}
int nolibc_strncmp(const char* s1, const char* s2, size_t n) {
  for (size_t i = 0; i != n; ++i) {
    char c1 = *s1++;
    char c2 = *s2++;
    if (c1 != c2)
      return c1 < c2 ? -1 : 1;
    if (c1 == '\0')
      break;
  }
  return 0;
}
char* nolibc_strcpy(char* dest, const char* src) {
  char* ret = dest;
  while ((*dest++ = *src++));
  return ret;
}
char* nolibc_strncpy(char* dest, const char* src, size_t n) {
  char* ret = dest;
  while (n-- && (*dest++ = *src++));
  return ret;
}
size_t nolibc_strlen(const char* str) {
  size_t i = 0;
  while (*str++) ++i;
  return i;
}
size_t nolibc_strnlen(const char* str, size_t n) {
  size_t i = 0;
  while (i != n && *str++) ++i;
  return i;
}
char* nolibc_strdup(const char* str) {
  size_t len = nolibc_strlen(str);
  char* ret = (char*)nolibc_malloc(len + 1);
  nolibc_memcpy(ret, str, len);
  ret[len] = '\0';
  return ret;
}