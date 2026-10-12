struct S { char pad[0x28]; int f; };
void func_00217FE0(struct S *p, int a, int b);
void func_00217FB8(struct S *p)
{
    if (p->f)
        func_00217FE0(p, 0, 0);
}
