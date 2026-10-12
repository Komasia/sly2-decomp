struct S { char pad[0x200]; int a; int b; };
extern char D_003DD490[];
void func_0020FEC0(void *g, void *pb, int n, void *pa, int x, int y, int z, int w);
void func_001816E8(struct S *p, int x, int y, int z, int w)
{
    func_0020FEC0(D_003DD490, &p->b, 4, &p->a, x, y, z, w);
}
