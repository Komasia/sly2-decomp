struct E { int a, b, c, d, e, f; };
struct S { char pad[0x50]; int f50; char pad2[0x94 - 0x54]; int c; struct E *ae; };
void func_00162728(struct S *p, int a, int b, int c, int d, int f)
{
    if (p->f50 == 0 && p->c < 32) {
        struct E *pe = &p->ae[p->c++];
        pe->f = f; pe->a = a; pe->b = b; pe->c = c; pe->d = d; pe->e = 0;
    }
}
