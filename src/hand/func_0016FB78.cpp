// RememberOverlaySourceFrame: build the two TEX0_2 packets that sample the current and the other display buffer.
#include "gifs.h"
#include "h2_gs.h"
extern int D_002DEDB0;
extern char D_002DEBE0[];
extern char D_002DECD0[];
extern QW D_002DFB00[];
extern QW D_002DFB20[];
static inline ulong FrameFromDisp(ulong disp)
{
    return ((disp & 0x1FF) << 5) | (((disp >> 16) & 0x3F) << 14);
}
// name: SafeHouse port (RememberOverlaySourceFrame)
extern "C" void RememberOverlaySourceFrame__Fv()
{
    char *pdisp;
    char *pdispOther;
    if (D_002DEDB0 & 1) {
        pdisp = D_002DEBE0;
        pdispOther = pdisp + 0xF0;
    } else {
        pdisp = D_002DECD0;
        pdispOther = pdisp - 0xF0;
    }
    ulong ul = 0x6A8000000L;
    GIFS gifs;
    gifs.AllocStatic(2, D_002DFB00);
    gifs.AddPrimPack(0, 1, GIF_REG_AD);
    gifs.PackAD(GS_REG_TEX0_2, FrameFromDisp(*(ulong *)pdisp) | ul);
    gifs.AddPrimEnd();
    GIFS gifs2;
    gifs2.AllocStatic(2, D_002DFB20);
    gifs2.AddPrimPack(0, 1, GIF_REG_AD);
    gifs2.PackAD(GS_REG_TEX0_2, FrameFromDisp(*(ulong *)pdispOther) | ul);
    gifs2.AddPrimEnd();
}
