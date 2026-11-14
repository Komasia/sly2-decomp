#include "clock.h"
#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; char pad2[0x20]; int n30; char pad3[8]; int n3C; int n40; };
struct S { char pad[0x10]; void *p10; int pad2; char a18[0x18]; int n30; float g34; char pad3[8]; int n40; };
void EndChildJob__FPP5AIJOB(void *p);
struct O *func_00205438(void *p, int n);
void SetGuardPursued__FP5GUARDP2LO(void *p, int n);
// name: SafeHouse port (JOBB2::SetB2State)
void SetB2State__5JOBB2i(struct S *p, int n) {
    if (n == p->n30) return;
    EndChildJob__FPP5AIJOB(p->a18);
    p->n30 = n;
    p->g34 = g_clock.t;
    switch (n) {
    case 0:
        { struct O *o = func_00205438(p->p10, 0x9E); VTENT *e = &o->vt[8]; ((void (*)(void *))e->pfn)(VT_THIS(o, e)); }
        SetGuardPursued__FP5GUARDP2LO(p->p10, 0);
        break;
    case 1:
        { struct O *o = func_00205438(p->p10, 0xA5); VTENT *e; o->n30 = p->n40; o->n40 = 1; e = &o->vt[8]; ((void (*)(void *))e->pfn)(VT_THIS(o, e)); }
        break;
    case 2:
        { struct O *o = func_00205438(p->p10, 0x9E); VTENT *e; o->n3C = 1; e = &o->vt[8]; ((void (*)(void *))e->pfn)(VT_THIS(o, e)); }
        break;
    }
}
