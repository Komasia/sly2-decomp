/* FUpdatableSaa (Sly 1 shdanim.c): update an animation at most once per frame. */
#include "shdanim.h"
#include "clock.h"

int FUpdatableSaa(SAA *psaa)
{
    if (psaa->tUpdates != g_clock.t)
    {
        psaa->tUpdates = g_clock.t;
        return 1;
    }

    return 0;
}
