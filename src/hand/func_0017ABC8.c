typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
struct VTE { short d; short pad; void *pfn; };
struct O { char pad[0xC]; struct VTE *vt; };
struct R { int n0; int a[11]; };
struct U { char pad[0x1C]; float g1C; };
struct W { char pad[0xA0]; int nA0; };
struct T { char pad[0x58]; struct W *p58; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x48]; struct O *p5C; int n60; struct U *p64; };
void GetTarget__5JOBB1P12LAUNCHTARGETP6VECTORT2(struct S *p, struct R *r, qword *a, qword *b);
qword func_0022FC48(int a, int b, qword q);
qword func_0022FCC8(int a, int b, qword q);
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
    a = func_0022FC48(0, w->nA0, q30);
    SetGoal__10CTRLTARGETG9VU_VECTORT1(p->p64, a, func_0022FCC8(0, w->nA0, q40));
}
