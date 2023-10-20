#include <stdbool.h>
#include "mem.h"
#include "sys.h"

struct nolibc_exit_t {
  void (*atfunc)();
  void (*on_func)(int, void*);
  void* on_arg;
  bool is_on;
};
struct nolibc_quick_exit_t {
  void (*func)();
};

int nolibc_atexit(void (*func)());
int nolibc_on_exit(void (*func)(int, void*), void* arg);
int nolibc_at_quick_exit(void (*func)());
__attribute__((noreturn)) void nolibc_exit(int status);
__attribute__((noreturn)) void nolibc_quick_exit(int status);