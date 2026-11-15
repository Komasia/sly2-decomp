// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
#include "ee_regs.h"
/* dmaRefImage (libmpeg): fetch the reference blocks for motion compensation into scratchpad RAM with one
   toSPR (DMA channel 9) chain: a REF tag per luma and chroma block, the last one ending the chain. */
#define D9_TADR_ADDR 0x1000D430
#define D9_SADR_ADDR 0x1000D480
#define DMATAG_ID_REFE 0
#define DMATAG_ID_REF  3
typedef struct {
    unsigned int sadr;
    int pad4;
    unsigned int y[4];
    unsigned int c[(0x12C - 0x18) / 4];
    int n;
    char pad130[0x140 - 0x130];
} REFS;
typedef struct {
    char pad0[0x5A0];
    REFS refs[2];
    int cur;
    char pad824[0x87C - 0x824];
    int busy;
} MP;
extern unsigned long D_00451E80[];  /* DMA tag chain buffer */
int DI(void);
void EI(void);
static inline unsigned long mktag(unsigned int addr, int id, int qwc)
{
    return ((unsigned long)addr << 32) | ((unsigned long)id << 28) | qwc;
}
void dmaRefImage(MP *mp)
{
    if (mp->busy == 0) {
        int i;
        int n = mp->refs[mp->cur].n;
        unsigned long *tag = (unsigned long *)(((unsigned int)D_00451E80 & 0x0FFFFFFF) | 0x20000000);
        int intr;
        for (i = 0; i < n; i++) {
            tag[0] = mktag(mp->refs[mp->cur].y[i] & 0x0FFFFFFF, DMATAG_ID_REF, 0x30);
            tag[2] = mktag(mp->refs[mp->cur].c[i] & 0x0FFFFFFF, (i == n - 1) ? DMATAG_ID_REFE : DMATAG_ID_REF, 0x30);
            tag += 4;
        }
        intr = DI();
        __asm__ __volatile__("sync");
        EE_REG(D9_SADR_ADDR) = mp->refs[mp->cur].sadr;
        EE_REG(D9_TADR_ADDR) = (unsigned int)D_00451E80;
        EE_REG(D9_QWC_ADDR) = 0;
        EE_REG(D9_CHCR_ADDR) = D_CHCR_STR_BIT | D_CHCR_MOD_CHAIN | D_CHCR_DIR_FROM_MEM;
        if (intr) EI();
    }
}
