// BlendPrevFrame (Sly 1 frm.c BlendPrevFrame): unless disabled (D_002DEB24 / D_003E12C8), draw the previous display
// buffer over the frame as 16 textured sprite strips of 32 pixels, blended (motion blur).
#include "gifs.h"
#include "h2_gs.h"
struct sceDmaChan;
extern int D_002DEB24;
extern int D_003E12C8;
extern int D_002DEDB0;
extern int D_002DEDB8;
extern char D_002DEBE0[];
extern char D_002DECD0[];
extern sceDmaChan *g_pdcGif;
void SendDmaSyncGsFinish(sceDmaChan *pch, QW *pqw);
static inline ulong Tex0FromDisp(ulong disp)
{
    return ((disp & 0x1FF) << 5) | (((disp >> 16) & 0x3F) << 14) | (((disp >> 24) & 0x3F) << 20);
}
// name: Sly 1 frm.c BlendPrevFrame (suggested by h2)
extern "C" void BlendPrevFrame__Fv()
{
    if (D_002DEB24 || D_003E12C8)
        return;
    GIFS gifs;
    QW aqw[0x64];
    gifs.AllocStatic(0x64, aqw);
    gifs.AddDmaCnt();
    gifs.AddPrimPack(0, 1, GIF_REG_AD);
    gifs.PackAD(GS_REG_TEXFLUSH, 0);
    ulong *pdisp = (ulong *)((D_002DEDB0 & 1) ? D_002DEBE0 : D_002DECD0);   /* the other buffer's DISPFB */
    gifs.PackAD(GS_REG_TEX0_1, Tex0FromDisp(*pdisp) | 0x2A8000000L);
    gifs.PackAD(GS_REG_TEX1_1, 0x61);
    gifs.PackAD(GS_REG_CLAMP_1, 5);
    gifs.PackAD(GS_REG_TEST_1, 0x33001);
    gifs.PackAD(GS_REG_ALPHA_1, 0x3000000064L);
    gifs.PackAD(GS_REG_RGBAQ, 0x3F80000080808080L);
    gifs.PackAD(GS_REG_SCISSOR_1, 0xDE000101FF0000L);
    gifs.AddPrimPack(0x156, 2, 0x43);
    int v = (D_002DEDB8 & 1) ? 0 : 0x10;   /* the field's half-line offset */
    for (int x = 0; x < 0x200; x += 0x20) {
        gifs.PackUV((x << 4) | 8, v);
        gifs.PackXYZF((x + 0x700) << 4, 0x7900, 0, 0);
        gifs.PackUV(((x + 0x20) << 4) | 8, v + 0xE00);
        gifs.PackXYZF((x + 0x720) << 4, 0x8700, 0, 0);
    }
    gifs.AddPrimPack(0, 1, GIF_REG_AD);
    gifs.PackAD(GS_REG_SCISSOR_1, 0xDF000001FF0000L);
    gifs.PackAD(GS_REG_FINISH, 0);
    gifs.AddPrimEnd();
    gifs.AddDmaEnd();
    gifs.EndDmaCnt();
    SendDmaSyncGsFinish(g_pdcGif, aqw);
}
