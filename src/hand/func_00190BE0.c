struct VTE { short d; short pad; float *(*pfn)(void *); };
struct O { int a, b, c; struct VTE *vt; };
struct S { char pad[0x18C4]; struct O *o; };
float atan2f(float, float);
// name: SafeHouse port (RadHangFrame)
void RadHangFrame__FP3SLYPf(struct S *p, float *pg) {
    float *a, *b;
    { struct O *o = p->o; struct VTE *e = &o->vt[31]; a = e->pfn((char *)o + e->d); }
    { struct O *o = p->o; struct VTE *e = &o->vt[31]; b = e->pfn((char *)o + e->d); }
    *pg = atan2f(a[1], b[0]);
}
