
struct VTE { short d; short pad; void (*pf)(void *); };
struct OW { char pad[0x26C]; int x; };
struct O { char pad[0xC]; struct VTE *vt; struct OW *pow; };
struct S { struct O *po; };
void func_001EEED0(int *p);
void func_001EF0D8(struct S *p)
{
    struct O *po = p->po;
    if (po) {
        int *px = &po->pow->x;
        po->vt[9].pf((char *)po + po->vt[9].d);
        func_001EEED0(px);
        p->po = 0;
    }
}
