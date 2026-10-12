struct S { char pad[0x188]; int n; };
void func_0017F090(struct S *p);
void func_00180188(struct S *p)
{
    func_0017F090(p);
    p->n = 10;
}
