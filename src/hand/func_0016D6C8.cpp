// func_0016D6C8: build the GIF packet of a full-screen copy pass (512 x 448 in 16-pixel sprite columns): FRAME_2
// with a write mask from grf, TEX0_2 / TEX1_2, the context-2 scissor / test / alpha, then the sprites; the positions
// of the patchable settings are noted (func_0016D698).
#include "gifs.h"
#include "h2_gs.h"
extern "C" void func_0016D698(int id, GIFS *pgifs, short **pppatch);
extern "C" void func_0016D6C8(GIFS *pgifs, uint grf, short **pppatch)
{
    pgifs->AddPrimPack(0x200, 1, GIF_REG_AD);
    func_0016D698((grf & 4) ? 4 : 5, pgifs, pppatch);
    if (grf & 0x200) {
        pgifs->PackAD(GS_REG_FRAME_2, 0x3FFF02000000L);
    } else if (grf & 0x100) {
        pgifs->PackAD(GS_REG_FRAME_2, 0xFFFFC00002000000L);
    } else {
        uint msk = (grf & 0x800000) ? 0x7FFFFFFF : 0xFFFFFFFF;
        if (grf & 0x400000) msk &= 0xFF7FFFFF;
        if (grf & 0x200000) msk &= 0xFFBFFFFF;
        if (grf & 0x100000) msk &= 0xFFDFFFFF;
        if (grf & 0x80000) msk &= 0xFFEFFFFF;
        if (grf & 0x40000) msk &= 0xFFF0FFFF;
        if (grf & 0x20000) msk &= 0xFFFF7FFF;
        if (grf & 0x10000) msk &= 0xFFFFBFFF;
        pgifs->PackAD(GS_REG_FRAME_2, ((ulong)msk << 32) | 0x2000000);
    }
    func_0016D698((grf & 1) ? 6 : 7, pgifs, pppatch);
    pgifs->PackAD(GS_REG_TEX0_2, 0xEA8200000L);
    pgifs->PackAD(GS_REG_TEX1_2, 1);
    pgifs->PackAD(GS_REG_TEXFLUSH, 0);
    pgifs->PackAD(GS_REG_DTHE, 0);
    pgifs->PackAD(GS_REG_XYOFFSET_2, 0);
    pgifs->PackAD(GS_REG_SCISSOR_2, 0x1C0000002000000L);
    pgifs->PackAD(GS_REG_TEST_2, 0x31001);
    pgifs->PackAD(GS_REG_ALPHA_2, 0x2A);
    pgifs->PackAD(GS_REG_TEXA, 0x8000000000L);
    pgifs->PackAD(GS_REG_RGBAQ, 0x180808080L);
    pgifs->PackAD(GS_REG_PRIM, 0x356);
    pgifs->AddPrimList(4, 0x5353);
    int u = (grf & 0x10) ? 0 : 8;
    for (int x = (grf & 0x40) ? 0 : 8; x < 0x200; x += 0x10, u += 0x10) {
        pgifs->ListUV((u << 4) + 8, 8);
        pgifs->ListXYZ(x << 4, 0, 0);
        pgifs->ListUV(((u + 8) << 4) + 8, 0x1C08);
        pgifs->ListXYZ((x + 8) << 4, 0x1C00, 0);
    }
    pgifs->AddPrimPack(0x200, 1, GIF_REG_AD);
    pgifs->PackAD(GS_REG_SCISSOR_2, 0xE0000002000000L);
}
