struct S { char pad[0x2D0]; unsigned int c; int a[8]; };
void func_00149248(struct S *p, int x)
{
    if (p->c < 8) {
        p->a[p->c++] = x;
    }
}
