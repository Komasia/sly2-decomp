struct VTE { short d; short pad; void (*pfn)(void *, int); };
struct O { int a[3]; struct VTE *vt; char pad[0x140]; int n150; char pad2[0xE4]; float g238; };
struct CLOCK { float t; float dt; };
extern struct CLOCK D_002DDED0;
void func_001C5E48(struct O *p);
void func_001C7778(struct O *p)
{
    func_001C5E48(p);
    if (!p->n150) {
        p->g238 -= D_002DDED0.dt;
        if (p->g238 <= 0.0f) { struct VTE *e = &p->vt[76]; e->pfn((char *)p + e->d, 5); }
    }
}
