struct S { char pad[0x1010]; int n; };
struct G { char pad[0x600]; int a; };
extern struct G g_cm;
extern int D_002F7900;
void SetCmPolicy__FP2CM3CPPP5CPLCYii(struct G *pg, int n, void *pv, int m, void *p);
void RevokeCmPolicy__FP2CMi3CPPP5CPLCYii(struct G *pg, int a, int b, void *c, void *d, int e);
void func_001CBF90(struct S *p, int n)
{
    if (p->n == n) return;
    p->n = n;
    if (n) SetCmPolicy__FP2CM3CPPP5CPLCYii(&g_cm, 6, &g_cm.a, D_002F7900, p);
    else RevokeCmPolicy__FP2CMi3CPPP5CPLCYii(&g_cm, 1, 6, 0, 0, 0);
}
