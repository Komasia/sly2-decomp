struct VTE { short d; short pad; void (*pfn)(); };
struct O { int a, b, c; struct VTE *vt; };
struct S { int a, b, c; struct VTE *vt; char pad[0x14]; struct O *po; };
void func_001DD6C8(struct S *p) {
    if (p->po) {
        {
            struct VTE *e = &p->vt[10];
            ((void (*)(void *))e->pfn)((char *)p + e->d);
        }
        {
            struct O *po = p->po;
            struct VTE *e = &po->vt[49];
            ((void (*)(void *, int))e->pfn)((char *)po + e->d, -1);
        }
    }
}
