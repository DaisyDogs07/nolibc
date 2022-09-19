#include <linux/capability.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <sys/socket.h>
#include <sys/timex.h>
#include <sys/types.h>
#include <sched.h>
#include <unistd.h>

#ifndef MREMAP_MAYMOVE
#define MREMAP_MAYMOVE 1
#endif
#ifndef MREMAP_FIXED
#define MREMAP_FIXED 2
#endif

int* const nolibc___errno_location();
__attribute__((noreturn)) int nolibc_abort();
int nolibc_accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen);
int nolibc_accept4(int sockfd, struct sockaddr* addr, socklen_t* addrlen, int flags);
int nolibc_access(const char* pathname, int mode);
int nolibc_acct(const char* filename);
int nolibc_adjtimex(struct timex* buf);
int nolibc_adjtime(const struct timeval* itv, struct timeval* otv);
unsigned int nolibc_alarm(unsigned int seconds);
useconds_t nolibc_ualarm(useconds_t usec, useconds_t interval);
int nolibc_bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen);
void* nolibc_brk(void* addr);
void* nolibc_sbrk(intptr_t incr);
int nolibc_capget(cap_user_header_t header, cap_user_data_t data);
int nolibc_capset(cap_user_header_t header, const cap_user_data_t data);
int nolibc_chdir(const char* path);
int nolibc_fchdir(int fd);
int nolibc_chmod(const char* path, mode_t mode);
int nolibc_fchmod(int fd, mode_t mode);
int nolibc_chown(const char* path, uid_t owner, gid_t group);
int nolibc_fchown(int fd, uid_t owner, gid_t group);
int nolibc_chroot(const char* path);
clock_t nolibc_clock();
int nolibc_clock_adjtime(clockid_t clk, struct timex* tx);
int nolibc_clock_getcpuclockid(pid_t pid, clockid_t* clk);
int nolibc_clock_getres(clockid_t clk, struct timespec* res);
int nolibc_clock_gettime(clockid_t clk, struct timespec* tp);
int nolibc_clock_nanosleep(clockid_t clk, int flags, const struct timespec* req, struct timespec* rem);
int nolibc_clock_settime(clockid_t clk, const struct timespec* tp);
int nolibc_clone(int (*fn)(void*), void* child_stack, int flags, void* arg, ...);
void nolibc_close(int fd);
int nolibc_connect(int fd, const struct sockaddr* addr, socklen_t len);
ssize_t nolibc_copy_file_range(int fd_in, off_t* off_in, int fd_out, off_t* off_out, size_t len, unsigned int flags);
int nolibc_creat(const char* path, mode_t mode);
int nolibc_epoll_pwait(int fd, struct epoll_event* events, int maxevents, int timeout, const sigset_t* sigmask);
int nolibc_eventfd(unsigned int initval, int flags);
int nolibc_eventfd_read(int fd, eventfd_t* value);
int nolibc_eventfd_write(int fd, eventfd_t value);
__attribute__((noreturn)) void nolibc__exit(int status);
int nolibc_getcpu(unsigned int* cpu, unsigned int* node);
int nolibc_getpagesize();
int nolibc_getpeername(int fd, struct sockaddr* addr, socklen_t* len);
int nolibc_getpid();
int nolibc_getpriority(int which, int who);
int nolibc_setpriority(int which, int who, int prio);
int nolibc_kill(pid_t pid, int sig);
void* nolibc_mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset);
void* nolibc_mremap(void* old_addr, size_t old_size, size_t new_size, int flags, ...);
int nolibc_munmap(void* addr, size_t length);
int nolibc_nanosleep(const struct timespec* req, struct timespec* rem);
int nolibc_open(const char* path, int oflag, ...);
int nolibc_openat(int fd, const char* path, int oflag, ...);
int nolibc_pause();
int nolibc_personality(unsigned long persona);
int nolibc_pipe(int pipefd[2]);
int nolibc_pipe2(int pipefd[2], int flags);
ssize_t nolibc_read(int fd, void* buf, size_t count);
ssize_t nolibc_readlink(const char* path, char* buf, size_t bufsiz);
ssize_t nolibc_readv(int fd, const struct iovec* iov, int iovcnt);
int nolibc_rename(const char* oldpath, const char* newpath);
int nolibc_renameat(int olddirfd, const char* oldpath, int newdirfd, const char* newpath);
int nolibc_rmdir(const char* path);
int nolibc_sched_yield();
int nolibc_sched_getaffinity(pid_t pid, size_t cpusetsize, cpu_set_t* mask);
int nolibc_sched_getcpu();
int nolibc_sched_getparam(pid_t pid, struct sched_param* param);
int nolibc_sched_setaffinity(pid_t pid, size_t cpusetsize, const cpu_set_t* mask);
int nolibc_sched_setparam(pid_t pid, const struct sched_param* param);
int nolibc_setitimer(int which, const struct itimerval* new_value, struct itimerval* old_value);
unsigned int nolibc_sleep(unsigned int seconds);
int nolibc_socket(int family, int type, int protocol);
int nolibc_socketpair(int family, int type, int protocol, int* sv);
ssize_t nolibc_write(int fd, const void* buf, size_t count);