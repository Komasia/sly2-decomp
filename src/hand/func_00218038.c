struct S { char pad[0x28]; int f; };
void func_00218060(struct S *p, int a, int b);
void func_00218038(struct S *p)
{
    if (p->f)
        func_00218060(p, 0, 0);
}
