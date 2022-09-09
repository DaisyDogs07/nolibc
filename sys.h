#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/timex.h>
#include <sys/types.h>
#include <stddef.h>
#include <stdint.h>

int* const nolibc___errno_location();
__attribute__((noreturn)) int nolibc_abort();
int nolibc_accept(int, struct sockaddr*, socklen_t*);
int nolibc_accept4(int, struct sockaddr*, socklen_t*, int);
int nolibc_access(const char*, int);
int nolibc_acct(const char*);
int nolibc_adjtimex(struct timex*);
int nolibc_adjtime(const struct timeval*, struct timeval*);
void* nolibc_brk(void*);
void* nolibc_sbrk(intptr_t);
int nolibc_chdir(const char*);
int nolibc_fchdir(int);
int nolibc_chmod(const char*, mode_t);
int nolibc_fchmod(int, mode_t);
int nolibc_clock_adjtime(clockid_t, struct timex*);
int nolibc_clock_getcpuclockid(pid_t, clockid_t*);
int nolibc_clock_getres(clockid_t, struct timespec*);
int nolibc_clock_gettime(clockid_t, struct timespec*);
int nolibc_clock_nanosleep(clockid_t, int, const struct timespec*, struct timespec*);
int nolibc_clock_settime(clockid_t, const struct timespec*);
clock_t nolibc_clock();
void nolibc_close(int);
int nolibc_connect(int, const struct sockaddr*, socklen_t);
ssize_t nolibc_copy_file_range(int, off_t*, int, off_t*, size_t, unsigned int);
int nolibc_creat(const char*, mode_t);
int nolibc_epoll_pwait(int, struct epoll_event*, int, int, const sigset_t*);
int nolibc_eventfd(unsigned int, int);
__attribute__((noreturn)) void nolibc__exit(int);
int nolibc_getpid();
int nolibc_kill(pid_t, int);
void* nolibc_mmap(void*, size_t, int, int, int, off_t);
int nolibc_munmap(void*, size_t);
int nolibc_pause();
ssize_t nolibc_read(int, void*, size_t);
ssize_t nolibc_write(int, const char*, size_t);