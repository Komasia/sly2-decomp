// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_kernel.h"
/* InitExecPS2 (libkernel): on kernels that need it (PatchIsNeeded), install the ExecPS2 patch the same way
   InitAlarm installs the alarm patch. */
#define EXECPS2_PATCH_ADDR ((void *)0x80074000)
typedef struct { int num; void *func; } SysEnt;   /* (syscall number, handler) */
extern SysEnt D_002C5268[];     /* [0] kCopy, [1] patch entry, [2] patched syscall */
extern char D_002C4AC0[];       /* ExecPS2 patch code, 0x7A8 bytes */
int PatchIsNeeded(void);
void func_00239718(int, void *);    /* SetSyscall (syscall 0x74) */
void func_00239728(void *, void *, int);    /* kCopy via syscall 0x5A */
void FlushCache(int);
void *func_00239770(int);       /* patch entry via syscall 0x5B */

void InitExecPS2(void)
{
    SysEnt *sys;
    unsigned int i;
    if (PatchIsNeeded()) {
        sys = D_002C5268;
        func_00239718(sys[0].num, sys[0].func);
        func_00239728(EXECPS2_PATCH_ADDR, D_002C4AC0, 0x7A8);
        FlushCache(WRITEBACK_DCACHE);
        FlushCache(INVALIDATE_ICACHE);
        func_00239718(sys[1].num, sys[1].func);
        for (i = 2; i < 3; i++)
            func_00239718(sys[i].num, func_00239770(sys[i].num));
    }
}
