/* class: ACTOR (SafeHouse gadget.cpp SetActorPower: the gadgets' power set, clamped to +0x1300 (100)). */

#include "actor.h"
void func_001441C0(struct ACTOR *pactor, int n)
{
    int *pn = pactor->pnPower;
    if (pn != 0) {
        int nMax = pactor->nPowerMax;
        *pn = n >= nMax ? nMax : n;
    }
}
