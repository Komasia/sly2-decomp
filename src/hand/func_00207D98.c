struct X { int a; };
struct S { int n; struct X *px; int b; int c; };
unsigned long func_00207B10(void *p);
struct S *func_00209C18(void *p, unsigned long m);
struct X *func_0020C010(int cb);
void func_0020BD78(struct X *px);
void func_00207D98(void *p, void *q, int a)
{
    struct S *s = func_00209C18(p, func_00207B10(q));
    s->n = 2;
    s->px = func_0020C010(0x40);
    func_0020BD78(s->px);
    s->px->a = a;
    s->c = 0;
}
