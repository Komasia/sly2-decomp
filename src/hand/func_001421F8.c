/* class: ACTOR (SafeHouse scpt.cpp / interact.cpp, orig 0x1421F8: the interaction of kind 5 with the +0x900 reach: the held object placed at it on the object; null ends
 * it when it is the one running - the actor's vt slot 88 with 0). */
#include "actor.h"
struct LO;
void StartInteract__FP5ACTORii3JTL(void *pinter, int kind, struct LO *plo, int n);
void PlaceReachObject__FP5REACHP2LO(void *preach, struct LO *plo);

void func_001421F8(struct ACTOR *pactor, struct LO *plo)
{
    if (plo != 0) {
        StartInteract__FP5ACTORii3JTL(&pactor->inter, 5, plo, 0);
        PlaceReachObject__FP5REACHP2LO(pactor->inter.reach, plo);
    } else if (pactor->inter.kind == 5) {
        VTENT *pvte = &pactor->so.lo.pvt[88];
        ((void (*)(void *, int))pvte->pfn)(VT_THIS(pactor, pvte), 0);
    }
}
