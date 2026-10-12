struct S { char pad[0x16C]; int c; int a[4]; };
void func_00228988(struct S *p, int v)
{
    if ((unsigned)p->c < 4) p->a[p->c++] = v;
}
