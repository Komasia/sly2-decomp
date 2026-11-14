#include "vtbl.h"
struct O { int a, b, c; VTENT *vt; char pad[0x18]; unsigned long fl; };
struct S { char pad[0x1AD8]; struct O *po; void *pv; };
void ApplyAseg__FP4ASEGiiffPP5ASEGA(void *a, struct O *po, int c, int d, float f, float g);
void func_001B9DB8(struct S *p, int x)
{
    if (!((int)(p->po->fl >> 60) & 1)) {
        VTENT *e = &p->po->vt[29];
        ((void (*)(void *, int))e->pfn)(VT_THIS(p->po, e), x);
        ApplyAseg__FP4ASEGiiffPP5ASEGA(p->pv, p->po, 0, 0, 0.0f, 1.0f);
    }
}
