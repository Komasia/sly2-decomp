struct O;
struct S { char pad[0xA4]; int c; struct O *a[4]; int b[4]; int d[4]; };
void func_001E5280(struct S *p, struct O *object, int b, int d);
void func_001E54E8(struct S *p)
{
    while (p->c) {
        func_001E5280(p, p->a[p->c - 1], p->b[p->c - 1], p->d[p->c - 1]);
    }
}
