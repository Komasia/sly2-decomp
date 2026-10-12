struct E { int a; int b; int c; int d; };
struct S { char pad[0x1D0]; struct E ae[3]; };
void func_001816C0(struct S *p, unsigned int i, int a, int d)
{
    if (i < 3) {
        p->ae[i].a = a;
        p->ae[i].d = d;
    }
}
