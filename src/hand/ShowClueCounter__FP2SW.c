/* ShowClueCounter: show the clue bottle counter (the world's screen object at SW +0x3BB8, screen object 0x36E) for
 * its few seconds and redraw it. The coin counter's twin (ShowCoinCounter__FP2SW, SW +0x3BAC).
 * name: SafeHouse port (pickup.cpp ShowClueCounter, "orig: 0x00161868 / 0x001618B0 (the coin / clue bottle counters
 * (screen objects 0x36D / 0x36E) shown for their 5 s)"); the argument is the world, as ShowCoinCounter's. */
#include "vtbl.h"
struct LO;
struct SCREENOBJVT { VTENT avte[50]; };
struct SCREENOBJ {
    /* 0x00 */ char pad0[0xC];
    /* 0x0C */ struct SCREENOBJVT *pvt;
};
struct SW {
    /* 0x0000 */ char pad0[0x3BB8];
    /* 0x3BB8 */ struct SCREENOBJ *pscrobjClues;   /* the clue bottle counter */
};
void RefreshScreenObj(struct SCREENOBJ *pscrobj) asm("RefreshScreenObj__FP2LO");

void ShowClueCounter__FP2SW(struct SW *psw)
{
    struct SCREENOBJ *pscrobj = psw->pscrobjClues;
    if (pscrobj) {
        VTENT *pvte = &pscrobj->pvt->avte[49];   /* vt slot 49: show it (-1: for its default time) */
        ((void (*)(void *, int))pvte->pfn)(VT_THIS(pscrobj, pvte), -1);
        RefreshScreenObj(pscrobj);
    }
}
