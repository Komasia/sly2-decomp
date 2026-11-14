#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct O { int a[3]; VTENT *vt; };
void RemoveNoise__FP5NOISE(struct O *o);
void PnoiseNew__FP9NOISETMPLG9VU_VECTORiP6VECTOR(void *x, qword q, int c, struct O **ppo);
// name: SafeHouse port (SetHeldNoise)
void SetHeldNoise__FPP5NOISEG9VU_VECTORiP2LO(void *x, qword q, int c, struct O **ppo)
{
    if (*ppo) {
        struct O *o;
        VTENT *e;
        RemoveNoise__FP5NOISE(*ppo);
        o = *ppo;
        e = &o->vt[2];
        ((void (*)())e->pfn)(VT_THIS(o, e));
        *ppo = 0;
    }
    if (x) {
        struct O *o;
        VTENT *e;
        PnoiseNew__FP9NOISETMPLG9VU_VECTORiP6VECTOR(x, q, c, ppo);
        o = *ppo;
        e = &o->vt[1];
        ((void (*)())e->pfn)(VT_THIS(o, e));
    }
}
