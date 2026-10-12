struct I { int a, b; };
struct E { int id; int n; int c; struct I *a; };
struct S;
extern char D_002A76C0[];
struct E *func_001BBE68(struct S *p, void *k);
struct I *func_001BBDB0(struct S *p, int x)
{
    struct E *pe = func_001BBE68(p, D_002A76C0);
    struct I *pi;
    if (!pe) return 0;
    if (pe->c >= 0x40) return 0;
    pi = &pe->a[pe->c++];
    pi->a = x;
    return pi;
}
