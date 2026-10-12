struct S { char pad[0x150]; unsigned int c; int a[7]; };
void func_001DE3D8(struct S *p, int n) {
    if (p->c < 7) {
        p->a[p->c++] = n;
    }
}
