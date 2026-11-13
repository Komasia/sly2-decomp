/* class: CID_74 (vt slot 16 = Update; SafeHouse update.cpp / hudwidget.cpp): after UpdateLo, once its three phases
 * (+0x5C, +0x60, +0x64) since the start time +0x68 are over, its vt slot 9 runs. */
#include "clock.h"
#include "vtbl.h"
struct LO74 {
    /* 0x00 */ char pad0[0xc];
    /* 0x0c */ VTENT *pvt;
    /* 0x10 */ char pad10[0x5c - 0x10];
    /* 0x5c */ float dt5C;
    /* 0x60 */ float dt60;
    /* 0x64 */ float dt64;
    /* 0x68 */ float tStart;
};
void UpdateLo__FP2LO(struct LO74 *plo);

void func_0015DCD8(struct LO74 *plo)
{
    VTENT *pvte;
    UpdateLo__FP2LO(plo);
    if (g_clock.t - plo->tStart > plo->dt5C + plo->dt60 + plo->dt64) {
        pvte = &plo->pvt[9];
        ((void (*)(void *))pvte->pfn)(VT_THIS(plo, pvte));
    }
}
