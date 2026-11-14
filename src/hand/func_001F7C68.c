#include "vtbl.h"
typedef unsigned long ulong;
struct VT { VTENT a[9]; };
struct P { char pad[0xC]; struct VT *pvt; char pad2[0x28 - 0x10]; ulong fl; char pad3[0x12C - 0x30]; float g12C; };
void SetFade__FP3ALOf(struct P *, float);
void func_001F7D10(struct P *, float);
// name: SafeHouse port (FadeAloIn)
void FadeAloIn__FP3ALOf(struct P *p, float f)
{
    if (f <= 0.0f) {
        SetFade__FP3ALOf(p, 0.0f);
        func_001F7D10(p, 1.0f);
    } else {
        if (p->fl & (1L << 56)) {
            ((void (*)(void *))p->pvt->a[8].pfn)(VT_THIS(p, &p->pvt->a[8]));
            p->g12C = 0.0f;
        }
        SetFade__FP3ALOf(p, 1.0f / f);
    }
}
