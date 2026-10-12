struct VTE { short d; short pad; void (*pfn)(); };
struct O { int a, b, c; struct VTE *vt; char pad[0x15C - 0x10]; int f15c; int f160; };
struct S { char pad[0x104]; int c; struct O *a[1]; };
void func_001BEAD0(struct S *p, struct O *po)
{
    if (po) {
        struct VTE *e;
        p->a[p->c++] = po;
        po->f160 = 1;
        po->f15c = 1;
        e = &po->vt[9];
        ((void (*)(void *))e->pfn)((char *)po + e->d);
    }
}
