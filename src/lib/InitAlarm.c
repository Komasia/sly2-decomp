// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_kernel.h"
/* InitAlarm (libkernel): install the kernel alarm patch on consoles whose ROM kernel lacks it (timer 3 compare
   interrupt not yet enabled). The patch is copied into kernel memory with a temporary kCopy syscall, then its
   entry syscall supplies the handlers for the patched syscalls. */
#define T3_MODE (*(volatile int *)0x10001810)
#define ALARM_PATCH_ADDR ((void *)0x80076000)
typedef struct { int num; void *func; } SysEnt;   /* (syscall number, handler) */
extern SysEnt D_002C59F0[];     /* [0] kCopy, [1] patch entry, [2..7] patched syscalls */
extern char D_002C5288[];       /* alarm patch code, 0x740 bytes */
extern char D_002C59C8[];       /* patch data copied to 0x82000 */
void func_00239900(int, void *);    /* SetSyscall (syscall 0x74) */
void func_00239910(void *, void *, int);    /* kCopy via syscall 0x5A */
void FlushCache(int);
void *func_00239958(int);       /* patch entry via syscall 0x5B: handler for a syscall */

void InitAlarm(void)
{
    SysEnt *sys;
    unsigned int i;
    if (!(T3_MODE & T_MODE_CMPE)) {
        sys = D_002C59F0;
        func_00239900(sys[0].num, sys[0].func);
        func_00239910(ALARM_PATCH_ADDR, D_002C5288, 0x740);
        func_00239910((void *)0x82000, D_002C59C8, 0x28);
        FlushCache(WRITEBACK_DCACHE);
        FlushCache(INVALIDATE_ICACHE);
        func_00239900(sys[1].num, sys[1].func);
        for (i = 2; i < 8; i++)
            func_00239900(sys[i].num, func_00239958(sys[i].num));
    }
}
