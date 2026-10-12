struct S { char pad[0xE0]; int c; void *a[1]; };
void func_001BEAA8(struct S *p, void *x)
{
    if (x) p->a[p->c++] = x;
}
