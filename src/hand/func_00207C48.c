struct X { int a; char p0[0x2C]; int b; char p1[0x2C]; int c; char p2[0x2C]; int d; };
struct E { int k; struct X *px; int pad; int n; };
long MaskOfList__FPv(int a);
struct E *PkindeOfMask__FP5GUARDUl(void *p, long id);
struct X *func_0020CA00(int cb);
void func_0020C7D8(struct X *px);
// name: SafeHouse port (SetGuardKind3)
void SetGuardKind3__FP5GUARDiiiii(void *p, int id, int a, int b, int c, int d)
{
    struct E *pe = PkindeOfMask__FP5GUARDUl(p, MaskOfList__FPv(id));
    pe->k = 3;
    pe->px = func_0020CA00(0xD0);
    func_0020C7D8(pe->px);
    pe->px->a = a;
    pe->px->b = b;
    pe->px->c = c;
    pe->px->d = d;
    pe->n = 8;
}
