/* UCompleteLoop (Sly 1 shdanim.c): how far through the loop (play time plus pause) the animation is. */
#include "shdanim.h"

float UCompleteLoop(LOOP *ploop)
{
    return (ploop->iframe / ploop->dframe) / ((float)ploop->saa.cframe / ploop->dframe + ploop->dtPause);
}
