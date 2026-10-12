struct S { char pad[0x54]; int c; int *a; };
void FUN_001e53f8(struct S *p, int n)
{
    if (p->c < 32) {
        p->a[p->c++] = n;
    }
}
