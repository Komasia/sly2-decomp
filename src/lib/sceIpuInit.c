// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* sceIpuInit (libipu): reset the IPU and load the default quantiser matrices, VQ CLUT and thresholds. */
typedef int qword __attribute__((mode(TI)));
#include "ee_regs.h"
#define REG(a) (*(volatile unsigned int *)(a))
#define FIFO (*(volatile qword *)0x10007010)     /* IPU input FIFO */
extern volatile qword D_002C8550[5];   /* default intra matrix (4 qwords) + one qword of the flat non-intra matrix */
extern qword D_002C85A0[2];            /* VQ colour look-up table */
#define IPU_SETIQ_NONINTRA 0x08000000
void setD4_CHCR_254C28(int);
#define SYNC() while ((int)REG(IPU_CTRL_ADDR) < 0)     /* IPU_CTRL.BUSY */
void sceIpuInit(void)
{
    setD4_CHCR_254C28(1);       /* stop toIPU DMA */
    REG(IPU_CTRL_ADDR) = IPU_CTRL_RST;
    SYNC();
    REG(IPU_CMD_ADDR) = IPU_CMD_BCLR;
    SYNC();
    FIFO = D_002C8550[0];
    FIFO = D_002C8550[1];
    FIFO = D_002C8550[2];
    FIFO = D_002C8550[3];
    FIFO = D_002C8550[4];
    FIFO = D_002C8550[4];
    FIFO = D_002C8550[4];
    FIFO = D_002C8550[4];
    REG(IPU_CMD_ADDR) = IPU_CMD_SETIQ;
    SYNC();
    REG(IPU_CMD_ADDR) = IPU_CMD_SETIQ | IPU_SETIQ_NONINTRA;
    SYNC();
    FIFO = D_002C85A0[0];
    FIFO = D_002C85A0[1];
    REG(IPU_CMD_ADDR) = IPU_CMD_SETVQ;
    SYNC();
    REG(IPU_CMD_ADDR) = IPU_CMD_SETTH;      /* thresholds 0 */
    SYNC();
    REG(IPU_CTRL_ADDR) = IPU_CTRL_RST;
    SYNC();
    REG(IPU_CMD_ADDR) = IPU_CMD_BCLR;
    SYNC();
}
