struct VTE { short d; short pad; void (*pf)(); };
struct O { int x0; int x4; int x8; struct VTE *vt; char p1[0x80 - 0x10]; char x80[0xD0]; int x150; };
struct G { char pad[0x403C]; char pool[0x30]; struct O *x406C; };
extern struct VTE g_vtso[];
extern struct VTE g_vtripg[];
void *func_0011CCC0(void *pool);
void *s1_memset(void *p, int c, int cb) asm("memset");
void *__7GLOBSET(void *p);
void *func_0015E3A8(struct G *p, int n);
void func_0011A070(void *pl, void *pv);
#define VCALL0(o, n) ((void (*)(void *))(o)->vt[n].pf)((char *)(o) + (o)->vt[n].d)
// name: SafeHouse port (PripgNew)
struct O *PripgNew__FP2SW5RIPGT(struct G *p, int a)
{
    struct O *po;
    if (!a && p->x406C) return p->x406C;
    po = func_0011CCC0(p->pool);
    if (!po) return 0;
    s1_memset(po, 0, 0x1B0);
    po->x0 = 0;
    po->x4 = 0;
    po->vt = g_vtso;
    __7GLOBSET(po->x80);
    po->x150 = a;
    po->vt = g_vtripg;
    func_0011A070(func_0015E3A8(p, 0x57), po);
    VCALL0(po, 7);
    VCALL0(po, 11);
    VCALL0(po, 15);
    if (!a) p->x406C = po;
    return po;
}
