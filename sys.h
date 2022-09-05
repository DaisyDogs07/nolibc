#include <sys/types.h>
#include <stddef.h>
#include <stdint.h>

int* const nolibc___errno_location();
int nolibc_abort();
void* nolibc_brk(void*);
void* nolibc_sbrk(intptr_t);
int nolibc_chdir(const char*);
int nolibc_fchdir(int);
int nolibc_chmod(const char*, mode_t);
int nolibc_fchmod(int, mode_t);
void nolibc_exit(int);
int nolibc_getpid();
void* nolibc_mmap(void*, size_t, int, int, int, off_t);
int nolibc_munmap(void*, size_t);