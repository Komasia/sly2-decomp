struct S { char pad[0x118]; int a; int b; };
extern char g_sw[];
void func_0020FEC0(void *g, void *pb, int n, void *pa, int x, int y, int z, int w);
// name: SafeHouse port (AddUseRsmg)
void AddUseRsmg__FP2LO3OIDN21(struct S *p, int y, int z, int w)
{
    func_0020FEC0(g_sw, &p->b, 4, &p->a, 1, y, z, w);
}
