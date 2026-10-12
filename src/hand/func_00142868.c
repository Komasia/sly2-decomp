struct S { char pad[0x1148]; int a; float f; };
void func_00142868(struct S *p, int a)
{
    p->a = a;
    p->f = 3.40282346638528859812e+38f;
}
