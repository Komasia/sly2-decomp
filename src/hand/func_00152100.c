#include "vtbl.h"
struct O { int a[3]; VTENT *vt; };
void PostStepLoad__FP4STEP(struct O *o);
void InitDancer__FP2LO(struct O *o);
// name: SafeHouse port (PostLoadDancer)
void PostLoadDancer__FP2LO(struct O *o)
{
    VTENT *e;
    PostStepLoad__FP4STEP(o);
    InitDancer__FP2LO(o);
    e = &o->vt[79];
    ((void (*)())e->pfn)(VT_THIS(o, e), 0);
}
