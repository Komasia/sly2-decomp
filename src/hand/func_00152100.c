struct VTE { short d; short pad; void (*pfn)(); };
struct O { int a[3]; struct VTE *vt; };
void PostStepLoad__FP4STEP(struct O *o);
void InitDancer__FP2LO(struct O *o);
// name: SafeHouse port (PostLoadDancer)
void PostLoadDancer__FP2LO(struct O *o)
{
    struct VTE *e;
    PostStepLoad__FP4STEP(o);
    InitDancer__FP2LO(o);
    e = &o->vt[79];
    e->pfn((char *)o + e->d, 0);
}
