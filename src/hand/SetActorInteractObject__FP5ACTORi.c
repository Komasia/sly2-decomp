/* SetActorInteractObject: the actor's interaction of kind 5 (the reach) on an object; null ends a running one (the
 * actor's virtual at vt +0x2C0 with 0). Layout: SafeHouse port (interact.h). */
#include "vtbl.h"

struct LO;
struct INTERACT {
    /* 0x00 */ char pad0[0x8];
    /* 0x08 */ int n4C8;     /* field: SafeHouse port - the running interaction's kind */
};
struct ACTOR {
    /* 0x000 */ char pad0[0xc];
    /* 0x00c */ VTENT *pvt;
    /* 0x010 */ char pad10[0x4c0 - 0x10];
    /* 0x4c0 */ struct INTERACT inter;   /* field: SafeHouse port */
};
void StartInteract(struct INTERACT *pinter, int n, struct LO *plo, int jtl) asm("StartInteract__FP5ACTORii3JTL");

// name: SafeHouse port (SetActorInteractObject)
void SetActorInteractObject__FP5ACTORi(struct ACTOR *pactor, struct LO *plo)
{
    if (plo) {
        StartInteract(&pactor->inter, 5, plo, 0);
    } else if (pactor->inter.n4C8 == 5) {
        VTENT *pvte = &pactor->pvt[0x2c0 / 8];
        ((void (*)(void *, int))pvte->pfn)(VT_THIS(pactor, pvte), 0);
    }
}
