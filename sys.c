#include <asm/errno.h>
#include <asm/unistd.h>
#include <sys/mman.h>
#include <sys/signal.h>
#include <sys/times.h>
#include <time.h>
#include "arch.h"
#include "sys.h"

__thread int nolibc_errno;

int* const nolibc___errno_location() {
  return &nolibc_errno;
}

__attribute__((noreturn)) int nolibc_abort() {
  int pid = syscall0(__NR_getpid);
  syscall2(__NR_kill, pid, SIGABRT);
  for (;;);
}

int nolibc_accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen) {
  int ret = syscall3(__NR_accept, sockfd, addr, addrlen);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_accept4(int sockfd, struct sockaddr* addr, socklen_t* addrlen, int flags) {
  int ret = syscall4(__NR_accept4, sockfd, addr, addrlen, flags);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_access(const char* pathname, int mode) {
  int ret = syscall2(__NR_access, pathname, mode);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_acct(const char* filename) {
  int ret = syscall1(__NR_acct, filename);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_adjtimex(struct timex* buf) {
  int ret = syscall1(__NR_adjtimex, buf);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_adjtime(const struct timeval* itv, struct timeval* otv) {
  struct timex tntx;
  if (itv) {
    tntx.modes = ADJ_OFFSET_SINGLESHOT;
    tntx.offset = itv->tv_sec * 1000000 + itv->tv_usec;
  } else tntx.modes = ADJ_OFFSET_SS_READ;
  if (nolibc_clock_adjtime(CLOCK_REALTIME, &tntx) < 0)
    return -1;
  if (otv) {
    if (tntx.offset < 0) {
      otv->tv_sec = -(-tntx.offset / 1000000);
      otv->tv_usec = -(-tntx.offset % 1000000);
    } else {
      otv->tv_sec = tntx.offset / 1000000;
      otv->tv_usec = tntx.offset % 1000000;
    }
  }
  return 0;
}
void* nolibc_brk(void* addr) {
  void* ret = (void*)syscall1(__NR_brk, addr);
  if (!ret) {
    nolibc_errno = ENOMEM;
    ret = (void*)-1;
  }
  return ret;
}
void* nolibc_sbrk(intptr_t incr) {
  void* ret = (void*)syscall1(__NR_brk, 0);
  if (ret && ((void*)syscall1(__NR_brk, ret + incr)) == ret + incr)
    return ret + incr;
  nolibc_errno = ENOMEM;
  return (void*)-1;
}
int nolibc_chdir(const char* path) {
  int ret = syscall1(__NR_chdir, path);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_fchdir(int fd) {
  int ret = syscall1(__NR_fchdir, fd);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_chmod(const char* path, mode_t mode) {
  int ret = syscall2(__NR_chmod, path, mode);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_fchmod(int fd, mode_t mode) {
  int ret = syscall2(__NR_fchmod, fd, mode);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_clock_adjtime(clockid_t clk, struct timex* tx) {
  int ret = syscall2(__NR_clock_adjtime, clk, tx);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_clock_getcpuclockid(pid_t pid, clockid_t* clk) {
  const clockid_t pidclock = (~pid << 3) | 2;
  int ret = syscall2(__NR_clock_getres, pidclock, NULL);
  if (ret == -EINVAL)
    return ESRCH;
  if (ret == 0) {
    *clk = pidclock;
    return 0;
  }
  return -ret;
}
int nolibc_clock_getres(clockid_t clk, struct timespec* res) {
  int ret = syscall2(__NR_clock_getres, clk, res);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_clock_gettime(clockid_t clk, struct timespec* tp) {
  int ret = syscall2(__NR_clock_gettime, clk, tp);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_clock_nanosleep(clockid_t clk, int flags, const struct timespec* rqtp, struct timespec* rmtp) {
  return -syscall4(__NR_clock_nanosleep, clk, flags, rqtp, rmtp);
}
int nolibc_clock_settime(clockid_t clk, const struct timespec* tp) {
  int ret = syscall2(__NR_clock_settime, clk, tp);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
clock_t nolibc_clock() {
  struct timespec ts;
  if (syscall2(__NR_clock_gettime, CLOCK_PROCESS_CPUTIME_ID, &ts) != 0)
    return -1;
  return ts.tv_sec * CLOCKS_PER_SEC + ts.tv_nsec / (1000000000 / CLOCKS_PER_SEC);
}
void nolibc_close(int fd) {
  syscall1(__NR_close, fd);
}
int nolibc_connect(int fd, const struct sockaddr* addr, socklen_t len) {
  int ret = syscall3(__NR_connect, fd, addr, len);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
ssize_t nolibc_copy_file_range(int fd_in, off_t* off_in, int fd_out, off_t* off_out, size_t len, unsigned int flags) {
  int ret = syscall6(__NR_copy_file_range, fd_in, off_in, fd_out, off_out, len, flags);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_creat(const char* path, mode_t mode) {
  int ret;
#ifdef __NR_creat
  ret = syscall2(__NR_creat, path, mode);
#else
  ret = syscall3(__NR_open, path, O_CREAT | O_WRONLY | O_TRUNC, mode);
#endif
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_epoll_pwait(int fd, struct epoll_event* events, int maxevents, int timeout, const sigset_t* sigmask) {
  int ret = syscall6(__NR_epoll_pwait, fd, events, maxevents, timeout, sigmask, sizeof(sigset_t));
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_eventfd(unsigned int initval, int flags) {
  int ret = syscall2(__NR_eventfd2, initval, flags);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
// TODO: Implement `atexit` and `on_exit`. And hopefully not let procrastination get in the way
__attribute__((noreturn)) void nolibc__exit(int status) {
  syscall1(__NR_exit_group, status);
  syscall1(__NR_exit, status);
  for (;;);
}
int nolibc_getpid() {
  return syscall0(__NR_getpid);
}
int nolibc_kill(pid_t pid, int sig) {
  int ret = syscall2(__NR_kill, pid, sig);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
void* nolibc_mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset) {
#ifndef syscall6
  nolibc_errno = ENOSYS;
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
    nolibc_errno = -(long)ret;
    ret = MAP_FAILED;
  }
  return ret;
#endif
}
int nolibc_munmap(void* addr, size_t length) {
  int ret = syscall2(__NR_munmap, addr, length);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_pause() {
  int ret;
#ifdef __NR_pause
  ret = syscall0(__NR_pause);
#else
  ret = syscall4(__NR_ppoll, NULL, 0, NULL, NULL);
#endif
  nolibc_errno = -ret;
  return -1;
}
ssize_t nolibc_read(int fd, void* buf, size_t count) {
  ssize_t ret = syscall3(__NR_read, fd, buf, count);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
ssize_t nolibc_write(int fd, const char* buf, size_t count) {
  ssize_t ret = syscall3(__NR_write, fd, buf, count);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}