/* class: ALO (SafeHouse physworld.cpp, orig 0x001F7D10: EOPID 57, option 129 - the fade value +0x12C; <= 0 removes
 * the object (vt slot 9) unless it is a class 0x69, otherwise it is added back (vt slot 8)). */
#include "vtbl.h"
struct ALO {
    /* 0x000 */ char pad0[0xc];
    /* 0x00c */ VTENT *pvt;
    /* 0x010 */ char pad10[0x12c - 0x10];
    /* 0x12c */ float gFade;   /* field: SafeHouse port */
};
int FIsBasicDerivedFrom__FP5BASIC3CID(struct ALO *pbasic, int cid);

void func_001F7D10(struct ALO *palo, int n, float gFade)
{
    VTENT *pvte;
    if (gFade <= 0.0f) {
        if (FIsBasicDerivedFrom__FP5BASIC3CID(palo, 0x69) == 0) {
            pvte = &palo->pvt[9];
            ((void (*)(void *))pvte->pfn)(VT_THIS(palo, pvte));
        }
    } else {
        pvte = &palo->pvt[8];
        ((void (*)(void *))pvte->pfn)(VT_THIS(palo, pvte));
    }
    palo->gFade = gFade;
}
