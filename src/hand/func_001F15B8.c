struct VTE { short d; short pad; void (*pfn)(void *); };
struct O { int a[3]; struct VTE *vt; };
struct S { struct O *po; };
void RetractSma__FP3SMA(struct O *);
// name: SafeHouse port (ClearSmaHandle)
void ClearSmaHandle__FPP3SMA(struct S *p)
{
    if (p->po) {
        RetractSma__FP3SMA(p->po);
        { struct O *po = p->po; po->vt[2].pfn((char *)po + po->vt[2].d); }
        p->po = 0;
    }
}
