/* class: ACTOR (SafeHouse sly.cpp / gadget.cpp: the health counter set, clamped to the capacity +0xDFC). */

#include "actor.h"
void func_00144188(struct ACTOR *pactor, int c)
{
    int cMax = pactor->cHealthMax;
    *pactor->pcHealth = c >= cMax ? cMax : c;
}
