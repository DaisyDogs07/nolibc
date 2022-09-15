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
    ++str;
  }
  return NULL;
}
int nolibc_strcmp(const char* s1, const char* s2) {
  while (1) {
    char c1 = *s1++;
    char c2 = *s2++;
    if (c1 != c2)
      return c1 - c2;
    if (c1 == '\0')
      break;
  }
  return 0;
}
int nolibc_strncmp(const char* s1, const char* s2, size_t n) {
  while (n--) {
    char c1 = *s1++;
    char c2 = *s2++;
    if (c1 != c2)
      return c1 - c2;
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
char* nolibc_strdup(const char* str) {
  size_t len = nolibc_strlen(str);
  char* ret = (char*)nolibc_malloc(len + 1);
  nolibc_memcpy(ret, str, len);
  ret[len] = '\0';
  return ret;
}
char* nolibc_strndup(const char* str, size_t n) {
  size_t len = nolibc_strnlen(str, n);
  char* ret = (char*)nolibc_malloc(len + 1);
  nolibc_memcpy(ret, str, len);
  ret[len] = '\0';
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
char* nolibc_strpbrk(const char* str, const char* accept) {
  str += nolibc_strcspn(str, accept);
  return *str ? (char*)str : NULL;
}
char* nolibc_strsep(char** str, const char* dilem) {
  char* ret = *str;
  if (!ret)
    return NULL;
  size_t len = nolibc_strcspn(ret, dilem);
  if (ret[len] == '\0')
    *str = NULL;
  else {
    ret[len] = '\0';
    *str = ret + len + 1;
  }
  return ret;
}
size_t nolibc_strspn(const char* str, const char* accept) {
  size_t ret = 0;
  while (*str && nolibc_strchr(accept, *str++))
    ++ret;
  return ret;
}
size_t nolibc_strcspn(const char* str, const char* reject) {
  size_t ret = 0;
  while (*str && !nolibc_strchr(reject, *str++))
    ++ret;
  return ret;
}
char* nolibc_strstr(const char* str, const char* substr) {
  size_t len = nolibc_strlen(substr);
  while (*str) {
    if (nolibc_strncmp(str, substr, len) == 0)
      return (char*)str;
    ++str;
  }
  return NULL;
}
char* nolibc_strtok_r(char* str, const char* delim, char** saveptr) {
  if (!str)
    str = *saveptr;
  str += nolibc_strspn(str, delim);
  if (*str == '\0')
    return NULL;
  char* ret = str;
  str += nolibc_strcspn(str, delim);
  if (*str == '\0')
    *saveptr = str;
  else {
    *str = '\0';
    *saveptr = str + 1;
  }
  return ret;
}
char* nolibc_strtok(char* str, const char* delim) {
  static char* last;
  return nolibc_strtok_r(str, delim, &last);
}
int nolibc_strverscmp(const char* s1, const char* s2) {
  while (1) {
    char c1 = *s1++;
    char c2 = *s2++;
    if (c1 != c2) {
      if (c1 == '\0' || c2 == '\0')
        return c1 - c2;
      if (__builtin_isdigit(c1) && __builtin_isdigit(c2)) {
        int i1 = c1 - '0';
        int i2 = c2 - '0';
        while (__builtin_isdigit(*s1))
          i1 = i1 * 10 + *s1++ - '0';
        while (__builtin_isdigit(*s2))
          i2 = i2 * 10 + *s2++ - '0';
        if (i1 != i2)
          return i1 - i2;
      } else return c1 - c2;
    } else if (c1 == '\0')
      break;
  }
  return 0;
}
void nolibc_swab(const void* src, void* dest, ssize_t n) {
  const char* s = (const char*)src;
  char* d = (char*)dest;
  while (n > 1) {
    char c = *s++;
    *d++ = *s++;
    *d++ = c;
    n -= 2;
  }
}