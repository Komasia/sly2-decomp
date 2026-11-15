// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* sceIpuRestartDMA (libipu): resume the IPU DMA channels saved by sceIpuStopDMA. */
typedef struct {
    unsigned int d4madr;
    unsigned int d4tadr;
    unsigned int d4qwc;
    unsigned int d4chcr;
    unsigned int d3madr;
    unsigned int d3qwc;
    unsigned int d3chcr;
    unsigned int ipubp;
} sceIpuDmaEnv;
#include "ee_regs.h"
void setD3_CHCR(unsigned int);
void setD4_CHCR(unsigned int);
void sceIpuRestartDMA(sceIpuDmaEnv *env)
{
    int bp = env->ipubp & 0x7F;                                         /* IPU_BP.BP: bit position */
    int fifo = ((env->ipubp >> 16) & 3) + ((env->ipubp >> 8) & 0xF);  /* FP + IFC: qwords held in the FIFO */
    unsigned int madr = env->d4madr - fifo * 16;                        /* re-send what the FIFO held */
    unsigned int qwc = env->d4qwc + fifo;

    if (env->d3madr && env->d3qwc) {
        EE_REG(D3_MADR_ADDR) = env->d3madr;
        EE_REG(D3_QWC_ADDR) = env->d3qwc;
        setD3_CHCR(env->d3chcr | D_CHCR_STR_BIT);
    }
    while (*(volatile int *)IPU_CTRL_ADDR < 0);
    EE_REG(IPU_CMD_ADDR) = IPU_CMD_BCLR | bp;   /* empty the FIFO, restore the bit position */
    while (*(volatile int *)IPU_CTRL_ADDR < 0);
    if (madr && qwc) {
        EE_REG(D4_MADR_ADDR) = madr;
        EE_REG(D4_TADR_ADDR) = env->d4tadr;
        EE_REG(D4_QWC_ADDR) = qwc;
        setD4_CHCR(env->d4chcr | D_CHCR_STR_BIT);
    }
}
