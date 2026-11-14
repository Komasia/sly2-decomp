typedef int qword __attribute__((mode(TI)));
#include "clock.h"
struct VTE { short d; short pad; void (*pfn)(void *); };
struct X { qword a; qword v; };
struct O { char pad[0xC]; struct VTE *vt; char pad2[0x28]; int n38; int n3C; char pad3[0xA8 - 0x40]; void *pA8; int nAC; char pad4[0x10]; int nC0; };
struct S { char pad[0x10]; void *p10; int pad2; char a18[0x18]; void *p30; char pad3[0xC]; qword v40; int n50; float f54; char pad4[8]; qword v60; };
void EndChildJob__FPP5AIJOB(void *p);
struct O *func_00205438(void *p, int n);
qword PosOfLo__FP2LO(void *p);
qword ConvertPos__FP2LOT0G9VU_VECTOR(void *p, int n, qword v);
void func_002562A8(struct X *x);
void SetGoal__7JOBGOTOP4GOAL(void *p, struct X *x);
// name: SafeHouse port (JOBSTATION::SetState)
void SetState__10JOBSTATIONi(struct S *p, int n) {
    struct X x;
    if (n == p->n50) return;
    EndChildJob__FPP5AIJOB(p->a18);
    p->n50 = n;
    p->f54 = g_clock.t;
    switch (n) {
    case 1:
        {
            struct O *o = func_00205438(p->p10, 0xBA);
            qword v = PosOfLo__FP2LO(p->p30);
            struct VTE *e;
            p->v60 = v;
            o->nC0 = 1; o->pA8 = p->p30; o->nAC = 1;
            func_002562A8(&x);
            x.v = v;
            SetGoal__7JOBGOTOP4GOAL(o, &x);
            o->n38 = 0x1C;
            e = &o->vt[8]; e->pfn((char *)o + e->d);
        }
        break;
    case 2:
        {
            struct O *o = func_00205438(p->p10, 0x9E);
            struct VTE *e;
            o->n38 = (int)p->p30;
            o->n3C = 1;
            e = &o->vt[8]; e->pfn((char *)o + e->d);
        }
        break;
    case 0:
        {
            struct O *o = func_00205438(p->p10, 0xBA);
            qword v;
            struct VTE *e;
            p->v60 = PosOfLo__FP2LO(p->p30);
            v = ConvertPos__FP2LOT0G9VU_VECTOR(p->p30, 0, p->v40);
            o->nC0 = 1;
            func_002562A8(&x);
            x.v = v;
            SetGoal__7JOBGOTOP4GOAL(o, &x);
            o->pA8 = p->p30;
            e = &o->vt[8]; e->pfn((char *)o + e->d);
        }
        break;
    }
}
