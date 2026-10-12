struct X { char pad[0x54]; int n; };
struct S { char pad[0x64]; struct X *a; struct X *b; };
static inline int Max(int a, int b) { return a > b ? a : b; }
int func_00163430(struct S *p)
{
    int n = p->a->n;
    return n < 2 ? n : Max(p->b->n, 1);
}
