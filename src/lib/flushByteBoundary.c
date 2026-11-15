// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_regs.h"
void _waitIpuIdle_254488(void *d);
void func_002544C0(void *d, int n);    /* skip n bits */

/* flushByteBoundary (libmpeg): skip to the next byte boundary of the bitstream (IPU_BP bit position). */
void flushByteBoundary(void *d)
{
    int n;
    _waitIpuIdle_254488(d);
    n = -(EE_REG(IPU_BP_ADDR) & 7) & 7;
    if (n) func_002544C0(d, n);
}
