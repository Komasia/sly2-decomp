/* class: ACTOR (SafeHouse actor.h / pad.cpp EOPID 759: the actor is busy - its AI jobs +0x270 or a script driving it). */

#include "actor.h"
int func_00144068(struct ACTOR *pactor)
{
    int fBusy = 0;
    if (pactor->cJob > 0 || pactor->prunScript != 0) {
        fBusy = 1;
    }
    return fBusy;
}
