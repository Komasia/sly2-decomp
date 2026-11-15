/* class: ACTOR (SafeHouse scpt.cpp / interact.cpp, orig 0x142340: the interaction of kind 9 on the object; null ends
 * it when it is the one running - the actor's vt slot 88 with 0). */
#include "actor.h"
struct LO;
void StartInteract__FP5ACTORii3JTL(void *pinter, int kind, struct LO *plo, int n);

void func_00142340(struct ACTOR *pactor, struct LO *plo)
{
    if (plo != 0) {
        StartInteract__FP5ACTORii3JTL(&pactor->inter, 9, plo, 0);
    } else if (pactor->inter.kind == 9) {
        VTENT *pvte = &pactor->so.lo.pvt[88];
        ((void (*)(void *, int))pvte->pfn)(VT_THIS(pactor, pvte), 0);
    }
}
