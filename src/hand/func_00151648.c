struct VTE { short d; short pad; void (*pfn)(); };
struct O { int a[3]; struct VTE *vt; };
struct B { int pad[5]; struct O *po; };
struct A { int pad[4]; struct B *pb; };
void func_0014FCC8(struct A *a, int n, struct B *b);
void func_00151648(struct A *a, int n, struct B *b)
{
    struct O *o;
    struct VTE *e;
    func_0014FCC8(a, n, b);
    a->pb = b;
    o = b->po;
    e = &o->vt[1];
    e->pfn((char *)o + e->d);
}
