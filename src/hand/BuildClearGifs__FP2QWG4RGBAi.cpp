// BuildClearGifs (Sly 1 gs.c): a GIF packet (0x25 qwords, into aqw) that fills the screen with rgba as 16 sprite
// columns (blended when the alpha is under 0x80); n picks the GS test (1, 2: the alpha test kinds, 3: the depth
// buffer cleared too).
#include "gifs.h"
#include "h2_gs.h"
struct RGBA {
    uchar bRed; uchar bGreen; uchar bBlue; uchar bAlpha;
    RGBA(const RGBA &rgba);
};
void BuildClearGifs(QW *aqw, RGBA rgba, int n)
{
    GIFS gifs;
    gifs.AllocStatic(0x25, aqw);
    gifs.AddPrimPack(rgba.bAlpha < 0x80 ? 0x46 : GS_PRIM_SPRITE, 1, GIF_REG_AD);
    gifs.PackAD(GS_REG_RGBAQ, (ulong)rgba.bRed | ((ulong)rgba.bGreen << 8) | ((ulong)rgba.bBlue << 16) | ((ulong)rgba.bAlpha << 24));
    ulong test;
    switch (n) {
    case 1: test = 0x31001; break;
    case 2: test = 0x32001; break;
    case 3: test = 0x30000; break;
    }
    gifs.PackAD(GS_REG_TEST_1, test);
    gifs.PackAD(GS_REG_ALPHA_1, 0x44);
    for (int x = 0; x < 0x200; x += 0x20) {
        gifs.PackAD(GS_REG_XYZ2, (ulong)((0x700 + x) * 16) | ((ulong)0x790 << 20));
        gifs.PackAD(GS_REG_XYZ2, (ulong)((0x720 + x) * 16) | ((ulong)0x870 << 20));
    }
    gifs.PackAD(GS_REG_TEST_1, 0x70000);
    gifs.AddPrimEnd();
}
