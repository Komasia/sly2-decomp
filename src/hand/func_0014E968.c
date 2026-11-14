#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct S { qword a[5]; };
struct O { int pad[3]; VTENT *vt; };
struct P { char pad[0x260]; struct O *po; int pad2[3]; struct S s; };
qword CalcCmAdjust__FP2CMP6CPDEFI(struct P *p, struct S *ps);
// name: SafeHouse port (GetCmCpdefi)
void GetCmCpdefi__FP2CMP2SOP6CPDEFI(struct P *p, struct O *po, struct S *ps)
{
    if (po == p->po) {
        *ps = p->s;
    } else {
        VTENT *e = &po->vt[50];
        qword q, r;
        ((void (*)(void *, struct S *))e->pfn)(VT_THIS(po, e), ps);
        q = CalcCmAdjust__FP2CMP6CPDEFI(p, ps);
        __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(ps->a[1]), "j"(q));
        ps->a[4] = r;
    }
}
