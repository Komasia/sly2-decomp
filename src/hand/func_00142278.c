#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct P { char pad[0xC]; VTENT *vt; char pad2[0x11B0 - 0x10]; char sub[0x10]; void *p11C0; char pad3[0x1290 - 0x11C4]; qword q1290; };
void FadeAloIn__FP3ALOf(void *p, float f);
qword PosOfLo__FP2LO(void *p);
void UpdateJtThrowArc__FP7JTTHROWi(void *p, int n);
void SetJtThrowState__FP7JTTHROWi(void *p, int n);
void func_00142278(struct P *p, void *a, void *b)
{
    VTENT *e;
    FadeAloIn__FP3ALOf(a, 0.25f);
    p->p11C0 = a;
    p->q1290 = PosOfLo__FP2LO(b);
    UpdateJtThrowArc__FP7JTTHROWi(p->sub, 0);
    e = &p->vt[88];
    ((void (*)(void *, int))e->pfn)(VT_THIS(p, e), 7);
    SetJtThrowState__FP7JTTHROWi(p->sub, 7);
}
