// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_regs.h"
#define R(a) (*(volatile unsigned int *)(a))
typedef struct { char p0[0x1C0]; int x1C0; char p1[0x828 - 0x1C4]; int top_invalid; } MpegD;
int DIntr(void);
int EIntr(void);
void sceIpuSync(int, int);
/* _clearEach (libmpeg): per-reset cleanup: stop the IPU and SPR DMA channels (DMAC held), clear their counts,
   reset the IPU and mark the cached bitstream word stale. */
void _clearEach(MpegD *d)
{
    int intr;
    d->top_invalid = 1;
    d->x1C0 = 0;
    intr = DIntr();
    R(D_ENABLEW_ADDR) = R(D_ENABLER_ADDR) | D_ENABLE_CPND;
    R(D3_CHCR_ADDR) = 0;
    R(D4_CHCR_ADDR) = 0;
    R(D9_CHCR_ADDR) = 0;
    R(D_ENABLEW_ADDR) = R(D_ENABLER_ADDR) & ~D_ENABLE_CPND;
    if (intr) EIntr();
    R(D3_QWC_ADDR) = 0;
    R(D4_QWC_ADDR) = 0;
    R(D9_QWC_ADDR) = 0;
    R(IPU_CTRL_ADDR) = IPU_CTRL_RST;
    sceIpuSync(0, 0);
}
