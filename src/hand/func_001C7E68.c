struct VTE { short d; short pad; void (*pfn)(void *, int); };
struct O { int a[3]; struct VTE *vt; };
void func_001CB518(struct O *p);
// name: SafeHouse port (ResetCluePlacement)
void ResetCluePlacement__FP2LO(struct O *p)
{
    func_001CB518(p);
    { struct VTE *e = &p->vt[76]; e->pfn((char *)p + e->d, 0); }
}
