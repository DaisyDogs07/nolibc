#include <asm/unistd.h>
#include <sys/mman.h>
#include "arch.h"
#include "mem.h"
#include "sys.h"

void* nolibc_bzero(void* s, size_t n) {
  return nolibc_memset(s, '\0', n);
};
void* nolibc_memchr(const void* s, char c, size_t n) {
  const char* str = (const char*)s;
  while (n--) {
    if (*str == c)
      return (void*)str;
    ++str;
  }
  return NULL;
}
void* nolibc_memrchr(const void* s, char c, size_t n) {
  const char* str = (const char*)s;
  str += n;
  while (n--) {
    if (*--str == c)
      return (void*)str;
  }
  return NULL;
}
void* nolibc_rawmemchr(const void* s, char c) {
  const char* str = (const char*)s;
  while (1) {
    if (*str == c)
      return (void*)str;
    ++str;
  }
  return NULL;
}
int nolibc_memcmp(const void* s1, const void* s2, size_t count) {
  const char* str1 = (const char*)s1;
  const char* str2 = (const char*)s2;
  while (--count) {
    char c1 = *str1++;
    char c2 = *str2++;
    if (c1 != c2)
      return c1 - c2;
  }
  return 0;
}
void* nolibc_memcpy(void* dest, const void* src, size_t len) {
  char* d = (char*)dest;
  const char* s = (const char*)src;
  while (len--)
    *d++ = *s++;
  return dest;
}
void* nolibc_memccpy(void* dest, const void* src, char c, size_t len) {
  char* d = (char*)dest;
  const char* s = (const char*)src;
  while (len--) {
    *d++ = *s;
    if (*s++ == c)
      return d;
  }
  return NULL;
}
void* nolibc_mempcpy(void* dest, const void* src, size_t len) {
  char* d = (char*)dest;
  const char* s = (const char*)src;
  while (len--)
    *d++ = *s++;
  return d;
}
void* nolibc_memfrob(void* s, size_t n) {
  char* str = (char*)s;
  while (n--)
    *str++ ^= 42;
  return s;
}
void* nolibc_memmem(const void* haystack, size_t haystack_len, const void* needle, size_t needle_len) {
  const char* h = (const char*)haystack;
  const char* n = (const char*)needle;
  if (needle_len == 0)
    return (void*)h;
  while (haystack_len-- >= needle_len) {
    if (*h == *n && nolibc_memcmp(h, n, needle_len) == 0)
      return (void*)h;
    ++h;
  }
  return NULL;
}
void* nolibc_memmove(void* dest, const void* src, size_t len) {
  char* d = (char*)dest;
  const char* s = (const char*)src;
  if (d < s)
    while (len--)
      *d++ = *s++;
  else {
    char* lastd = d + (len - 1);
    const char* lasts = s + (len - 1);
    while (len--)
      *lastd-- = *lasts--;
  }
  return dest;
}
void* nolibc_memset(void* dst, char c, size_t len) {
  char* p = (char*)dst;
  while (len--)
    *p++ = c;
  return dst;
}
void nolibc_swab(const void* src, void* dest, size_t n) {
  const char* s = (const char*)src;
  char* d = (char*)dest;
  n &= ~1;
  while (n > 1) {
    char c = *s++;
    *d++ = *s++;
    *d++ = c;
    n -= 2;
  }
}

struct nolibc_heap {
  size_t len;
  char user_p[];
};

void nolibc_free(void* ptr) {
  if (!ptr)
    return;
  struct nolibc_heap* heap = ptr - __builtin_offsetof(struct nolibc_heap, user_p);
  syscall2(__NR_munmap, heap, heap->len);
}
void* nolibc_malloc(size_t len) {
  len += __builtin_offsetof(struct nolibc_heap, user_p);
  struct nolibc_heap* heap = nolibc_mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
  if (__builtin_expect(heap == MAP_FAILED, 0))
    return NULL;
  heap->len = len;
  return heap->user_p;
}
void* nolibc_calloc(size_t size, size_t nmemb) {
  size_t res = 0;
  if (__builtin_expect(__builtin_mul_overflow(nmemb, size, &res), 0))
    return NULL;
  return nolibc_malloc(res);
}
void* nolibc_realloc(void* ptr, size_t size) {
  if (!ptr)
    return nolibc_malloc(size);
  struct nolibc_heap* heap = ptr - __builtin_offsetof(struct nolibc_heap, user_p);
  size_t ptr_len = heap->len - __builtin_offsetof(struct nolibc_heap, user_p);
  if (ptr_len == size)
    return ptr;
  heap = nolibc_mremap(heap, heap->len, size, MREMAP_MAYMOVE);
  if (__builtin_expect(heap == MAP_FAILED, 0))
    return NULL;
  return heap->user_p;
}