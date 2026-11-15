/* class: ACTOR, vt slot 78 (the camera-focus change; SafeHouse cmworld.cpp / gadget.cpp "the players' slot 78
 * 0x144480"): the base SetCmFocusObject, then vt slot 105 (UpdateAbilityDisplay: Bentley's Hover Pack shown while
 * he is the current player); losing the focus retracts the active ability's animation and clears the ability. */
#include "actor.h"
#include "vtbl.h"

struct ASEGA;

#define VTS_UpdateAbilityDisplay 105   /* SafeHouse gadget.cpp */

void SetCmFocusObject__FP2LOi(struct ACTOR *pactor, int fFocus);
void RetractAsegaPp__FPP5ASEGA(struct ASEGA **ppasega);

void func_00144480(struct ACTOR *pactor, int fFocus)
{
    VTENT *pvte;
    SetCmFocusObject__FP2LOi(pactor, fFocus);
    pvte = &pactor->so.lo.pvt[VTS_UpdateAbilityDisplay];
    ((void (*)(void *))pvte->pfn)(VT_THIS(pactor, pvte));
    if (!fFocus) {
        RetractAsegaPp__FPP5ASEGA(&pactor->pasegaAbility);
        pactor->idAbility = -1;
    }
}
