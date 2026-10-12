struct S { char pad[0x5C]; int c; int *a; };
void func_00162630(struct S *p, int n)
{
    if (p->c < 32) {
        p->a[p->c++] = n;
    }
}
