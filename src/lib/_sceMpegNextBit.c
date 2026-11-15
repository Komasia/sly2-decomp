// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_regs.h"
/* _sceMpegNextBit (libmpeg): read the next n bits of the bitstream through the IPU (FDEC), keeping the
   32 bits at IPU_TOP cached in top_bits. top_invalid is set after commands that leave IPU_TOP stale. */
typedef struct { char p0[0x828]; int top_invalid; /* 0x828 IPU_TOP must be re-read */ unsigned int cmd; char p1[0x848 - 0x830]; unsigned int top_bits; int top_nbits; } MpegDec;
void _waitIpuIdle(MpegDec *d);
long _sceMpegWaitIpuIdle64(MpegDec *d);
unsigned int _sceMpegNextBit(MpegDec *d, int n)
{
    unsigned int r, c, m;
    _waitIpuIdle(d);
    if (d->top_invalid || d->top_nbits < n) {
        EE_REG(IPU_CMD_ADDR) = IPU_CMD_FDEC;
        d->top_invalid = 0;
        d->cmd = IPU_CMD_FDEC;
        d->top_bits = _sceMpegWaitIpuIdle64(d);
    }
    r = d->top_bits >> (32 - n);
    d->top_nbits = 32;
    c = n | IPU_CMD_FDEC;
    EE_REG(IPU_CMD_ADDR) = c;
    m = c & IPU_CMD_MASK;
    d->cmd = m;
    if (m == IPU_CMD_BDEC || m == IPU_CMD_VDEC || m == IPU_CMD_FDEC)
        d->top_invalid = 0;
    else
        d->top_invalid = 1;
    d->top_bits = _sceMpegWaitIpuIdle64(d);
    return r;
}
