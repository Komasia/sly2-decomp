/* UpdateSlyDodgeTransitions: the dodge ends (vt slot 88 with 0) when its animation (+0x1030) is over. */
#include "vtbl.h"
struct SLY { int pad[3]; VTENT *vt; char pad2[0x1020]; int pasega1030; };
struct SLYDODGE { struct SLY *psly; };
int FAsegaRetracted(int) asm("FAsegaRetracted__FP5ASEGA");
// name: SafeHouse port (UpdateSlyDodgeTransitions)
void UpdateSlyDodgeTransitions__FP3SLY(struct SLYDODGE *pdodge) {
    if (FAsegaRetracted(pdodge->psly->pasega1030)) {
        struct SLY *psly = pdodge->psly; VTENT *vt = psly->vt;
        ((void (*)(void *, int))vt[88].pfn)(VT_THIS(psly, &vt[88]), 0);
    }
}
