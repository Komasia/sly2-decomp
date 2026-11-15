// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
#include "ee_regs.h"
int DIntr(void);
int EIntr(void);
#define REG(a) (*(volatile unsigned int *)(a))
/* _sceMpegStopIpuDma (libmpeg): abort the IPU transfers: stop DMA channels 3 and 4 while the DMAC is held,
   clear their counts and reset the IPU. */
void _sceMpegStopIpuDma(void)
{
  int intr = DIntr();
  REG(D_ENABLEW_ADDR) = REG(D_ENABLER_ADDR) | D_ENABLE_CPND;
  REG(D3_CHCR_ADDR) = 0;
  REG(D4_CHCR_ADDR) = 0;
  REG(D_ENABLEW_ADDR) = REG(D_ENABLER_ADDR) & ~D_ENABLE_CPND;
  if (intr) EIntr();
  REG(D3_QWC_ADDR) = 0;
  REG(D4_QWC_ADDR) = 0;
  REG(IPU_CTRL_ADDR) = IPU_CTRL_RST;
}
