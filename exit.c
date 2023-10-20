#include "exit.h"
#include "mem.h"
#include "sys.h"

__thread struct nolibc_exit_t* nolibc_exit_list = NULL;
__thread size_t nolibc_exit_length = 0;
__thread struct nolibc_quick_exit_t* nolibc_quick_exit_list = NULL;
__thread size_t nolibc_quick_exit_length = 0;

int nolibc_atexit(void (*func)()) {
  struct nolibc_exit_t entry;
  entry.atfunc = func;
  entry.is_on = false;
  void* new_list = nolibc_realloc(nolibc_exit_list, sizeof(struct nolibc_exit_t) * (nolibc_exit_length + 1));
  if (!new_list)
    return -1;
  nolibc_exit_list = new_list;
  nolibc_exit_list[nolibc_exit_length++] = entry;
  return 0;
}

int nolibc_on_exit(void (*func)(int, void*), void* arg) {
  struct nolibc_exit_t entry;
  entry.on_func = func;
  entry.on_arg = arg;
  entry.is_on = true;
  void* new_list = nolibc_realloc(nolibc_exit_list, sizeof(struct nolibc_exit_t) * (nolibc_exit_length + 1));
  if (!new_list)
    return -1;
  nolibc_exit_list = new_list;
  nolibc_exit_list[nolibc_exit_length++] = entry;
  return 0;
}

int nolibc_at_quick_exit(void (*func)()) {
  struct nolibc_quick_exit_t entry;
  entry.func = func;
  void* new_list = nolibc_realloc(nolibc_quick_exit_list, sizeof(struct nolibc_quick_exit_t) * (nolibc_quick_exit_length + 1));
  if (!new_list)
    return -1;
  nolibc_quick_exit_list = new_list;
  nolibc_quick_exit_list[nolibc_quick_exit_length++] = entry;
  return 0;
}

__attribute__((noreturn)) void nolibc_exit(int status) {
  if (nolibc_exit_length != 0) {
    for (size_t i = nolibc_exit_length - 1; i >= 0; --i) {
      struct nolibc_exit_t entry = nolibc_exit_list[i];
      if (entry.is_on)
        entry.on_func(status, entry.on_arg);
      else entry.atfunc();
      if (i == 0)
        break;
    }
    nolibc_free(nolibc_exit_list);
  }
  if (nolibc_quick_exit_length != 0)
    nolibc_free(nolibc_quick_exit_list);
  nolibc__exit(status);
}

__attribute__((noreturn)) void nolibc_quick_exit(int status) {
  if (nolibc_quick_exit_length != 0) {
    for (size_t i = nolibc_quick_exit_length - 1; i >= 0; --i) {
      nolibc_quick_exit_list[i].func();
      if (i == 0)
        break;
    }
    nolibc_free(nolibc_quick_exit_list);
  }
  if (nolibc_exit_length != 0)
    nolibc_free(nolibc_exit_list);
  nolibc__exit(status);
}