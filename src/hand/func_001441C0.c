/* class: ACTOR (SafeHouse gadget.cpp SetActorPower: the gadgets' power set, clamped to +0x1300 (100)). */

#include "actor.h"
// name: SafeHouse port (gadget.h SetActorPower, orig 0x1441C0)
void SetActorPower__FP5ACTORi(struct ACTOR *pactor, int n)
{
    int *pn = pactor->pnPower;
    if (pn != 0) {
        int nMax = pactor->nPowerMax;
        *pn = n >= nMax ? nMax : n;
    }
}
