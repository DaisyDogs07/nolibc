#include "str.h"
#include "mem.h"
#include "sys.h"

char* nolibc_basename(const char* path) {
  char* p = nolibc_strrchr(path, '/');
  return p ? p + 1 : (char*)path;
}
char* nolibc_dirname(const char* path) {
  static const char dot[] = ".";
  char* last_slash = path ? nolibc_strrchr(path, '/') : NULL;
  if (last_slash && last_slash != path && last_slash[1] == '\0') {
    char* runp = last_slash;
    for (;runp != path; --runp)
      if (runp[-1] != '/')
        break;
      if (runp != path)
        last_slash = nolibc_memrchr(path, '/', runp - path);
  }
  if (last_slash) {
    char* runp = last_slash;
    for (;runp != path; --runp)
      if (runp[-1] != '/')
        break;
    if (runp == path) {
      if (last_slash == path + 1)
        ++last_slash;
      else last_slash = (char*)path + 1;
    } else last_slash = runp;
    last_slash[0] = '\0';
  } else path = dot;
  return (char*)path;
}
bool nolibc_isalnum(char c) {
  return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
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
  return c >= '0' && c <= '9';
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
  return c >= '0' && c <= '9' ||
    c >= 'a' && c <= 'f' ||
    c >= 'A' && c <= 'F';
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
char* nolibc_strrchr(const char* str, char c) {
  char* ret = NULL;
  while (*str) {
    if (*str == c)
      ret = (char*)str;
    ++str;
  }
  return ret;
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
int nolibc_strcasecmp(const char* s1, const char* s2) {
  while (1) {
    char c1 = nolibc_tolower(*s1++);
    char c2 = nolibc_tolower(*s2++);
    if (c1 != c2)
      return c1 - c2;
    if (c1 == '\0')
      break;
  }
  return 0;
}
int nolibc_strncasecmp(const char* s1, const char* s2, size_t n) {
  while (n--) {
    char c1 = nolibc_tolower(*s1++);
    char c2 = nolibc_tolower(*s2++);
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
double nolibc_atof(const char* str) {
  return nolibc_strtod(str, (char**)NULL);
}
int nolibc_atoi(const char* str) {
  return nolibc_strtol(str, (char**)NULL, 10);
}
long nolibc_atol(const char* str) {
  return nolibc_strtol(str, (char**)NULL, 10);
}
long long nolibc_atoll(const char* str) {
  return nolibc_strtoll(str, (char**)NULL, 10);
}
double nolibc_strtod(const char* str, char** endptr) {
  double ret = 0.0;
  int sign = 1;
  while (*str == ' ' || *str == '\t')
    ++str;
  if (*str == '-') {
    sign = -1;
    ++str;
  } else if (*str == '+')
    ++str;
  if (*str == 'i' || *str == 'I') {
    char* tmp = nolibc_strdup(str);
    for (int i = 0; tmp[i]; ++i)
      tmp[i] = nolibc_tolower(tmp[i]);
    if (nolibc_strncmp(tmp, "inf", 3) == 0) {
      nolibc_free(tmp);
      return (1.0 * sign) / 0.0;
    }
    nolibc_free(tmp);
  } else if (*str == 'n' || *str == 'N') {
    char* tmp = nolibc_strdup(str);
    for (int i = 0; tmp[i]; ++i)
      tmp[i] = nolibc_tolower(tmp[i]);
    if (nolibc_strncmp(tmp, "nan", 3) == 0) {
      nolibc_free(tmp);
      return (0.0 * sign) / 0.0;
    }
    nolibc_free(tmp);
  }
  while (*str >= '0' && *str <= '9')
    ret = ret * 10.0 + (*str++ - '0');
  if (*str == '.') {
    ++str;
    size_t fracLen = 0;
    while (*str >= '0' && *str <= '9') {
      ++str;
      ++fracLen;
    }
    str -= fracLen;
    double frac = 0.0;
    for (size_t i = 0; i != fracLen; ++i)
      frac = frac * 10.0 + (*str++ - '0');
    if (frac != 0.0) {
      while (fracLen--)
        frac /= 10.0;
      ret += frac;
    }
  }
  if (*str == 'e' || *str == 'E') {
    ++str;
    int exp_sign = 1;
    if (*str == '-') {
      exp_sign = -1;
      ++str;
    } else if (*str == '+')
      ++str;
    int exp = 0;
    while (*str >= '0' && *str <= '9')
      exp = exp * 10 + (*str++ - '0');
    if (exp_sign == 1) {
      while (exp--)
        ret *= 10.0;
    } else {
      while (exp--)
        ret /= 10.0;
    }
  }
  if (endptr)
    *endptr = (char*)str;
  return ret * sign;
}
float nolibc_strtof(const char* str, char** endptr) {
  float ret = 0.0f;
  int sign = 1;
  while (*str == ' ' || *str == '\t')
    ++str;
  if (*str == '-') {
    sign = -1;
    ++str;
  } else if (*str == '+')
    ++str;
  if (*str == 'i' || *str == 'I') {
    char* tmp = nolibc_strdup(str);
    for (int i = 0; tmp[i]; ++i)
      tmp[i] = nolibc_tolower(tmp[i]);
    if (nolibc_strncmp(tmp, "inf", 3) == 0) {
      nolibc_free(tmp);
      return (1.0f * sign) / 0.0f;
    }
    nolibc_free(tmp);
  } else if (*str == 'n' || *str == 'N') {
    char* tmp = nolibc_strdup(str);
    for (int i = 0; tmp[i]; ++i)
      tmp[i] = nolibc_tolower(tmp[i]);
    if (nolibc_strncmp(tmp, "nan", 3) == 0) {
      nolibc_free(tmp);
      return (0.0f * sign) / 0.0f;
    }
    nolibc_free(tmp);
  }
  while (*str >= '0' && *str <= '9')
    ret = ret * 10.0f + (*str++ - '0');
  if (*str == '.') {
    ++str;
    size_t fracLen = 0;
    while (*str >= '0' && *str <= '9') {
      ++str;
      ++fracLen;
    }
    str -= fracLen;
    float frac = 0.0f;
    for (size_t i = 0; i != fracLen; ++i)
      frac = frac * 10.0f + (*str++ - '0');
    if (frac != 0.0f) {
      while (fracLen--)
        frac /= 10.0f;
      ret += frac;
    }
  }
  if (*str == 'e' || *str == 'E') {
    ++str;
    int exp_sign = 1;
    if (*str == '-') {
      exp_sign = -1;
      ++str;
    } else if (*str == '+')
      ++str;
    int exp = 0;
    while (*str >= '0' && *str <= '9')
      exp = exp * 10 + (*str++ - '0');
    if (exp_sign == 1) {
      while (exp--)
        ret *= 10.0f;
    } else {
      while (exp--)
        ret /= 10.0f;
    }
  }
  if (endptr)
    *endptr = (char*)str;
  return ret * sign;
}
long double nolibc_strtold(const char* str, char** endptr) {
  long double ret = 0.0l;
  int sign = 1;
  while (*str == ' ' || *str == '\t')
    ++str;
  if (*str == '-') {
    sign = -1;
    ++str;
  } else if (*str == '+')
    ++str;
  if (*str == 'i' || *str == 'I') {
    char* tmp = nolibc_strdup(str);
    for (int i = 0; tmp[i]; ++i)
      tmp[i] = nolibc_tolower(tmp[i]);
    if (nolibc_strncmp(tmp, "inf", 3) == 0) {
      nolibc_free(tmp);
      return (1.0l * sign) / 0.0l;
    }
    nolibc_free(tmp);
  } else if (*str == 'n' || *str == 'N') {
    char* tmp = nolibc_strdup(str);
    for (int i = 0; tmp[i]; ++i)
      tmp[i] = nolibc_tolower(tmp[i]);
    if (nolibc_strncmp(tmp, "nan", 3) == 0) {
      nolibc_free(tmp);
      return (0.0l * sign) / 0.0l;
    }
    nolibc_free(tmp);
  }
  while (*str >= '0' && *str <= '9')
    ret = ret * 10.0l + (*str++ - '0');
  if (*str == '.') {
    ++str;
    size_t fracLen = 0;
    while (*str >= '0' && *str <= '9') {
      ++str;
      ++fracLen;
    }
    str -= fracLen;
    long double frac = 0.0l;
    for (size_t i = 0; i != fracLen; ++i)
      frac = frac * 10.0l + (*str++ - '0');
    if (frac != 0.0l) {
      while (fracLen--)
        frac /= 10.0l;
      ret += frac;
    }
  }
  if (*str == 'e' || *str == 'E') {
    ++str;
    int exp_sign = 1;
    if (*str == '-') {
      exp_sign = -1;
      ++str;
    } else if (*str == '+')
      ++str;
    int exp = 0;
    while (*str >= '0' && *str <= '9')
      exp = exp * 10 + (*str++ - '0');
    if (exp_sign == 1) {
      while (exp--)
        ret *= 10.0l;
    } else {
      while (exp--)
        ret /= 10.0l;
    }
  }
  if (endptr)
    *endptr = (char*)str;
  return ret * sign;
}
long nolibc_strtol(const char* str, char** endptr, int base) {
  long ret = 0;
  int sign = 1;
  while (*str == ' ' || *str == '\t')
    ++str;
  if (*str == '-') {
    sign = -1;
    ++str;
  } else if (*str == '+')
    ++str;
  if (base == 0) {
    if (*str == '0') {
      ++str;
      if (*str == 'x' || *str == 'X') {
        base = 16;
        ++str;
      } else base = 8;
    } else base = 10;
  } else if (base == 8) {
    if (*str == '0')
      ++str;
  } else if (base == 16) {
    if (*str == '0') {
      ++str;
      if (*str == 'x' || *str == 'X')
        ++str;
    }
  }
  while (*str == '0')
    ++str;
  while (*str) {
    int digit;
    if (*str >= '0' && *str <= '0' + base - 1)
      digit = *str - '0';
    else if (base > 10) {
      char lowc = nolibc_tolower(*str);
      if (lowc >= 'a' && lowc <= 'a' + base - 11)
        digit = lowc - 'a' + 10;
      else break;
    } else break;
    ret = (ret * base) + digit;
    ++str;
  }
  if (endptr)
    *endptr = (char*)str;
  return ret * sign;
}
long long nolibc_strtoll(const char* str, char** endptr, int base) {
  long long ret = 0;
  int sign = 1;
  while (*str == ' ' || *str == '\t')
    ++str;
  if (*str == '-') {
    sign = -1;
    ++str;
  } else if (*str == '+')
    ++str;
  if (base == 0) {
    if (*str == '0') {
      ++str;
      if (*str == 'x' || *str == 'X') {
        base = 16;
        ++str;
      } else base = 8;
    } else base = 10;
  } else if (base == 8) {
    if (*str == '0')
      ++str;
  } else if (base == 16) {
    if (*str == '0') {
      ++str;
      if (*str == 'x' || *str == 'X')
        ++str;
    }
  }
  while (*str == '0')
    ++str;
  while (*str) {
    int digit;
    if (*str >= '0' && *str <= '0' + base - 1)
      digit = *str - '0';
    else if (base > 10) {
      char lowc = nolibc_tolower(*str);
      if (lowc >= 'a' && lowc <= 'a' + base - 11)
        digit = lowc - 'a' + 10;
      else break;
    } else break;
    ret = (ret * base) + digit;
    ++str;
  }
  if (endptr)
    *endptr = (char*)str;
  return ret * sign;
}
unsigned long nolibc_strtoul(const char* str, char** endptr, int base) {
  unsigned long ret = 0;
  int sign = 1;
  while (*str == ' ' || *str == '\t')
    ++str;
  if (*str == '-') {
    sign = -1;
    ++str;
  } else if (*str == '+')
    ++str;
  if (base == 0) {
    if (*str == '0') {
      ++str;
      if (*str == 'x' || *str == 'X') {
        base = 16;
        ++str;
      } else base = 8;
    } else base = 10;
  } else if (base == 8) {
    if (*str == '0')
      ++str;
  } else if (base == 16) {
    if (*str == '0') {
      ++str;
      if (*str == 'x' || *str == 'X')
        ++str;
    }
  }
  while (*str == '0')
    ++str;
  while (*str) {
    int digit;
    if (*str >= '0' && *str <= '0' + base - 1)
      digit = *str - '0';
    else if (base > 10) {
      char lowc = nolibc_tolower(*str);
      if (lowc >= 'a' && lowc <= 'a' + base - 11)
        digit = lowc - 'a' + 10;
      else break;
    } else break;
    ret = (ret * base) + digit;
    ++str;
  }
  if (endptr)
    *endptr = (char*)str;
  return ret * sign;
}
unsigned long long nolibc_strtoull(const char* str, char** endptr, int base) {
  unsigned long long ret = 0;
  int sign = 1;
  while (*str == ' ' || *str == '\t')
    ++str;
  if (*str == '-') {
    sign = -1;
    ++str;
  } else if (*str == '+')
    ++str;
  if (base == 0) {
    if (*str == '0') {
      ++str;
      if (*str == 'x' || *str == 'X') {
        base = 16;
        ++str;
      } else base = 8;
    } else base = 10;
  } else if (base == 8) {
    if (*str == '0')
      ++str;
  } else if (base == 16) {
    if (*str == '0') {
      ++str;
      if (*str == 'x' || *str == 'X')
        ++str;
    }
  }
  while (*str == '0')
    ++str;
  while (*str) {
    int digit;
    if (*str >= '0' && *str <= '0' + base - 1)
      digit = *str - '0';
    else if (base > 10) {
      char lowc = nolibc_tolower(*str);
      if (lowc >= 'a' && lowc <= 'a' + base - 11)
        digit = lowc - 'a' + 10;
      else break;
    } else break;
    ret = (ret * base) + digit;
    ++str;
  }
  if (endptr)
    *endptr = (char*)str;
  return ret * sign;
}
int nolibc_strverscmp(const char* s1, const char* s2) {
  while (1) {
    char c1 = *s1++;
    char c2 = *s2++;
    if (c1 != c2) {
      if (c1 == '\0' || c2 == '\0')
        return c1 - c2;
      if ((c1 >= '0' && c1 <= '9') &&
          (c2 >= '0' && c2 <= '9')) {
        int i1 = c1 - '0';
        int i2 = c2 - '0';
        while (*s1 >= '0' && *s1 <= '9')
          i1 = i1 * 10 + (*s1++ - '0');
        while (*s2 >= '0' && *s2 <= '9')
          i2 = i2 * 10 + (*s2++ - '0');
        if (i1 != i2)
          return i1 - i2;
      } else return c1 - c2;
    } else if (c1 == '\0')
      break;
  }
  return 0;
}
char nolibc_getchar() {
  char c;
  nolibc_read(0, &c, 1);
  return c;
}
char* nolibc_gets(char* str) {
  char* ret = str;
  while (1) {
    char c = nolibc_getchar();
    if (c == '\n')
      break;
    *str++ = c;
  }
  *str = '\0';
  return ret;
}
int nolibc_putchar(char c) {
  return nolibc_write(1, &c, 1);
}
int nolibc_puts(const char* str) {
  int ret = 0;
  while (*str)
    ret += nolibc_putchar(*str++);
  ret += nolibc_putchar('\n');
  return ret;
}