/* InitCircler (Sly 1 shdanim.c): circular texture motion from the level settings. */
#include "shdanim.h"

void InitSaa(SAA *psaa, SAAF *psaaf);

void InitCircler(CIRCLER *pcircler, SAAF *psaaf)
{
    InitSaa(&pcircler->saa, psaaf);

    pcircler->radsSpeed = psaaf->dtLoopMin;
    pcircler->radius = psaaf->dtLoopMax;
    pcircler->duCenter = psaaf->dtPauseMin;
    pcircler->dvCenter = psaaf->dtPauseMax;
}
