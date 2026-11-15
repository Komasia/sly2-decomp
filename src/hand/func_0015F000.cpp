// func_0015F000: when fClip, reset the GS scissor to the whole screen (0..511 x 0..223) after drawing clipped text.
#include "gifs.h"
#include "h2_gs.h"
extern "C" void func_0015F000(void *pfont, int fClip, GIFS *pgifs)
{
    if (fClip) {
        pgifs->AddPrimPack(0, 1, GIF_REG_AD);
        pgifs->PackAD(GS_REG_SCISSOR_1, 0xdf000001ff0000L);
    }
}
