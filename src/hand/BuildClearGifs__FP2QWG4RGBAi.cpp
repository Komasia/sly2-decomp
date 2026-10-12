#include "gifs.h"
struct RGBA {
    uchar bRed; uchar bGreen; uchar bBlue; uchar bAlpha;
    RGBA(const RGBA &rgba);
};
void BuildClearGifs(QW *aqw, RGBA rgba, int n)
{
    GIFS gifs;
    gifs.AllocStatic(0x25, aqw);
    gifs.AddPrimPack(rgba.bAlpha < 0x80 ? 0x46 : 6, 1, 0xE);
    gifs.PackAD(1, (ulong)rgba.bRed | ((ulong)rgba.bGreen << 8) | ((ulong)rgba.bBlue << 16) | ((ulong)rgba.bAlpha << 24));
    ulong test;
    switch (n) {
    case 1: test = 0x31001; break;
    case 2: test = 0x32001; break;
    case 3: test = 0x30000; break;
    }
    gifs.PackAD(0x47, test);
    gifs.PackAD(0x42, 0x44);
    for (int x = 0; x < 0x200; x += 0x20) {
        gifs.PackAD(5, (ulong)((0x700 + x) * 16) | ((ulong)0x790 << 20));
        gifs.PackAD(5, (ulong)((0x720 + x) * 16) | ((ulong)0x870 << 20));
    }
    gifs.PackAD(0x47, 0x70000);
    gifs.AddPrimEnd();
}
