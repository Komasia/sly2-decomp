struct S { char pad[0x118]; int a; int b; };
extern char D_003DD490[];
void func_0020FEC0(void *g, void *pb, int n, void *pa, int x, int y, int z, int w);
void func_001840B8(struct S *p, int y, int z, int w)
{
    func_0020FEC0(D_003DD490, &p->b, 4, &p->a, 1, y, z, w);
}
