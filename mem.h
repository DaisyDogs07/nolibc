#include <stddef.h>

void* nolibc_memset(void* dst, char c, size_t len);
void* nolibc_memmove(void* dest, const void* src, size_t len);
void* nolibc_memcpy(void* dest, const void* src, size_t len);
int nolibc_memcmp(const void* str1, const void* str2, size_t count);
void nolibc_free(void* ptr);
void* nolibc_malloc(size_t len);
void* nolibc_calloc(size_t size, size_t nmemb);
void* nolibc_realloc(void* ptr, size_t size);