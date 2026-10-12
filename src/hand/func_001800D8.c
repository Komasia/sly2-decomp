struct E { int a; int b; int c; int d; };
struct S { char pad[0x1C8]; struct E ae[5]; };
void func_001800D8(struct S *p, unsigned int i, int a, int d)
{
    if (i < 5) {
        p->ae[i].a = a;
        p->ae[i].d = d;
    }
}
