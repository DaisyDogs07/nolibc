/* Syscalls for RISCV :
 *   - stack is 16-byte aligned
 *   - syscall number is passed in a7
 *   - arguments are in a0, a1, a2, a3, a4, a5
 *   - the system call is performed by calling ecall
 *   - syscall return comes in a0
 *   - the arguments are cast to long and assigned into the target
 *     registers which are then simply passed as registers to the asm code,
 *     so that we don't have to experience issues with register constraints.
 *
 * On riscv, select() is not implemented so we have to use pselect6().
 */
#define __ARCH_WANT_SYS_PSELECT6

#define syscall0(num)                                                      \
({                                                                            \
	register long _num  __asm__ ("a7") = (num);                           \
	register long _arg1 __asm__ ("a0");                                   \
									      \
	__asm__  volatile (                                                   \
		"ecall\n\t"                                                   \
		: "=r"(_arg1)                                                 \
		: "r"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_arg1;                                                                \
})

#define syscall1(num, arg1)                                                \
({                                                                            \
	register long _num  __asm__ ("a7") = (num);                           \
	register long _arg1 __asm__ ("a0") = (long)(arg1);		      \
									      \
	__asm__  volatile (                                                   \
		"ecall\n"                                                     \
		: "+r"(_arg1)                                                 \
		: "r"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_arg1;                                                                \
})

#define syscall2(num, arg1, arg2)                                          \
({                                                                            \
	register long _num  __asm__ ("a7") = (num);                           \
	register long _arg1 __asm__ ("a0") = (long)(arg1);                    \
	register long _arg2 __asm__ ("a1") = (long)(arg2);                    \
									      \
	__asm__  volatile (                                                   \
		"ecall\n"                                                     \
		: "+r"(_arg1)                                                 \
		: "r"(_arg2),                                                 \
		  "r"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_arg1;                                                                \
})

#define syscall3(num, arg1, arg2, arg3)                                    \
({                                                                            \
	register long _num  __asm__ ("a7") = (num);                           \
	register long _arg1 __asm__ ("a0") = (long)(arg1);                    \
	register long _arg2 __asm__ ("a1") = (long)(arg2);                    \
	register long _arg3 __asm__ ("a2") = (long)(arg3);                    \
									      \
	__asm__  volatile (                                                   \
		"ecall\n\t"                                                   \
		: "+r"(_arg1)                                                 \
		: "r"(_arg2), "r"(_arg3),                                     \
		  "r"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_arg1;                                                                \
})

#define syscall4(num, arg1, arg2, arg3, arg4)                              \
({                                                                            \
	register long _num  __asm__ ("a7") = (num);                           \
	register long _arg1 __asm__ ("a0") = (long)(arg1);                    \
	register long _arg2 __asm__ ("a1") = (long)(arg2);                    \
	register long _arg3 __asm__ ("a2") = (long)(arg3);                    \
	register long _arg4 __asm__ ("a3") = (long)(arg4);                    \
									      \
	__asm__  volatile (                                                   \
		"ecall\n"                                                     \
		: "+r"(_arg1)                                                 \
		: "r"(_arg2), "r"(_arg3), "r"(_arg4),                         \
		  "r"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_arg1;                                                                \
})

#define syscall5(num, arg1, arg2, arg3, arg4, arg5)                        \
({                                                                            \
	register long _num  __asm__ ("a7") = (num);                           \
	register long _arg1 __asm__ ("a0") = (long)(arg1);                    \
	register long _arg2 __asm__ ("a1") = (long)(arg2);                    \
	register long _arg3 __asm__ ("a2") = (long)(arg3);                    \
	register long _arg4 __asm__ ("a3") = (long)(arg4);                    \
	register long _arg5 __asm__ ("a4") = (long)(arg5);                    \
									      \
	__asm__  volatile (                                                   \
		"ecall\n"                                                     \
		: "+r"(_arg1)                                                 \
		: "r"(_arg2), "r"(_arg3), "r"(_arg4), "r"(_arg5),             \
		  "r"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_arg1;                                                                \
})

#define syscall6(num, arg1, arg2, arg3, arg4, arg5, arg6)                  \
({                                                                            \
	register long _num  __asm__ ("a7") = (num);                           \
	register long _arg1 __asm__ ("a0") = (long)(arg1);                    \
	register long _arg2 __asm__ ("a1") = (long)(arg2);                    \
	register long _arg3 __asm__ ("a2") = (long)(arg3);                    \
	register long _arg4 __asm__ ("a3") = (long)(arg4);                    \
	register long _arg5 __asm__ ("a4") = (long)(arg5);                    \
	register long _arg6 __asm__ ("a5") = (long)(arg6);                    \
									      \
	__asm__  volatile (                                                   \
		"ecall\n"                                                     \
		: "+r"(_arg1)                                                 \
		: "r"(_arg2), "r"(_arg3), "r"(_arg4), "r"(_arg5), "r"(_arg6), \
		  "r"(_num)                                                   \
		: "memory", "cc"                                              \
	);                                                                    \
	_arg1;                                                                \
})
