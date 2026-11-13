/* ShowCoinCounter: the coin counter (the screen object at SW +0x3BAC) shown (its virtual ShowScreenObj, vt slot 49,
 * with -1) and its idle time started again (RefreshScreenObj) so it stays up for its 5 s.
 * Source: SafeHouse port (pickup.cpp). */
#include "vtbl.h"

struct LO {
    /* 0x00 */ char pad0[0xc];
    /* 0x0c */ VTENT *pvt;
};
struct SW {
    /* 0x0000 */ char pad0[0x3bac];
    /* 0x3bac */ struct LO *ploCoinCounter;   /* SafeHouse: screen object 0x36D */
};
void RefreshScreenObj__FP2LO(struct LO *plo);

// name: SafeHouse port (ShowCoinCounter)
void ShowCoinCounter__FP2SW(struct SW *psw)
{
    struct LO *plo = psw->ploCoinCounter;
    if (plo != 0) {
        VTENT *pvte = &plo->pvt[0x188 / 8];
        ((void (*)(void *, int))pvte->pfn)(VT_THIS(plo, pvte), -1);
        RefreshScreenObj__FP2LO(plo);
    }
}
