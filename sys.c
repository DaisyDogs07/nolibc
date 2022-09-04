#include <sys/signal.h>
#include <asm/unistd.h>
#include <sys/mman.h>
#include <asm/errno.h>
#include "sys.h"
#include "arch.h"

__thread int errno;

int* const nolibc___errno_location() {
  return &errno;
}

__attribute__((noreturn)) int nolibc_abort() {
  int pid = syscall0(__NR_getpid);
  syscall2(__NR_kill, pid, SIGABRT);
  for (;;);
}

void* nolibc_mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset) {
#ifndef syscall6
  errno = -ENOSYS;
  return MAP_FAILED;
#else
  int n;
#if defined(__i386__)
	n = __NR_mmap2;
	offset >>= 12;
#else
	n = __NR_mmap;
#endif
  void* ret = (void*)syscall6(n, addr, length, prot, flags, fd, offset);
  if ((unsigned long)ret >= -4095UL) {
    errno = -(long)ret;
    ret = MAP_FAILED;
  }
  return ret;
#endif
}
int nolibc_munmap(void* addr, size_t length) {
  int ret = syscall2(__NR_munmap, addr, length);
  if (ret < 0) {
    errno = -ret;
    ret = -1;
  }
  return ret;
}