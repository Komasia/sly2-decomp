struct VTE { short d; short pad; void (*pfn)(); };
struct O { int pad[3]; struct VTE *vt; char pad2[0x1020]; int f1030; };
struct S { struct O *po; };
int func_00131968(int);
void func_001371C8(struct S *p) {
    if (func_00131968(p->po->f1030)) {
        struct O *po = p->po; struct VTE *vt = po->vt;
        ((void (*)(void *, int))vt[88].pfn)((char *)po + vt[88].d, 0);
    }
}
