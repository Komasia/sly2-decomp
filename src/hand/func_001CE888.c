struct R { int a, b; void *p8; };
struct G { char pad[0x4054]; char pool[4]; };
struct Q { char pad[0x15C]; char dl[4]; };
extern char g_sw[];
struct Q *PripgNew__FP2SW5RIPGT(void *pg, int n);
void *func_0011CCC0(void *pool);
struct R *func_001CE6D0(void *pv, void *a);
void AppendDlEntry__FP2DLPv(void *pdl, void *pv);
void AddRipRef(struct R *r) asm("AddRipRef__FP3RIP");
// name: SafeHouse port (FLaunchHudRip)
struct R *FLaunchHudRip__FP2LOP6VECTORP7MATRIX3(struct G *p, void *a, struct Q *q)
{
    void *pv;
    struct R *r;
    if (!q) q = PripgNew__FP2SW5RIPGT(g_sw, 0);
    if (!q) return 0;
    pv = func_0011CCC0(p->pool);
    if (pv) {
    r = func_001CE6D0(pv, a);
    r->p8 = q;
    AppendDlEntry__FP2DLPv(q->dl, r);
    AddRipRef(r);
    return r; }
    return 0;
}
