// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_regs.h"
/* _sceMpegFlushBuf (libmpeg): skip n bits of the bitstream (FDEC n) and refresh the cached IPU_TOP word. */
typedef struct { char p0[0x828]; int top_invalid; /* 0x828 IPU_TOP must be re-read */ unsigned int cmd; char p1[0x848 - 0x830]; int top_bits; int top_nbits; } MpegDec;
void _waitIpuIdle(MpegDec *d);
long _sceMpegWaitIpuIdle64(MpegDec *d);
void _sceMpegFlushBuf(MpegDec *d, unsigned int n)
{
    _waitIpuIdle(d);
    n |= IPU_CMD_FDEC;
    EE_REG(IPU_CMD_ADDR) = n;
    n &= IPU_CMD_MASK;
    d->cmd = n;
    if (n == IPU_CMD_BDEC || n == IPU_CMD_VDEC || n == IPU_CMD_FDEC)
        d->top_invalid = 0;
    else
        d->top_invalid = 1;
    d->top_bits = _sceMpegWaitIpuIdle64(d);
    d->top_nbits = 32;
}
