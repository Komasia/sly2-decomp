struct VTE { short d; short pad; void (*pf)(void *, void *); };
struct O { int a[3]; struct VTE *vt; };
struct B { int a; struct O *po; };
// name: SafeHouse port (NotifyWaterObject)
void NotifyWaterObject__FP3ALOP5WNODE(void *p, struct B *b)
{
    struct O *po = b->po;
    po->vt[72].pf((char *)po + po->vt[72].d, p);
}
