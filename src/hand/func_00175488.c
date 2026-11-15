typedef int qword __attribute__((mode(TI)));
#include "clock.h"
#include "vtbl.h"
extern qword D_002A2DD0;
struct Q { char pad[0xC]; VTENT *vt; };
struct O { char pad[0xC]; VTENT *vt; char pad2[0x28]; struct Q *q38; int n3C; int n40; };
struct P { char pad[0xA0]; int nA0; char pad2[0x1C]; int nC0; };
struct S { char pad[0x10]; void *p10; int pad2; char a18[0x18]; struct Q *q30; int n34; float g38; struct P *p3C; };
void RemoveLoListener__FP2LOi(struct Q *q, void *p);
void AddLoListener__FP2LOi(struct Q *q, void *p);
void SetGuardActionAim__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(void *p, void *po, int n, qword v);
void EndChildJob__FPP5AIJOB(void *p);
void UnlockJob__FP5AIJOB(struct S *p);
struct O *func_00205438(void *p, int n);
// name: SafeHouse port (JOBACT::SetActState)
void SetActState__6JOBACTi(struct S *p, int n) {
    if (n == p->n34) return;
    if (p->n34 == 0) {
        RemoveLoListener__FP2LOi(p->q30, p->p10);
        p->q30 = 0;
        SetGuardActionAim__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(p->p10, 0, 0, D_002A2DD0);
    }
    EndChildJob__FPP5AIJOB(p->a18);
    p->n34 = n;
    p->g38 = g_clock.t;
    switch (n) {
    case 0:
        {
            struct O *o;
            VTENT *e;
            AddLoListener__FP2LOi(p->q30, p->p10);
            o = func_00205438(p->p10, 0x9F);
            o->q38 = p->q30;
            o->n40 = p->p3C->nC0;
            if (p->p3C->nA0) {
                struct B { char pad[0x30]; qword v; } b;
                struct Q *q = p->q30;
                VTENT *f = &q->vt[0x20];
                SetGuardActionAim__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(p->p10, p->p3C, ((int (*)(void *, void *))f->pfn)(VT_THIS(q, f), &b), b.v);
            }
            e = &o->vt[8]; ((void (*)(void *))e->pfn)(VT_THIS(o, e));
        }
        break;
    case 1:
        {
            struct O *o = func_00205438(p->p10, 0x9D);
            VTENT *e;
            o->n3C = 4;
            o->q38 = p->q30;
            e = &o->vt[8]; ((void (*)(void *))e->pfn)(VT_THIS(o, e));
        }
        break;
    case -1:
        UnlockJob__FP5AIJOB(p);
        break;
    }
}
