struct VTE { short d; short pad; void (*pfn)(void *); };
struct O { char pad[0xC]; struct VTE *vt; };
struct S { char pad[0x3BC4]; struct O *po; char pad2[0x476C - 0x3BC8]; int n; };
void func_00161958(struct S *p)
{
    struct O *po = p->po;
    if (po) {
        struct VTE *e = &po->vt[50];
        e->pfn((char *)po + e->d);
    }
    p->n = 0;
}
