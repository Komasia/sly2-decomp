struct VTE { short d; short pad; void (*pfn)(void *, void *, int); };
struct O { int a[3]; struct VTE *vt; char pad[0x14]; struct O *pNext; char pad2[0x3C]; struct O *pFirst; };
void func_001CA118(struct O *p, void *a);
void func_001CA308(struct O *p, void *a)
{
    struct O *o;
    int unused[4];
    func_001CA118(p, a);
    for (o = p->pFirst; o; o = o->pNext) { struct VTE *e = &o->vt[25]; e->pfn((char *)o + e->d, a, 0); }
}
