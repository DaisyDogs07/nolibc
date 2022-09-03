#include <sys/types.h>
#include <stddef.h>

int* const nolibc___errno_location();
int nolibc_abort();
void* nolibc_mmap(void*, size_t, int, int, int, off_t);
int nolibc_munmap(void*, size_t);