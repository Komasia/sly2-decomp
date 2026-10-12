struct S { char pad[0x238]; unsigned int c; int a[4]; };
void func_001B2020(struct S *p, int x)
{
    if (p->c < 4) p->a[p->c++] = x;
}
