/* SetActorInteractObject: the actor's interaction of kind 5 (the reach) on an object; null ends a running one (the
 * actor's virtual at vt +0x2C0 with 0). Layout: SafeHouse port (interact.h). */
#include "actor.h"

struct LO;
void StartInteract(struct INTERACT *pinter, int n, struct LO *plo, int jtl) asm("StartInteract__FP5ACTORii3JTL");

// name: SafeHouse port (SetActorInteractObject)
void SetActorInteractObject__FP5ACTORi(struct ACTOR *pactor, struct LO *plo)
{
    if (plo) {
        StartInteract(&pactor->inter, 5, plo, 0);
    } else if (pactor->inter.kind == 5) {
        VTENT *pvte = &pactor->so.lo.pvt[0x2c0 / 8];
        ((void (*)(void *, int))pvte->pfn)(VT_THIS(pactor, pvte), 0);
    }
}
