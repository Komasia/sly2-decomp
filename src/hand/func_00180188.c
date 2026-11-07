struct S { char pad[0x188]; int n; };
void InitHackSo__FP2LO(struct S *p);
void func_00180188(struct S *p)
{
    InitHackSo__FP2LO(p);
    p->n = 10;
}
