/* InitScroller (Sly 1 shdanim.c): scroll speeds and offsets from the level settings, unit scale. */
#include "shdanim.h"

void InitSaa(SAA *psaa, SAAF *psaaf);

void InitScroller(SCROLLER *pscroller, SAAF *psaaf)
{
    InitSaa(&pscroller->saa, psaaf);

    pscroller->duSpeed = psaaf->dtLoopMin;
    pscroller->dvSpeed = psaaf->dtLoopMax;
    pscroller->du = psaaf->dtPauseMin;
    pscroller->dv = psaaf->dtPauseMax;

    pscroller->sv = 1.0f;
    pscroller->su = 1.0f;
}
