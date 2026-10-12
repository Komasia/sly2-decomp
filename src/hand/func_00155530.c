struct E { int a; int pad4; int b; int padc; int c; int pad14; int d; int pad1c; int pad20; };
struct L { char pad[0x1010]; int c; struct E *ae; };
void func_00155530(struct L *p, int a, int b, int c, int d)
{
    struct E *pe = &p->ae[p->c++];
    pe->a = a;
    pe->b = b;
    pe->c = c;
    pe->d = d;
}
