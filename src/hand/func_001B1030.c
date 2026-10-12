struct VTE { short d; short pad; void (*pfn)(); };
struct V3 { int x, y, z; };
struct X { char pad[0xF0]; struct V3 v; };
struct S { int a, b, c; struct VTE *vt; char pad[0x58 - 0x10]; struct X *px58; struct X *px5c; char pad2[0x220 - 0x60]; int n; };
void func_001F3980(struct S *p);
static __inline__ void ClearV(struct V3 *pv) { pv->z = 0; pv->y = 0; pv->x = 0; }
void func_001B1030(struct S *p)
{
    int n = p->n;
    if (n < 4) if (n >= 2) {
        struct VTE *e;
        ClearV(&p->px58->v);
        ClearV(&p->px5c->v);
        e = &p->vt[70];
        ((void (*)(void *))e->pfn)((char *)p + e->d);
    }
    func_001F3980(p);
}
