/* func_0015DCD8: a screen fade's update (cid 0x74, vt slot 16; SafeHouse update.cpp / hudwidget.cpp): after
 * UpdateLo, once its three phases (in, hold, out) since its start time are over, it removes itself (vt slot 9). */
#include "clock.h"
#include "vtbl.h"
struct FADE {
    /* 0x00 */ char pad0[0xc];
    /* 0x0c */ VTENT *pvt;
    /* 0x10 */ char pad10[0x5c - 0x10];
    /* 0x5c */ float dtIn;
    /* 0x60 */ float dtHold;
    /* 0x64 */ float dtOut;
    /* 0x68 */ float tStart;
};
void UpdateLo__FP2LO(struct FADE *pfade);

void func_0015DCD8(struct FADE *pfade)
{
    VTENT *pvte;
    UpdateLo__FP2LO(pfade);
    if (g_clock.t - pfade->tStart > pfade->dtIn + pfade->dtHold + pfade->dtOut) {
        pvte = &pfade->pvt[9];
        ((void (*)(void *))pvte->pfn)(VT_THIS(pfade, pvte));
    }
}
