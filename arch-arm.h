/* Syscalls for ARM in ARM or Thumb modes :
 *   - registers are 32-bit
 *   - stack is 8-byte aligned
 *     ( http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.faqs/ka4127.html)
 *   - syscall number is passed in r7
 *   - arguments are in r0, r1, r2, r3, r4, r5
 *   - the system call is performed by calling svc #0
 *   - syscall return comes in r0.
 *   - only lr is clobbered.
 *   - the arguments are cast to long and assigned into the target registers
 *     which are then simply passed as registers to the asm code, so that we
 *     don't have to experience issues with register constraints.
 *   - the syscall number is always specified last in order to allow to force
 *     some registers before (gcc refuses a %-register at the last position).
 *
 * Also, ARM supports the old_select syscall if newselect is not available
 */
#define __ARCH_WANT_SYS_OLD_SELECT

#define syscall0(num)                                                      \
({                                                                            \
	register long _num __asm__ ("r7") = (num);                            \
	register long _arg1 __asm__ ("r0");                                   \
	                                                                      \
	__asm__  volatile (                                                   \
		"svc #0\n"                                                    \
		: "=r"(_arg1)                                                 \
		: "r"(_num)                                                   \
		: "memory", "cc", "lr"                                        \
	);                                                                    \
	_arg1;                                                                \
})

#define syscall1(num, arg1)                                                \
({                                                                            \
	register long _num __asm__ ("r7") = (num);                            \
	register long _arg1 __asm__ ("r0") = (long)(arg1);                    \
	                                                                      \
	__asm__  volatile (                                                   \
		"svc #0\n"                                                    \
		: "=r"(_arg1)                                                 \
		: "r"(_arg1),                                                 \
		  "r"(_num)                                                   \
		: "memory", "cc", "lr"                                        \
	);                                                                    \
	_arg1;                                                                \
})

#define syscall2(num, arg1, arg2)                                          \
({                                                                            \
	register long _num __asm__ ("r7") = (num);                            \
	register long _arg1 __asm__ ("r0") = (long)(arg1);                    \
	register long _arg2 __asm__ ("r1") = (long)(arg2);                    \
	                                                                      \
	__asm__  volatile (                                                   \
		"svc #0\n"                                                    \
		: "=r"(_arg1)                                                 \
		: "r"(_arg1), "r"(_arg2),                                     \
		  "r"(_num)                                                   \
		: "memory", "cc", "lr"                                        \
	);                                                                    \
	_arg1;                                                                \
})

#define syscall3(num, arg1, arg2, arg3)                                    \
({                                                                            \
	register long _num __asm__ ("r7") = (num);                            \
	register long _arg1 __asm__ ("r0") = (long)(arg1);                    \
	register long _arg2 __asm__ ("r1") = (long)(arg2);                    \
	register long _arg3 __asm__ ("r2") = (long)(arg3);                    \
	                                                                      \
	__asm__  volatile (                                                   \
		"svc #0\n"                                                    \
		: "=r"(_arg1)                                                 \
		: "r"(_arg1), "r"(_arg2), "r"(_arg3),                         \
		  "r"(_num)                                                   \
		: "memory", "cc", "lr"                                        \
	);                                                                    \
	_arg1;                                                                \
})

#define syscall4(num, arg1, arg2, arg3, arg4)                              \
({                                                                            \
	register long _num __asm__ ("r7") = (num);                            \
	register long _arg1 __asm__ ("r0") = (long)(arg1);                    \
	register long _arg2 __asm__ ("r1") = (long)(arg2);                    \
	register long _arg3 __asm__ ("r2") = (long)(arg3);                    \
	register long _arg4 __asm__ ("r3") = (long)(arg4);                    \
	                                                                      \
	__asm__  volatile (                                                   \
		"svc #0\n"                                                    \
		: "=r"(_arg1)                                                 \
		: "r"(_arg1), "r"(_arg2), "r"(_arg3), "r"(_arg4),             \
		  "r"(_num)                                                   \
		: "memory", "cc", "lr"                                        \
	);                                                                    \
	_arg1;                                                                \
})

#define syscall5(num, arg1, arg2, arg3, arg4, arg5)                        \
({                                                                            \
	register long _num __asm__ ("r7") = (num);                            \
	register long _arg1 __asm__ ("r0") = (long)(arg1);                    \
	register long _arg2 __asm__ ("r1") = (long)(arg2);                    \
	register long _arg3 __asm__ ("r2") = (long)(arg3);                    \
	register long _arg4 __asm__ ("r3") = (long)(arg4);                    \
	register long _arg5 __asm__ ("r4") = (long)(arg5);                    \
	                                                                      \
	__asm__  volatile (                                                   \
		"svc #0\n"                                                    \
		: "=r" (_arg1)                                                \
		: "r"(_arg1), "r"(_arg2), "r"(_arg3), "r"(_arg4), "r"(_arg5), \
		  "r"(_num)                                                   \
		: "memory", "cc", "lr"                                        \
	);                                                                    \
	_arg1;                                                                \
})
