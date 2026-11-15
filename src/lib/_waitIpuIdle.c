// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_regs.h"
/* _waitIpuIdle (libmpeg, static helper; each object has its own copy): wait for the IPU if it is busy decoding
   (busy and no start code detected). */
void _sceMpegWaitIpuIdle(void *mp);
void _waitIpuIdle(void *mp)
{
    if ((EE_REG(IPU_CTRL_ADDR) & (IPU_CTRL_BUSY | IPU_CTRL_ECD)) == IPU_CTRL_BUSY)
        _sceMpegWaitIpuIdle(mp);
}
