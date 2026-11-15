/* PS2 GS register addresses (for GIF A+D packing, GIFS::PackAD) and GIF tag values (EE User's Manual / GS User's
 * Manual). */
#ifndef H2_GS_H
#define H2_GS_H

/* GS registers */
#define GS_REG_PRIM         0x00
#define GS_REG_RGBAQ        0x01
#define GS_REG_ST           0x02
#define GS_REG_UV           0x03
#define GS_REG_XYZF2        0x04
#define GS_REG_XYZ2         0x05
#define GS_REG_TEX0_1       0x06
#define GS_REG_TEX0_2       0x07
#define GS_REG_CLAMP_1      0x08
#define GS_REG_CLAMP_2      0x09
#define GS_REG_FOG          0x0a
#define GS_REG_XYZF3        0x0c
#define GS_REG_XYZ3         0x0d
#define GS_REG_TEX1_1       0x14
#define GS_REG_TEX1_2       0x15
#define GS_REG_TEX2_1       0x16
#define GS_REG_TEX2_2       0x17
#define GS_REG_XYOFFSET_1   0x18
#define GS_REG_XYOFFSET_2   0x19
#define GS_REG_PRMODECONT   0x1a
#define GS_REG_PRMODE       0x1b
#define GS_REG_TEXCLUT      0x1c
#define GS_REG_SCANMSK      0x22
#define GS_REG_TEXA         0x3b
#define GS_REG_FOGCOL       0x3d
#define GS_REG_TEXFLUSH     0x3f
#define GS_REG_SCISSOR_1    0x40
#define GS_REG_SCISSOR_2    0x41
#define GS_REG_ALPHA_1      0x42
#define GS_REG_ALPHA_2      0x43
#define GS_REG_DIMX         0x44
#define GS_REG_DTHE         0x45
#define GS_REG_COLCLAMP     0x46
#define GS_REG_TEST_1       0x47
#define GS_REG_TEST_2       0x48
#define GS_REG_PABE         0x49
#define GS_REG_FBA_1        0x4a
#define GS_REG_FBA_2        0x4b
#define GS_REG_FRAME_1      0x4c
#define GS_REG_FRAME_2      0x4d
#define GS_REG_ZBUF_1       0x4e
#define GS_REG_ZBUF_2       0x4f
#define GS_REG_BITBLTBUF    0x50
#define GS_REG_TRXPOS       0x51
#define GS_REG_TRXREG       0x52
#define GS_REG_TRXDIR       0x53
#define GS_REG_FINISH       0x61

/* GS primitive types (PRIM bits 0..2) */
#define GS_PRIM_POINT       0
#define GS_PRIM_LINE        1
#define GS_PRIM_LINESTRIP   2
#define GS_PRIM_TRI         3
#define GS_PRIM_TRISTRIP    4
#define GS_PRIM_TRIFAN      5
#define GS_PRIM_SPRITE      6

/* GIF tag REGS nibble: the A+D register descriptor */
#define GIF_REG_AD          0xe

#endif
