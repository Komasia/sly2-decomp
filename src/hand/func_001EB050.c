struct S { int a, b, c, d; unsigned int n10; int n14; unsigned int n18; };
struct T { int a, b, c, d; unsigned int n10; int n14; };
struct S *func_001EB050(struct S *p, struct T *q)
{
    *(struct T *)p = *q;
    p->n18 = (p->n10 + 15) >> 4;
    return p;
}
