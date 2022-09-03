#if defined(__x86_64__)
#include "arch-x86_64.h"
#elif defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__)
#include "arch-i386.h"
#elif defined(__ARM_EABI__)
#include "arch-arm.h"
#elif defined(__aarch64__)
#include "arch-aarch64.h"
#elif defined(__mips__) && defined(_ABIO32)
#include "arch-mips.h"
#elif defined(__riscv)
#include "arch-riscv.h"
#endif