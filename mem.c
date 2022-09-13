#include <asm/unistd.h>
#include <sys/mman.h>
#include "arch.h"
#include "mem.h"
#include "sys.h"

void* nolibc_memset(void* dst, char c, size_t len) {
  char* p = (char*)dst;
  while (len--)
    *(p++) = c;
  return dst;
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
void* nolibc_memcpy(void* dest, const void* src, size_t len) {
  char* d = (char*)dest;
  const char* s = (const char*)src;
  while (len--)
    *d++ = *s++;
  return dest;
}
int nolibc_memcmp(const void* str1, const void* str2, size_t count) {
  const char* s1 = (const char*)str1;
  const char* s2 = (const char*)str2;
  while (--count) {
    char c1 = *s1++;
    char c2 = *s2++;
    if (c1 != c2)
      return c1 < c2 ? -1 : 1;
  }
  return 0;
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