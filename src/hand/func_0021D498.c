struct Q { char b[8]; };
struct S { char pad[0xE0]; struct Q q; };
void func_002311B0(struct S *p);
void func_0021D498(struct S *p)
{
    struct Q t = p->q;
    func_002311B0(p);
    p->q = t;
}
