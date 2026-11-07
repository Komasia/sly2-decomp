struct VTE { short d; short pad; void (*pfn)(); };
struct O { int a, b, c; struct VTE *vt; };
struct S { char pad[0x1050]; struct O *po; };
void ResetGuard__FP2LO(struct S *p);
void func_001BA0B8(struct S *p)
{
    struct O *po;
    ResetGuard__FP2LO(p);
    po = p->po;
    if (po) {
        struct VTE *e = &po->vt[9];
        ((void (*)(void *))e->pfn)((char *)po + e->d);
    }
}
