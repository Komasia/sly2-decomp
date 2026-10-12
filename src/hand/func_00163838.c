struct E { int a, b, c, d; };
struct S { char pad[0x50]; int f50; char pad2[0xA8 - 0x54]; int c; struct E *ae; };
int func_00162050(void *p);
void func_00163838(struct S *p, int a, void *pv, int b, int d)
{
    if (p->f50 == 0 && p->c < 32) {
        struct E *pe = &p->ae[p->c++];
        pe->a = a;
        pe->b = b;
        pe->c = func_00162050(pv);
        pe->d = d;
    }
}
