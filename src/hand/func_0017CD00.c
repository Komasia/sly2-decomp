#include "clock.h"
#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; char pad2[0x2C]; int n3C; };
struct S { char pad[0x10]; void *p10; int pad2; char a18[0x18]; int n30; float g34; };
void EndChildJob__FPP5AIJOB(void *p);
struct O *func_00205438(void *p, int n);
// name: SafeHouse port (JOBRAIL::SetRailState)
void SetRailState__7JOBRAILi(struct S *p, int n) {
    if (n == p->n30) return;
    EndChildJob__FPP5AIJOB(p->a18);
    p->n30 = n;
    p->g34 = g_clock.t;
    switch (n) {
    case 1:
        { struct O *o = func_00205438(p->p10, 0x9D); VTENT *e; o->n3C = 2; e = &o->vt[8]; ((void (*)(void *))e->pfn)(VT_THIS(o, e)); }
        break;
    case 0:
        { struct O *o = func_00205438(p->p10, 0x9D); VTENT *e; o->n3C = 9; e = &o->vt[8]; ((void (*)(void *))e->pfn)(VT_THIS(o, e)); }
        break;
    }
}
