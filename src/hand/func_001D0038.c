#include "vtbl.h"
struct O { int a, b, c; VTENT *vt; };
#include "clock.h"
struct S { char p0[0x14]; float g14; float g18; struct O *po; char p1[0x104-0x20]; int f104; };
void func_001CFD30(struct S *p);
void RemoveRip(struct S *p) asm("RemoveRip__FP3RIP");
void func_001D0038(struct S *p) {
    if (g_clock.t >= p->g14 && p->f104) func_001CFD30(p);
    if (g_clock.t - p->g14 > p->g18) {
        struct O *po = p->po;
        VTENT *e = &po->vt[8];
        ((void (*)(void *))e->pfn)(VT_THIS(po, e));
        RemoveRip(p);
    }
}
