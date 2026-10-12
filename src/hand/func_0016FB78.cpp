#include "gifs.h"
extern int D_002DEDB0;
extern char D_002DEBE0[];
extern char D_002DECD0[];
extern QW D_002DFB00[];
extern QW D_002DFB20[];
static inline ulong FrameFromDisp(ulong disp)
{
    return ((disp & 0x1FF) << 5) | (((disp >> 16) & 0x3F) << 14);
}
extern "C" void func_0016FB78()
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
    gifs.AddPrimPack(0, 1, 0xE);
    gifs.PackAD(7, FrameFromDisp(*(ulong *)pdisp) | ul);
    gifs.AddPrimEnd();
    GIFS gifs2;
    gifs2.AllocStatic(2, D_002DFB20);
    gifs2.AddPrimPack(0, 1, 0xE);
    gifs2.PackAD(7, FrameFromDisp(*(ulong *)pdispOther) | ul);
    gifs2.AddPrimEnd();
}
