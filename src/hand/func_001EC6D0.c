typedef int qword __attribute__((mode(TI)));
struct O { char pad[0x30]; qword q; };
struct E { int a; struct O *po; };
struct S { char pad[0x20]; struct E *ae; };
void func_00226F28(int a, int b, int c, qword *d, int e);
int func_001EC6D0(struct S *p, int i, int x, int y)
{
    struct E *pe = p->ae + i; qword q = pe->po->q;
    func_00226F28(y, 12, 1, &q, x);
    return 1;
}
