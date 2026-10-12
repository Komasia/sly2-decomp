struct E { int a; void *pv; int pad[5]; };
struct P { int pad[10]; struct E ae[1]; };
extern char D_002BFDA8[], D_002BFE08[], D_002BFE68[];
int func_001D9880(struct P *p);
int func_001B0078(struct P *p)
{
    int n;
    void *pv;
    if (!func_001D9880(p)) return -1;
    n = p->pad[9];
    if (n <= 0) return -1;
    pv = p->ae[n - 1].pv;
    if (pv == D_002BFDA8) return 0x1E;
    if (pv == D_002BFE08) return 0x1F;
    if (pv == D_002BFE68) return 0x19;
    return -1;
}
