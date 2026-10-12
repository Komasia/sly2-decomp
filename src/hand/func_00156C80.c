typedef int qword __attribute__((mode(TI)));
struct S { char pad[0x4020]; int a; int b; };
void func_00156BE0(int n, qword q, int c, int d);
void func_00156C80(struct S *p, int k, qword q, int c, int d)
{
    int n;
    switch (k) {
    case 0: n = p->a; break;
    case 1: n = p->b; break;
    default: n = 0; break;
    }
    func_00156BE0(n, q, c, d);
}
