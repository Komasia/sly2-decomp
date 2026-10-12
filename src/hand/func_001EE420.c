struct T { int n; };
struct S { char pad[0x60]; int n60; };
int func_001EDB80(struct S *p, struct T *t);
int func_001EE420(struct S *p, struct T *t)
{
    int f = 0;
    if (func_001EDB80(p, t) || t->n == p->n60) f = 1;
    return f;
}
