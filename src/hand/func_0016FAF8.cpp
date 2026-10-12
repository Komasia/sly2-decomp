#include "gifs.h"
extern "C" void func_0016FAF8(int cqw, QW *aqw, long d)
{
    GIFS gifs;
    gifs.AllocStatic(cqw, aqw);
    gifs.AddPrimPack(0, 1, 0xE);
    gifs.PackAD(0x4A, d);
    gifs.EndPrim(1);
}
