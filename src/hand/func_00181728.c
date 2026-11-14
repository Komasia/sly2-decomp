#include "vtbl.h"
struct S { char pad[0xC]; VTENT *vt; char p2[0x1B8]; void *x1c8; };
void SetShipState__FP2LOi(void *p, int n);
void func_00181728(struct S *p)
{
    VTENT *e;
    SetShipState__FP2LOi(p->x1c8, 1);
    p->x1c8 = 0;
    e = &p->vt[3];
    ((void (*)(void *, int, int, int, int, int))e->pfn)(VT_THIS(p, e), 6, 0, 0, 0, 0);
}
