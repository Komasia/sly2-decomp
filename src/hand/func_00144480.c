/* class: ACTOR, vt slot 78 (the camera-focus change; SafeHouse cmworld.cpp / gadget.cpp "the players' slot 78
 * 0x144480"): the base SetCmFocusObject, then vt slot 105 (UpdateAbilityDisplay: Bentley's Hover Pack shown while
 * he is the current player); losing the focus retracts the active ability's animation and clears the ability. */
#include "vtbl.h"

struct ASEGA;
struct ACTOR {
    /* 0x0000 */ char pad0[0xc];
    /* 0x000c */ VTENT *pvt;
    /* 0x0010 */ char pad10[0x1310 - 0x10];
    /* 0x1310 */ struct ASEGA *pasegaAbility;   /* field: SafeHouse port - the active cane animation */
    /* 0x1314 */ int idAbility;                 /* field: SafeHouse port - the active ability, -1 after clearing */
};

#define VTS_UpdateAbilityDisplay 105   /* SafeHouse gadget.cpp */

void SetCmFocusObject__FP2LOi(struct ACTOR *pactor, int fFocus);
void RetractAsegaPp__FPP5ASEGA(struct ASEGA **ppasega);

void func_00144480(struct ACTOR *pactor, int fFocus)
{
    VTENT *pvte;
    SetCmFocusObject__FP2LOi(pactor, fFocus);
    pvte = &pactor->pvt[VTS_UpdateAbilityDisplay];
    ((void (*)(void *))pvte->pfn)(VT_THIS(pactor, pvte));
    if (!fFocus) {
        RetractAsegaPp__FPP5ASEGA(&pactor->pasegaAbility);
        pactor->idAbility = -1;
    }
}
