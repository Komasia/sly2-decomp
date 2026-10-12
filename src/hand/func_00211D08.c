struct S { char pad[0xB0]; int f; };
void func_001A5270(struct S *p);
void func_00211D08(struct S *p)
{
    func_001A5270(p);
    p->f = 1;
}
