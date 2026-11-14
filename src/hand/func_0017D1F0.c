#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct M3 { qword a, b, c; };
struct O { char pad[0xC]; VTENT *vt; char pad2[0x2C]; int n3C; };
struct T { char pad[0x1B0]; struct M3 m1B0; char pad2[0xF84 - 0x1E0]; void *pF84; };
struct S { char pad[0x10]; struct T *pt; };
extern qword g_normalZ;
void Enter__5AIJOB(struct S *p);
struct O *func_00205438(void *p, int n);
qword *MatJtLo__FP2LO(void *p);
struct M3 BuildLookAtMatrix__FP6VECTORG9VU_VECTORT1(qword a, qword b);
// name: SafeHouse port (JOBHOLD::Enter)
void Enter__7JOBHOLD(struct S *p) {
    struct O *o; VTENT *e; struct T *t;
    Enter__5AIJOB(p);
    o = func_00205438(p->pt, 0x9D); o->n3C = 2; e = &o->vt[8]; ((void (*)(void *))e->pfn)(VT_THIS(o, e));
    t = p->pt;
    t->m1B0 = BuildLookAtMatrix__FP6VECTORG9VU_VECTORT1(*MatJtLo__FP2LO(t->pF84), g_normalZ);
}
