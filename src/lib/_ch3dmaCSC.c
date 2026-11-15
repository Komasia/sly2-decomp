// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_regs.h"
/* _ch3dmaCSC (libmpeg): fromIPU (DMA channel 3) end-of-transfer handler for _doCSC2. A colour space
   conversion of more than 1023 macroblocks is done in chunks of 1023: each interrupt queues the DMA and the
   IPU CSC command for the next chunk, the last one for the remainder. */
#define CSC_CHUNK_MB 1023           /* macroblocks per CSC command */
#define RGB32_MB_QWC 64             /* one RGB32 16x16 macroblock = 1 KB */
typedef struct {
    volatile int chunk;     /* chunks done */
    int done;               /* set on error (IPU or DMA still busy) */
    int mbs;                /* macroblocks left for the last chunk */
    unsigned int addr;      /* destination of the next chunk */
    int chunks;             /* total chunks */
} CscState;
static __inline__ void EI(void) { __asm__ volatile("sync\n\tei"); }

int _ch3dmaCSC(void *mp, CscState *csc)
{
    EE_REG(D_STAT_ADDR) = D_STAT_CIS(3);
    csc->chunk++;
    if (EE_REG(D3_QWC_ADDR) != 0 || (EE_REG(D3_CHCR_ADDR) & D_CHCR_STR_BIT)) {
        csc->done = 1;
        EI();
        return 0;
    }
    if (csc->chunk < csc->chunks - 1) {
        EE_REG(D3_MADR_ADDR) = csc->addr;
        EE_REG(D3_QWC_ADDR) = CSC_CHUNK_MB * RGB32_MB_QWC;
        EE_REG(D3_CHCR_ADDR) = D_CHCR_STR_BIT;
        EE_REG(IPU_CMD_ADDR) = IPU_CMD_CSC | CSC_CHUNK_MB;
        csc->addr = (csc->addr + CSC_CHUNK_MB * RGB32_MB_QWC * 16) & 0x0fffffff;
    } else if (csc->chunk == csc->chunks - 1) {
        csc->mbs -= csc->chunk * CSC_CHUNK_MB;
        EE_REG(D3_MADR_ADDR) = csc->addr;
        EE_REG(D3_QWC_ADDR) = csc->mbs << 6;
        EE_REG(D3_CHCR_ADDR) = D_CHCR_STR_BIT;
        EE_REG(IPU_CMD_ADDR) = csc->mbs | IPU_CMD_CSC;
    }
    EI();
    return 0;
}
