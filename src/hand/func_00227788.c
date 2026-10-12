struct C { unsigned char a[4]; };
struct S { int k; struct C c; int z; };
void func_002275B8(struct C *pc, int a);
void func_00227788(struct S *p)
{
    struct C c;
    p->k = -1;
    func_002275B8(&c, -1);
    p->c = c;
    p->z = 0;
}
