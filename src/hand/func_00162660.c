struct S { char pad[0xAC]; int a; int b; int c; };
void func_00162660(struct S *p, int a, int b, int c)
{
    p->a = a;
    p->b = b;
    p->c = c;
}
