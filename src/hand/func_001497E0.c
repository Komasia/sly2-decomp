struct S { char pad[0x2AC]; unsigned int c; int a[4]; };
void func_001497E0(struct S *p, int x)
{
    if (p->c < 4) {
        p->a[p->c++] = x;
    }
}
