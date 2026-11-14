typedef int qword __attribute__((mode(TI)));
#include "clock.h"
struct VTE { short d; short pad; void *pfn; };
struct O { char pad[0xC]; struct VTE *vt; };
struct R { int n0; int a[11]; };
struct U { char pad[0x1C]; float g1C; };
struct W { char pad[0xA0]; int nA0; };
struct T { char pad[0x58]; struct W *p58; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x48]; struct O *p5C; int n60; struct U *p64; };
void GetTarget__5JOBB1P12LAUNCHTARGETP6VECTORT2(struct S *p, struct R *r, qword *a, qword *b);
qword PosConvertXfs__FP2XFT0G9VU_VECTOR(int a, int b, qword q);
qword VecConvertXfs__FP2XFT0G9VU_VECTOR(int a, int b, qword q);
void SetGoal__10CTRLTARGETG9VU_VECTORT1(struct U *u, qword a, qword b);
// name: SafeHouse port (JOBB1::UpdateTarget)
void UpdateTarget__5JOBB1(struct S *p) {
    struct R r;
    qword q30, q40;
    struct W *w;
    qword a;
    if (!p->n60) return;
    { struct O *o = p->p5C; struct VTE *e = &o->vt[0x60]; ((void (*)(void *, struct R *, float))e->pfn)((char *)o + e->d, &r, p->p64->g1C - g_clock.t); }
    if (!r.n0) { p->n60 = 0; return; }
    w = p->pt->p58;
    GetTarget__5JOBB1P12LAUNCHTARGETP6VECTORT2(p, &r, &q30, &q40);
    a = PosConvertXfs__FP2XFT0G9VU_VECTOR(0, w->nA0, q30);
    SetGoal__10CTRLTARGETG9VU_VECTORT1(p->p64, a, VecConvertXfs__FP2XFT0G9VU_VECTOR(0, w->nA0, q40));
}
