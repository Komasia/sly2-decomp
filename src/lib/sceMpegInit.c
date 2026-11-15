// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_regs.h"
/* sceMpegInit (libmpeg): stop both IPU DMA channels and reset the IPU. */
int DIntr(void);
int EIntr(void);
void sceIpuInit(void);
#define REG(a) (*(volatile unsigned int *)(a))
int sceMpegInit(void)
{
  int s = DIntr();
  REG(D_ENABLEW_ADDR) = REG(D_ENABLER_ADDR) | D_ENABLE_CPND;       /* hold all DMA channels */
  REG(D3_CHCR_ADDR) = REG(D3_CHCR_ADDR) & ~D_CHCR_STR_BIT;         /* stop fromIPU */
  REG(D4_CHCR_ADDR) = REG(D4_CHCR_ADDR) & ~D_CHCR_STR_BIT;         /* stop toIPU */
  REG(D_ENABLEW_ADDR) = REG(D_ENABLER_ADDR) & ~D_ENABLE_CPND;
  if (s) EIntr();
  REG(D3_QWC_ADDR) = 0;
  REG(D4_QWC_ADDR) = 0;
  sceIpuInit();
  return 1;
}
