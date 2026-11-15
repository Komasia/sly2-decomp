// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
#include "ee_regs.h"
/* _ch4dma (libmpeg): toIPU (DMA channel 4) end-of-transfer handler for _sceMpegCscStoreRefImage; sends a
   buffer larger than one transfer (MAX_QWC) in pieces. Returns 1 when everything has been sent. */
typedef struct { unsigned int qwc; unsigned int addr; } DmaRemain;     /* what is left to send */
static __inline__ void EI(void) { __asm__ volatile("sync\n\tei"); }

int _ch4dma(void *mp, DmaRemain *rem)
{
    unsigned int qwc = MAX_QWC;
    EE_REG(D_STAT_ADDR) = D_STAT_CIS(4);
    if (rem->qwc == 0) {
        EI();
        return 1;
    }
    if (rem->qwc > qwc) {
        EE_REG(D4_MADR_ADDR) = rem->addr;
        EE_REG(D4_QWC_ADDR) = qwc;
        EE_REG(D4_CHCR_ADDR) = D_CHCR_STR_BIT | D_CHCR_DIR_FROM_MEM;
        rem->addr = (rem->addr + qwc * 16) & 0x0fffffff;
        rem->qwc -= qwc;
    } else {
        EE_REG(D4_MADR_ADDR) = rem->addr;
        EE_REG(D4_QWC_ADDR) = rem->qwc;
        EE_REG(D4_CHCR_ADDR) = D_CHCR_STR_BIT | D_CHCR_DIR_FROM_MEM;
        rem->qwc = 0;
    }
    EI();
    return 0;
}
