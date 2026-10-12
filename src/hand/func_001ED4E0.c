struct S { int n; };
extern struct S **D_003DD010;
struct S *func_001ED4E0(int n)
{
    int i;
    struct S *p;
    if (!D_003DD010) return 0;
    i = n % 0x3FFD;
loop:
    p = D_003DD010[i];
    if (!p || p->n == n) return p;
    i = (i + 1) % 0x3FFD;
    goto loop;
}
