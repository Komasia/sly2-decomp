#include "clock.h"
#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; char pad2[0x28]; int n38; int n3C; };
struct T { char pad[0xF60]; int nF60; };
struct S { char pad[0x10]; struct T *pt; int pad2; char a18[0x18]; int n30; float g34; int n38; };
void EndChildJob__FPP5AIJOB(void *p);
struct O *func_00205438(void *p, int n);
// name: SafeHouse port (JOBSHOOT::SetShootState)
void SetShootState__8JOBSHOOTi(struct S *p, int n) {
    if (n == p->n30) return;
    EndChildJob__FPP5AIJOB(p->a18);
    if (!p->n30) p->pt->nF60 = 0;
    p->n30 = n;
    p->g34 = g_clock.t;
    if (!n) {
        struct O *o = func_00205438(p->pt, 0x9D);
        VTENT *e;
        o->n3C = 0x11;
        o->n38 = p->n38;
        e = &o->vt[8];
        ((void (*)(void *))e->pfn)(VT_THIS(o, e));
        p->pt->nF60 = 1;
    }
}
