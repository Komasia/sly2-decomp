// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* sceIpuStopDMA (libipu): stop both IPU DMA channels and save their state and the IPU bit position into `env`. */
typedef struct {
    unsigned int d4madr, d4tadr, d4qwc, d4chcr;
    unsigned int d3madr, d3qwc, d3chcr;
    unsigned int ipubp, ipuctrl;
} sceIpuDmaEnv;
void setD3_CHCR(unsigned int v);
void setD4_CHCR(unsigned int v);
#include "ee_regs.h"
#define R(a) (*(volatile unsigned int *)(a))
void sceIpuStopDMA(sceIpuDmaEnv *env)
{
    setD4_CHCR(1);                      /* stop toIPU (STR off) */
    env->d4madr = R(D4_MADR_ADDR);
    env->d4tadr = R(D4_TADR_ADDR);
    env->d4qwc = R(D4_QWC_ADDR);
    env->d4chcr = R(D4_CHCR_ADDR);
    while (R(IPU_CTRL_ADDR) & 0xF0)     /* IPU_CTRL.OFC: let the output FIFO drain */
        ;
    setD3_CHCR(0);                      /* stop fromIPU */
    env->d3madr = R(D3_MADR_ADDR);
    env->d3qwc = R(D3_QWC_ADDR);
    env->d3chcr = R(D3_CHCR_ADDR);
    env->ipubp = R(IPU_BP_ADDR);
    env->ipuctrl = R(IPU_CTRL_ADDR);
}
