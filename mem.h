#include <stddef.h>

void* nolibc_bcopy(const void* src, void* dest, size_t n);
void* nolibc_bzero(void* s, size_t n);
void* nolibc_memchr(const void* s, char c, size_t n);
void* nolibc_memrchr(const void* s, char c, size_t n);
void* nolibc_rawmemchr(const void* s, char c);
int nolibc_memcmp(const void* s1, const void* s2, size_t count);
void* nolibc_memcpy(void* dest, const void* src, size_t len);
void* nolibc_memccpy(void* dest, const void* src, char c, size_t len);
void* nolibc_mempcpy(void* dest, const void* src, size_t len);
void* nolibc_memfrob(void* s, size_t n);
void* nolibc_memmem(const void* haystack, size_t haystack_len, const void* needle, size_t needle_len);
void* nolibc_memmove(void* dest, const void* src, size_t len);
void* nolibc_memset(void* dst, char c, size_t len);
void nolibc_swab(const void* src, void* dest, size_t n);
void nolibc_free(void* ptr);
void* nolibc_malloc(size_t len);
void* nolibc_calloc(size_t size, size_t nmemb);
void* nolibc_realloc(void* ptr, size_t size);