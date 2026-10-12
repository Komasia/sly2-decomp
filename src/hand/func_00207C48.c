struct X { int a; char p0[0x2C]; int b; char p1[0x2C]; int c; char p2[0x2C]; int d; };
struct E { int k; struct X *px; int pad; int n; };
long func_00207B10(int a);
struct E *func_00209C18(void *p, long id);
struct X *func_0020CA00(int cb);
void func_0020C7D8(struct X *px);
void func_00207C48(void *p, int id, int a, int b, int c, int d)
{
    struct E *pe = func_00209C18(p, func_00207B10(id));
    pe->k = 3;
    pe->px = func_0020CA00(0xD0);
    func_0020C7D8(pe->px);
    pe->px->a = a;
    pe->px->b = b;
    pe->px->c = c;
    pe->px->d = d;
    pe->n = 8;
}
