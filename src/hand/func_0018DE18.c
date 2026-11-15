/* class: ACTOR (SafeHouse scpt.cpp / interact.cpp, orig 0x18DE18: the interaction of EOPID 769, option 752 of class 0x35: Sly's cane reach toward an object, kind 6 (+0x9C0 set) on the object; null ends
 * it when it is the one running - the actor's vt slot 88 with 0). */
#include "actor.h"
struct LO;
void StartInteract__FP5ACTORii3JTL(void *pinter, int kind, struct LO *plo, int n);

void func_0018DE18(struct ACTOR *pactor, struct LO *plo)
{
    if (plo != 0) {
        pactor->inter.f500 = 1;   /* +0x9C0 */
        StartInteract__FP5ACTORii3JTL(&pactor->inter, 6, plo, 0);
    } else if (pactor->inter.kind == 6) {
        VTENT *pvte = &pactor->so.lo.pvt[88];
        ((void (*)(void *, int))pvte->pfn)(VT_THIS(pactor, pvte), 0);
    }
}
