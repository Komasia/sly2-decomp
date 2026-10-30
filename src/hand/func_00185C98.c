struct K { int a; int b; };
struct S { char pad[0x100]; struct K k; };
void CloneAlo__FP3ALOT0(struct S *p);
void func_00185C98(struct S *p)
{
    struct K k = p->k;
    CloneAlo__FP3ALOT0(p);
    p->k = k;
}
