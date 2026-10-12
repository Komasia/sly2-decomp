struct E { int a; int b; };
struct S { char pad[0x20]; struct E *ae; };
void func_00226F28(int a, int b, int c, int d, int e);
int func_001EC688(struct S *p, int i, int x, int y)
{
    struct E *pe = &p->ae[i];
    func_00226F28(y, 12, pe->a, pe->b, x);
    return pe->a;
}
