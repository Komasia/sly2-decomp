/* class: ACTOR (SafeHouse scpt.cpp / interact.cpp, orig 0x18DE18: the interaction of EOPID 769, option 752 of class 0x35: Sly's cane reach toward an object, kind 6 (+0x9C0 set) on the object; null ends
 * it when it is the one running - the actor's vt slot 88 with 0). */
#include "vtbl.h"
struct LO;
struct ACTOR {
    /* 0x000 */ char pad0[0xc];
    /* 0x00c */ VTENT *pvt;
    /* 0x010 */ char pad10[0x4c0 - 0x10];
    /* 0x4c0 */ char inter[8];        /* SafeHouse port: the interaction */
    /* 0x4c8 */ int kindInteract;     /* SafeHouse port (n4C8) */
    /* 0x4cc */ char pad4cc[0x9c0 - 0x4cc];
    /* 0x9c0 */ int fCaneReach;
};
void StartInteract__FP5ACTORii3JTL(void *pinter, int kind, struct LO *plo, int n);

void func_0018DE18(struct ACTOR *pactor, struct LO *plo)
{
    if (plo != 0) {
        pactor->fCaneReach = 1;
        StartInteract__FP5ACTORii3JTL(pactor->inter, 6, plo, 0);
    } else if (pactor->kindInteract == 6) {
        VTENT *pvte = &pactor->pvt[88];
        ((void (*)(void *, int))pvte->pfn)(VT_THIS(pactor, pvte), 0);
    }
}
