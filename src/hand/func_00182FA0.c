struct K { int a; int b; };
struct S { char pad[0x1B4]; struct K k; };
void ClonePath__FP4PATHT0(struct S *p);
void func_00182FA0(struct S *p)
{
    struct K k = p->k;
    ClonePath__FP4PATHT0(p);
    p->k = k;
}
