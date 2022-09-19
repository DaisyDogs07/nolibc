#include <asm/errno.h>
#include <asm/unistd.h>
#include <sys/mman.h>
#include <sys/param.h>
#include <sys/signal.h>
#include <fcntl.h>
#include <stdarg.h>
#include <time.h>
#include "arch.h"
#include "mem.h"
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
  int ret;
#ifdef __NR_accept
  ret = syscall3(__NR_accept, sockfd, addr, addrlen);
#else
  ret = syscall4(__NR_accept4, sockfd, addr, addrlen, 0);
#endif
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
unsigned int nolibc_alarm(unsigned int seconds) {
  struct itimerval itv, oitv;
  itv.it_interval.tv_usec = 0;
  itv.it_interval.tv_sec = 0;
  itv.it_value.tv_usec = 0;
  itv.it_value.tv_sec = seconds;
  if (syscall3(__NR_setitimer, ITIMER_REAL, &itv, &oitv) < 0)
    return 0;
  unsigned int ret = oitv.it_value.tv_sec;
  if (oitv.it_value.tv_usec > 500000 ||
      (ret == 0 && oitv.it_value.tv_usec > 0))
    ret++;
  return ret;
}
useconds_t nolibc_ualarm(useconds_t usec, useconds_t interval) {
  struct itimerval timer, otimer;
  timer.it_interval.tv_sec = 0;
  timer.it_interval.tv_usec = interval;
  timer.it_value.tv_sec = 0;
  timer.it_value.tv_usec = usec;
  if (syscall3(__NR_setitimer, ITIMER_REAL, &timer, &otimer) < 0)
    return 0;
  return (otimer.it_value.tv_sec * 1000000) + otimer.it_value.tv_usec;
}
int nolibc_bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen) {
  int ret = syscall3(__NR_bind, sockfd, addr, addrlen);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
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
int nolibc_capget(cap_user_header_t header, cap_user_data_t data) {
  int ret = syscall2(__NR_capget, header, data);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_capset(cap_user_header_t header, const cap_user_data_t data) {
  int ret = syscall2(__NR_capset, header, data);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
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
int nolibc_chown(const char* path, uid_t owner, gid_t group) {
  int ret = syscall3(__NR_chown, path, owner, group);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_fchown(int fd, uid_t owner, gid_t group) {
  int ret = syscall3(__NR_fchown, fd, owner, group);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_chroot(const char* path) {
  int ret = syscall1(__NR_chroot, path);
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
int nolibc_clock_nanosleep(clockid_t clk, int flags, const struct timespec* req, struct timespec* rem) {
  return -syscall4(__NR_clock_nanosleep, clk, flags, req, rem);
}
int nolibc_clock_settime(clockid_t clk, const struct timespec* tp) {
  int ret = syscall2(__NR_clock_settime, clk, tp);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_clone(int (*fn)(void*), void* child_stack, int flags, void* arg, ...) {
  void* ptid;
  void* tls;
  void* ctid;
  va_list ap;
  va_start(ap, arg);
  ptid = va_arg(ap, void*);
  tls = va_arg(ap, void*);
  ctid = va_arg(ap, void*);
  va_end(ap);
  int ret;
  if (!fn || !child_stack) {
    nolibc_errno = EINVAL;
    ret = -1;
  } else {
    ret = syscall5(__NR_clone, flags, child_stack, ptid, tls, ctid);
    if (ret == 0)
      nolibc__exit(fn(arg));
    else if (ret < 0) {
      nolibc_errno = -ret;
      ret = -1;
    }
  }
  return ret;
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
#ifndef syscall6
  nolibc_errno = ENOSYS;
  return -1;
#else
  int ret = syscall6(__NR_copy_file_range, fd_in, off_in, fd_out, off_out, len, flags);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
#endif
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
#ifndef syscall6
  nolibc_errno = ENOSYS;
  return -1;
#else
  int ret = syscall6(__NR_epoll_pwait, fd, events, maxevents, timeout, sigmask, sizeof(sigset_t));
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
#endif
}
int nolibc_eventfd(unsigned int initval, int flags) {
  int ret = syscall2(__NR_eventfd2, initval, flags);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_eventfd_read(int fd, eventfd_t* value) {
  return nolibc_read(fd, value, sizeof(eventfd_t)) != sizeof(eventfd_t) ? -1 : 0;
}
int nolibc_eventfd_write(int fd, eventfd_t value) {
  return nolibc_write(fd, &value, sizeof(eventfd_t)) != sizeof(eventfd_t) ? -1 : 0;
}
// TODO: Implement `atexit` and `on_exit`. And hopefully not let procrastination get in the way
__attribute__((noreturn)) void nolibc__exit(int status) {
  syscall1(__NR_exit_group, status);
  syscall1(__NR_exit, status);
  for (;;);
}
int nolibc_getcpu(unsigned int* cpu, unsigned int* node) {
  int ret = syscall3(__NR_getcpu, cpu, node, NULL);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_getpagesize() {
#ifdef	EXEC_PAGESIZE
  return EXEC_PAGESIZE;
#else
#ifdef	NBPG
#ifndef	CLSIZE
#define	CLSIZE	1
#endif
  return NBPG * CLSIZE;
#else
  return NBPC;
#endif
#endif
}
int nolibc_getpeername(int fd, struct sockaddr* addr, socklen_t* len) {
  int ret = syscall3(__NR_getpeername, fd, addr, len);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_getpid() {
  return syscall0(__NR_getpid);
}
int nolibc_getpriority(int which, int who) {
  int ret = syscall2(__NR_getpriority, which, who);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  if (ret >= 0)
    ret = 20 - ret;
  return ret;
}
int nolibc_setpriority(int which, int who, int prio) {
  int ret = syscall3(__NR_setpriority, which, who, prio);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
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
void* nolibc_mremap(void* old_addr, size_t old_size, size_t new_size, int flags, ...) {
  va_list va;
  void* new_addr = NULL;
  if (flags & MREMAP_FIXED) {
    va_start(va, flags);
    new_addr = va_arg(va, void*);
    va_end(va);
  }
  void* ret = (void*)syscall5(__NR_mremap, old_addr, old_size, new_size, flags, new_addr);
  if ((unsigned long)ret >= -4095UL) {
    nolibc_errno = -(long)ret;
    ret = MAP_FAILED;
  }
  return ret;
}
int nolibc_munmap(void* addr, size_t length) {
  int ret = syscall2(__NR_munmap, addr, length);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_nanosleep(const struct timespec* req, struct timespec* rem) {
  int ret = syscall4(__NR_clock_nanosleep, CLOCK_REALTIME, 0, req, rem);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_open(const char* path, int oflag, ...) {
  va_list va;
  mode_t mode = 0;
  if (oflag & O_CREAT) {
    va_start(va, oflag);
    mode = va_arg(va, mode_t);
    va_end(va);
  }
  int ret = syscall3(__NR_open, path, oflag, mode);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_openat(int fd, const char* path, int oflag, ...) {
  va_list va;
  mode_t mode = 0;
  if (oflag & O_CREAT) {
    va_start(va, oflag);
    mode = va_arg(va, mode_t);
    va_end(va);
  }
  int ret = syscall4(__NR_openat, fd, path, oflag, mode);
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
int nolibc_personality(unsigned long persona) {
  int ret = syscall1(__NR_personality, persona);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_pipe(int pipefd[2]) {
  int ret = syscall2(__NR_pipe2, (int*)pipefd, 0);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_pipe2(int pipefd[2], int flags) {
  int ret = syscall2(__NR_pipe2, (int*)pipefd, flags);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
ssize_t nolibc_read(int fd, void* buf, size_t count) {
  ssize_t ret = syscall3(__NR_read, fd, buf, count);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
ssize_t nolibc_readlink(const char* path, char* buf, size_t bufsiz) {
  ssize_t ret = syscall3(__NR_readlink, path, buf, bufsiz);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
ssize_t nolibc_readv(int fd, const struct iovec* iov, int iovcnt) {
  ssize_t ret = syscall3(__NR_readv, fd, iov, iovcnt);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_rename(const char* oldpath, const char* newpath) {
  int ret = syscall2(__NR_rename, oldpath, newpath);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_renameat(int olddirfd, const char* oldpath, int newdirfd, const char* newpath) {
  int ret = syscall4(__NR_renameat, olddirfd, oldpath, newdirfd, newpath);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_rmdir(const char* path) {
  int ret = syscall1(__NR_rmdir, path);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_sched_yield() {
  return syscall0(__NR_sched_yield);
}
int nolibc_sched_getaffinity(pid_t pid, size_t cpusetsize, cpu_set_t* mask) {
  int ret = syscall3(__NR_sched_getaffinity, pid, cpusetsize, mask);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_sched_getcpu() {
  int cpu;
  return nolibc_getcpu(&cpu, NULL) == -1 ? -1 : cpu;
}
int nolibc_sched_getparam(pid_t pid, struct sched_param* param) {
  int ret = syscall2(__NR_sched_getparam, pid, param);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_sched_setaffinity(pid_t pid, size_t cpusetsize, const cpu_set_t* mask) {
  int ret = syscall3(__NR_sched_setaffinity, pid, cpusetsize, mask);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_sched_setparam(pid_t pid, const struct sched_param* param) {
  int ret = syscall2(__NR_sched_setparam, pid, param);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_setitimer(int which, const struct itimerval* new_value, struct itimerval* old_value) {
  if ((int32_t)new_value->it_value.tv_sec != new_value->it_value.tv_sec ||
      (int32_t)new_value->it_interval.tv_sec != new_value->it_interval.tv_sec) {
    nolibc_errno = EOVERFLOW;
    return -1;
  }
  int ret = syscall3(__NR_setitimer, which, new_value, old_value);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
unsigned int nolibc_sleep(unsigned int seconds) {
  int save_errno = nolibc_errno;
  const unsigned int max = (unsigned int)(((unsigned long int)(~((time_t)0))) >> 1);
  struct timespec ts = {0, 0};
  do {
    if (sizeof(ts.tv_sec) <= sizeof(seconds)) {
      ts.tv_sec += seconds < max ? seconds : max;
      seconds -= (unsigned int)ts.tv_sec;
    } else {
      ts.tv_sec = (time_t)seconds;
      seconds = 0;
    }
    if (nolibc_nanosleep(&ts, &ts) < 0)
      return seconds + ts.tv_sec;
  } while (seconds > 0);
  nolibc_errno = save_errno;
  return 0;
}
int nolibc_socket(int family, int type, int protocol) {
  int ret = syscall3(__NR_socket, family, type, protocol);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
int nolibc_socketpair(int family, int type, int protocol, int* sv) {
  int ret = syscall4(__NR_socketpair, family, type, protocol, sv);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}
ssize_t nolibc_write(int fd, const void* buf, size_t count) {
  ssize_t ret = syscall3(__NR_write, fd, buf, count);
  if (ret < 0) {
    nolibc_errno = -ret;
    ret = -1;
  }
  return ret;
}