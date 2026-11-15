// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_regs.h"
/* _sceMpegPeepBit (libmpeg): look at the next n bits of the bitstream without consuming them. */
typedef struct { char p0[0x828]; int top_invalid; /* 0x828 IPU_TOP must be re-read */ unsigned int cmd; char p1[0x848 - 0x830]; unsigned int top_bits; int top_nbits; } MpegDec;
void _waitIpuIdle(MpegDec *d);
long _sceMpegWaitIpuIdle64(MpegDec *d);
unsigned int _sceMpegPeepBit(MpegDec *d, int n)
{
    if (d->top_invalid || d->top_nbits < n) {
        _waitIpuIdle(d);
        EE_REG(IPU_CMD_ADDR) = IPU_CMD_FDEC;
        d->top_invalid = 0;
        d->cmd = IPU_CMD_FDEC;
        d->top_bits = _sceMpegWaitIpuIdle64(d);
        d->top_nbits = 32;
    }
    return d->top_bits >> (32 - n);
}
