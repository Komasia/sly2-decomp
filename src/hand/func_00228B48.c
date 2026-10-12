struct S { char pad[0x40]; int f; char pad2[0x13C]; int a, b, c; };
static inline int FIsPtr(int f) { return !(f & 1); }
void func_001F2108(struct S *p);
void func_00228B48(struct S *p)
{
    int f;
    func_001F2108(p);
    f = p->f;
    p->a = 1;
    p->b = -10;
    p->c = 0x2000;
    if (FIsPtr(f)) *(int *)f |= 2;
    else p->f = f | 2;
}
