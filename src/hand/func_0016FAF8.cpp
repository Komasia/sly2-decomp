// func_0016FAF8: build a one-register GIF packet (into aqw): FBA_1 = d.
#include "gifs.h"
#include "h2_gs.h"
extern "C" void func_0016FAF8(int cqw, QW *aqw, long d)
{
    GIFS gifs;
    gifs.AllocStatic(cqw, aqw);
    gifs.AddPrimPack(0, 1, GIF_REG_AD);
    gifs.PackAD(GS_REG_FBA_1, d);
    gifs.EndPrim(1);
}
