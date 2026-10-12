struct E { int a; int b; int c; int d; };
struct S { char pad[0x220]; struct E ae[5]; };
void func_00181308(struct S *p, unsigned int i, int a, int d)
{
    if (i < 5) {
        p->ae[i].a = a;
        p->ae[i].d = d;
    }
}
