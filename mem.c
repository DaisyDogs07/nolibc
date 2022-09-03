#include <sys/mman.h>
#include "mem.h"
#include "sys.h"

void nolibc_memset(void* dst, char c, size_t len) {
  char* p = (char*)dst;
  while (len--)
    *(p++) = c;
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
char nolibc_memcmp(const void* str1, const void* str2, size_t count) {
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

#ifndef container_of
#define container_of(PTR, TYPE, FIELD) ({      \
  __typeof__(((TYPE*)0)->FIELD)* __FIELD_PTR = (PTR);  \
  (TYPE*)((char*)__FIELD_PTR - __builtin_offsetof(TYPE, FIELD));  \
})
#endif

struct nolibc_heap {
  size_t len;
  char user_p[] __attribute__((__aligned__));
};

void nolibc_free(void* ptr) {
  struct nolibc_heap* heap;
  if (!ptr)
    return;
  heap = container_of(ptr, struct nolibc_heap, user_p);
  nolibc_munmap(heap, heap->len);
}
void* nolibc_malloc(size_t len) {
  struct nolibc_heap* heap;
  len = sizeof(*heap) + len;
  len = (len + 4095UL) & -4096UL;
  heap = nolibc_mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
  if (__builtin_expect(heap == MAP_FAILED, 0))
    return NULL;
  heap->len = len;
  return heap->user_p;
}
void* nolibc_calloc(size_t size, size_t nmemb) {
  void* orig;
  size_t res = 0;
  if (__builtin_expect(__builtin_mul_overflow(nmemb, size, &res), 0))
    return NULL;
  return nolibc_malloc(res);
}
void* nolibc_realloc(void* old_ptr, size_t new_size) {
  struct nolibc_heap* heap;
  size_t user_p_len;
  void* ret;
  if (!old_ptr)
    return nolibc_malloc(new_size);
  heap = container_of(old_ptr, struct nolibc_heap, user_p);
  user_p_len = heap->len - sizeof(*heap);
  if (user_p_len >= new_size)
    return old_ptr;
  ret = nolibc_malloc(new_size);
  if (__builtin_expect(!ret, 0))
    return NULL;
  nolibc_memcpy(ret, heap->user_p, heap->len);
  nolibc_munmap(heap, heap->len);
  return ret;
}