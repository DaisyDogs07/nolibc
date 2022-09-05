#include <stddef.h>

void* nolibc_memset(void*, char, size_t);
void* nolibc_memmove(void*, const void*, size_t);
void* nolibc_memcpy(void*, const void*, size_t);
int nolibc_memcmp(const void*, const void*, size_t);
void nolibc_free(void*);
void* nolibc_malloc(size_t);
void* nolibc_calloc(size_t, size_t);
void* nolibc_realloc(void*, size_t);