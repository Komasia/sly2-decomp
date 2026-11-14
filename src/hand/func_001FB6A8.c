/* class: CSnd, a sound (SafeHouse sound.cpp, orig 0x1FB658 + 0x1FB6A8: on the active list D_003DD08C while any bit
 * is set, holding a reference - its vt slot 1). */
#include "vtbl.h"
struct DL;
struct CSND {
    /* 0x00 */ char pad0[0xc];
    /* 0x0c */ VTENT *pvt;
};
extern struct DL D_003DD08C;   /* the active sounds */
int FFindDlEntry__FP2DLPv(struct DL *pdl, void *pv);
void AppendDlEntry__FP2DLPv(struct DL *pdl, void *pv);

void func_001FB6A8(struct CSND *psnd)
{
    if (FFindDlEntry__FP2DLPv(&D_003DD08C, psnd) == 0) {
        VTENT *pvte = &psnd->pvt[1];
        ((void (*)(void *))pvte->pfn)(VT_THIS(psnd, pvte));
        AppendDlEntry__FP2DLPv(&D_003DD08C, psnd);
    }
}
