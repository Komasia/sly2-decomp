#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct B { char pad[0xB0]; qword v; };
struct S { char pad[0xC]; VTENT *vt; char pad2[0x5C - 0x10]; struct B *pb; char pad3[0x1A8 - 0x60]; float g; char pad4[0x1F4 - 0x1AC]; int x; };
float atan2f(float y, float x);
void RadSmooth(float a, float b, float c, int *p, float *pf) asm("RadSmooth__FfffP3SMPPf");
// name: SafeHouse port (TurnActorNow)
void TurnActorNow__FP5ACTOR(struct S *p)
{
    U v;
    float *a, *b;
    v.q = p->pb->v;
    a = ((float *(*)(void *))p->vt[31].pfn)(VT_THIS(p, &p->vt[31]));
    b = ((float *(*)(void *))p->vt[31].pfn)(VT_THIS(p, &p->vt[31]));
    RadSmooth(atan2f(a[1], b[0]), p->g, 0.0f, &p->x, &v.f[2]);
    ((void (*)(void *, qword))p->vt[36].pfn)(VT_THIS(p, &p->vt[36]), v.q);
}
