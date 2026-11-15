// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_regs.h"
/* _sceMpegWaitIpuIdle (libmpeg): wait while the IPU is busy. If it is starving for input during a
   bitstream command (fewer than 32 bits in its FIFO and the toIPU DMA done) or after a while, ask the
   application for more data (Nodata callback); give up if decoding was stopped. */
#define IPU_FIFO_BITS(bp) ((((bp) & 0xFF00) >> 1) + (((bp) & 0x30000) >> 9) - ((bp) & 0x7F))  /* IFC, FP, BP */
typedef struct {
    char p0[0x82C]; unsigned int cmd;
    char p830[0x868 - 0x830]; void *mp;
    char p86C[0x878 - 0x86C]; int stop;
} MpegDec;
#define R(a) (*(volatile unsigned int *)(a))
int _sceMpegDispatchMpegCbNodata(void *mp);
void _sceMpegStopIpuDma(void);
void _sceMpegWaitIpuIdle(MpegDec *d)
{
    int cnt = 0;

    while ((R(IPU_CTRL_ADDR) & (IPU_CTRL_BUSY | IPU_CTRL_ECD)) == IPU_CTRL_BUSY) {
        unsigned int bp = R(IPU_BP_ADDR);
        unsigned int cmd = d->cmd;
        unsigned int n = IPU_FIFO_BITS(bp);
        if ((cmd == IPU_CMD_BDEC || cmd == IPU_CMD_VDEC || cmd == IPU_CMD_FDEC) && n < 32 && R(D4_QWC_ADDR) == 0) {
            _sceMpegDispatchMpegCbNodata(d->mp);
            if (d->stop) { _sceMpegStopIpuDma(); break; }
            cnt = 0;
        }
        if (cnt++ > 5000) {
            _sceMpegDispatchMpegCbNodata(d->mp);
            if (d->stop) { _sceMpegStopIpuDma(); break; }
            cnt = 0;
        }
    }
    d->cmd = 0;
}
