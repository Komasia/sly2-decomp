/* SetAbilityState: a gadget slot's state (0 idle, 1 held, 2 started and done at once) and its time; leaving 1 ends
 * the ability (the actor's vt slot 102), entering 1 or 2 starts it (slot 100). Layout: SafeHouse port (gadget.cpp
 * ABSLOT). */
#include "clock.h"
#include "vtbl.h"

struct ABSLOT {
    /* 0x0 */ int id;      /* field: SafeHouse port */
    /* 0x4 */ int state;   /* field: SafeHouse port */
    /* 0x8 */ float t;     /* field: SafeHouse port */
};
struct ACTOR {
    /* 0x00 */ char pad0[0xc];
    /* 0x0c */ VTENT *pvt;
};

// name: SafeHouse port (SetAbilityState)
void SetAbilityState__FP5ACTORP6ABSLOTi(struct ACTOR *pactor, struct ABSLOT *pslot, int state)
{
    VTENT *pvte;
    int stateOld = pslot->state;
    if (stateOld != state) {
        if (stateOld == 1) {
            pvte = &pactor->pvt[0x330 / 8];   /* EndAbility */
            ((void (*)(void *, int))pvte->pfn)(VT_THIS(pactor, pvte), pslot->id);
        }
        pslot->state = state;
        pslot->t = g_clock.t;
        switch (state) {
        case 2:
            pvte = &pactor->pvt[0x320 / 8];   /* StartAbility */
            ((void (*)(void *, int))pvte->pfn)(VT_THIS(pactor, pvte), pslot->id);
            pslot->state = 0;
            return;
        case 1:
            pvte = &pactor->pvt[0x320 / 8];
            ((void (*)(void *, int))pvte->pfn)(VT_THIS(pactor, pvte), pslot->id);
            break;
        }
    }
}
