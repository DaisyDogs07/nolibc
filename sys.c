#include <sys/signal.h>
#include <sys/syscall.h>
#include <sys/mman.h>
#include "sys.h"
#include "arch.h"

__thread int errno;

int* const nolibc___errno_location() {
  return &errno;
}

__attribute__((noreturn)) int nolibc_abort() {
  int pid = syscall0(SYS_getpid);
  syscall2(SYS_kill, pid, SIGABRT);
  for (;;);
}

void* nolibc_mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset) {
  void* ret = (void*)syscall6(SYS_mmap, addr, length, prot, flags, fd, offset);
  if ((unsigned long)ret >= -4095UL) {
    errno = -(long)ret;
    ret = MAP_FAILED;
  }
  return ret;
}
int nolibc_munmap(void* addr, size_t length) {
  int ret = syscall2(SYS_munmap, addr, length);
  if (ret < 0) {
    errno = -ret;
    ret = -1;
  }
  return ret;
}