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

void* nolibc_brk(void* addr) {
  void* ret = (void*)syscall1(__NR_brk, addr);
  if (!ret) {
    errno = ENOMEM;
    ret = (void*)-1;
  }
  return ret;
}
void* nolibc_sbrk(intptr_t incr) {
  void* ret = (void*)syscall1(__NR_brk, 0);
  if (ret && ((void*)syscall1(__NR_brk, ret + incr)) == ret + incr)
    return ret + incr;
  errno = ENOMEM;
  return (void*)-1;
}
int nolibc_chdir(const char* path) {
  int ret = syscall1(__NR_chdir, path);
  if (ret < 0) {
    errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_fchdir(int fd) {
  int ret = syscall1(__NR_fchdir, fd);
  if (ret < 0) {
    errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_chmod(const char* path, mode_t mode) {
  int ret = syscall2(__NR_chmod, path, mode);
  if (ret < 0) {
    errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_fchmod(int fd, mode_t mode) {
  int ret = syscall2(__NR_fchmod, fd, mode);
  if (ret < 0) {
    errno = -ret;
    ret = -1;
  }
  return ret;
}
// TODO: Implement `atexit` and `on_exit`. And hopefully not let procrastination get in the way
__attribute__((noreturn)) void nolibc_exit(int status) {
  syscall1(__NR_fsync, 0); // in
  syscall1(__NR_fsync, 1); // out
  syscall1(__NR_fsync, 2); // err
  syscall1(__NR_exit, status & 0377);
  for (;;);
}
int nolibc_getpid() {
  return syscall0(__NR_getpid);
}
void* nolibc_mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset) {
#ifndef syscall6
  errno = ENOSYS;
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