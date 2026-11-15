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
/* IPU_CMD commands (top nibble) */
#define IPU_CMD_BCLR  0x00000000    /* clear the input FIFO */
#define IPU_CMD_IDEC  0x10000000    /* intra decode */
#define IPU_CMD_BDEC  0x20000000    /* block decode */
#define IPU_CMD_VDEC  0x30000000    /* variable-length decode */
#define IPU_CMD_FDEC  0x40000000    /* fixed-length decode (read bits) */
#define IPU_CMD_SETIQ 0x50000000    /* load a quantiser matrix */
#define IPU_CMD_SETVQ 0x60000000
#define IPU_CMD_CSC   0x70000000    /* colour space conversion; low bits = macroblock count */
#define IPU_CMD_PACK  0x80000000
#define IPU_CMD_SETTH 0x90000000
#define IPU_CMD_MASK  0xF0000000
/* IPU_CTRL bits */
#define IPU_CTRL_ECD  0x00004000    /* error code (start code) detected */
#define IPU_CTRL_RST  0x40000000
#define IPU_CTRL_BUSY 0x80000000
#define IPU_CTRL_MP1  0x00800000    /* MPEG-1 bitstream */

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
#define D_ENABLER_ADDR 0x1000F520   /* DMA hold state (read) */
#define D_ENABLEW_ADDR 0x1000F590   /* DMA hold control (write) */
#define D_ENABLE_CPND  0x10000      /* suspend all channels */
#define D9_CHCR_ADDR 0x1000D400     /* toSPR */
#define D9_QWC_ADDR  0x1000D420

/* Dn_CHCR bits */
#define D_CHCR_DIR_FROM_MEM 0x001   /* direction: memory -> peripheral */
#define D_CHCR_MOD_CHAIN    0x004
#define D_CHCR_STR_BIT      0x100   /* start / busy */

/* D_STAT channel interrupt status bits (write 1 to clear) */
#define D_STAT_CIS(ch) (1 << (ch))

#define MAX_QWC 0xFFFF              /* largest QWC of one normal-mode transfer */

/* GS privileged registers (64-bit) */
#define GS_PMODE_ADDR    0x12000000
#define GS_SMODE2_ADDR   0x12000020
#define GS_DISPFB1_ADDR  0x12000070
#define GS_DISPLAY1_ADDR 0x12000080
#define GS_DISPFB2_ADDR  0x12000090
#define GS_DISPLAY2_ADDR 0x120000A0
#define GS_EXTDATA_ADDR  0x120000C0
#define GS_BGCOLOR_ADDR  0x120000E0
#define GS_CSR_ADDR      0x12001000
#define GS_IMR_ADDR      0x12001010

#endif /* EE_REGS_H */
