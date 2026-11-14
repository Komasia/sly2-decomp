/* class: ACTOR (SafeHouse scpt.cpp / interact.cpp, orig 0x1421F8: the interaction of kind 5 with the +0x900 reach: the held object placed at it on the object; null ends
 * it when it is the one running - the actor's vt slot 88 with 0). */
#include "vtbl.h"
struct LO;
struct ACTOR {
    /* 0x000 */ char pad0[0xc];
    /* 0x00c */ VTENT *pvt;
    /* 0x010 */ char pad10[0x4c0 - 0x10];
    /* 0x4c0 */ char inter[8];        /* SafeHouse port: the interaction */
    /* 0x4c8 */ int kindInteract;     /* SafeHouse port (n4C8) */
    /* 0x4cc */ char pad4cc[0x900 - 0x4cc];
    /* 0x900 */ char reach[4];        /* SafeHouse port: inter.reach */
};
void StartInteract__FP5ACTORii3JTL(void *pinter, int kind, struct LO *plo, int n);
void PlaceReachObject__FP5REACHP2LO(void *preach, struct LO *plo);

void func_001421F8(struct ACTOR *pactor, struct LO *plo)
{
    if (plo != 0) {
        StartInteract__FP5ACTORii3JTL(pactor->inter, 5, plo, 0);
        PlaceReachObject__FP5REACHP2LO(pactor->reach, plo);
    } else if (pactor->kindInteract == 5) {
        VTENT *pvte = &pactor->pvt[88];
        ((void (*)(void *, int))pvte->pfn)(VT_THIS(pactor, pvte), 0);
    }
}
