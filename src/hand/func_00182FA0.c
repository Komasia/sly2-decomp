struct K { int a; int b; };
struct S { char pad[0x1B4]; struct K k; };
void func_001E5DB8(struct S *p);
void func_00182FA0(struct S *p)
{
    struct K k = p->k;
    func_001E5DB8(p);
    p->k = k;
}
