// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_regs.h"
typedef struct { int type; int data[7]; } CB;
typedef struct { char p0[0x868]; void *mp; } D;
void _sceMpegError(D *d, const char *msg);
int _sceMpegDispatchMpegCallback(void *mp, CB *cb);
int DIntr(void);
int EIntr(void);
/* _sceMpegErrorBdec (libmpeg): the IPU found a start code inside a block (BDEC error): report it, reset the
   IPU between the StopDMA/RestartDMA callbacks and abort the fromIPU transfer. */
void _sceMpegErrorBdec(D *d)
{
    CB cb;
    int intr;

    _sceMpegError(d, "Error code detected(BDEC)");
    cb.type = 2;    /* sceMpegCbStopDMA */
    _sceMpegDispatchMpegCallback(d->mp, &cb);
    EE_REG(IPU_CTRL_ADDR) = IPU_CTRL_RST;
    cb.type = 3;    /* sceMpegCbRestartDMA */
    _sceMpegDispatchMpegCallback(d->mp, &cb);
    intr = DIntr();
    EE_REG(D_ENABLEW_ADDR) = EE_REG(D_ENABLER_ADDR) | D_ENABLE_CPND;
    EE_REG(D3_CHCR_ADDR) = 0;
    EE_REG(D_ENABLEW_ADDR) = EE_REG(D_ENABLER_ADDR) & ~D_ENABLE_CPND;
    if (intr) EIntr();
    EE_REG(D3_QWC_ADDR) = 0;
}
