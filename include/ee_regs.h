/* ee_regs.h - EE hardware register addresses used by the SDK library code in src/lib (libdma, libipu,
 * libmpeg, ...). Names follow the SDK's eeregs.h / the EE user's manual. Macros only. */
#ifndef EE_REGS_H
#define EE_REGS_H

#define EE_REG(addr) (*(volatile unsigned int *)(addr))

/* IPU */
#define IPU_CMD_ADDR  0x10002000
#define IPU_CTRL_ADDR 0x10002010
#define IPU_BP_ADDR   0x10002020
#define IPU_TOP_ADDR  0x10002030
#define IPU_CMD_CSC   0x70000000    /* colour space conversion; low bits = macroblock count */

/* DMA channel 3 (fromIPU) and 4 (toIPU) */
#define D3_CHCR_ADDR 0x1000B000
#define D3_MADR_ADDR 0x1000B010
#define D3_QWC_ADDR  0x1000B020
#define D4_CHCR_ADDR 0x1000B400
#define D4_MADR_ADDR 0x1000B410
#define D4_QWC_ADDR  0x1000B420
#define D4_TADR_ADDR 0x1000B430

/* DMA controller */
#define D_CTRL_ADDR 0x1000E000
#define D_STAT_ADDR 0x1000E010
#define D_PCR_ADDR  0x1000E020

/* Dn_CHCR bits */
#define D_CHCR_DIR_FROM_MEM 0x001   /* direction: memory -> peripheral */
#define D_CHCR_MOD_CHAIN    0x004
#define D_CHCR_STR_BIT      0x100   /* start / busy */

/* D_STAT channel interrupt status bits (write 1 to clear) */
#define D_STAT_CIS(ch) (1 << (ch))

#define MAX_QWC 0xFFFF              /* largest QWC of one normal-mode transfer */

#endif /* EE_REGS_H */
