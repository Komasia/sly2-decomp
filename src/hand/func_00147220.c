struct VTE { short d; short pad; void (*pfn)(); };
struct O { char pad[0xC]; struct VTE *vt; char pad2[0x150 - 0x10]; int n150; };
extern char D_002BD380[];
void func_001F36A8(void *p);
void BindLoParts__FP3ALOiPv(void *p, int n, void *q);
// name: SafeHouse port (PostLoadAnimatedOverlay)
void PostLoadAnimatedOverlay__FP2LO(struct O *p)
{
    struct VTE *e;
    func_001F36A8(p);
    BindLoParts__FP3ALOiPv(p, 2, D_002BD380);
    e = &p->vt[9];
    p->n150 = -1;
    ((void (*)(void *))e->pfn)((char *)p + e->d);
}
