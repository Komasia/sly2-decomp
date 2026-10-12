struct E { int a, b, c, d, e, f; };
struct S { char pad[0x50]; int f50; char pad2[0xB0 - 0x54]; int c; struct E *ae; };
void func_001638A0(struct S *p, int a, int b, int c, int d, int e, int f)
{
    if (p->f50 == 0 && p->c < 32) {
        struct E *pe = &p->ae[p->c++];
        pe->a = a; pe->b = b; pe->c = c; pe->d = d; pe->e = e; pe->f = f;
    }
}
