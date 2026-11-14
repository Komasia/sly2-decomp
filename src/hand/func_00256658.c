/* class: a Splice library object (vtable entries at 0x2CA5F4 / 0x2CA674, the classes around 0x2564E0): its +0x10
 * CDynArray freed, then each object of its +0x28 list told through its vtable entry 1 (+0x8 vtable, next at +0x4). */
#include "so.h"

typedef struct LINK {
    /* 0x0 */ int n0;
    /* 0x4 */ struct LINK *pnext;
    /* 0x8 */ VTE *pvt;
} LINK;
typedef struct SPLOBJ {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ char dynarray[0x18];   /* CDynArray */
    /* 0x28 */ LINK *plink;
} SPLOBJ;

void Free__9CDynArray(void *pdynarray);

void func_00256658(SPLOBJ *p)
{
    LINK *plink;

    Free__9CDynArray(p->dynarray);
    for (plink = p->plink; plink != 0; plink = plink->pnext) {
        VTE *pvt = plink->pvt;
        ((void (*)(void *))pvt[1].pfn)((char *)plink + pvt[1].d);
    }
}
