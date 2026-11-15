// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_kernel.h"
/* InitTLBFunctions (libkernel): install the TLB patch (PutTLBEntry/SetTLBEntry/... syscalls) the same way
   InitAlarm installs the alarm patch, and remember the handler of syscall 3. */
#define TLB_PATCH_ADDR ((void *)0x80075000)
typedef struct { int num; void *func; } SysEnt;   /* (syscall number, handler) */
extern SysEnt D_002C5DE8[8];    /* [0] kCopy, [1] patch entry, [2] installed as is, [3..7] patched */
extern int D_002C5DE0;          /* handler of syscall 3 */
extern char D_002C5A68[];       /* TLB patch code, 0x330 bytes */
void func_0023B280(int, void *);    /* SetSyscall (syscall 0x74) */
void *func_0023B270(int);       /* patch entry via syscall 0x5B */
void func_0023B228(void *, void *, int);    /* kCopy via syscall 0x5A */
void FlushCache(int);

void InitTLBFunctions(void)
{
    unsigned int i;
    func_0023B280(D_002C5DE8[0].num, D_002C5DE8[0].func);
    func_0023B228(TLB_PATCH_ADDR, D_002C5A68, 0x330);
    FlushCache(WRITEBACK_DCACHE);
    FlushCache(INVALIDATE_ICACHE);
    func_0023B280(D_002C5DE8[1].num, D_002C5DE8[1].func);
    func_0023B280(D_002C5DE8[2].num, D_002C5DE8[2].func);
    for (i = 3; i < 8; i++)
        func_0023B280(D_002C5DE8[i].num, func_0023B270(D_002C5DE8[i].num));
    D_002C5DE0 = (int)func_0023B270(3);
}
