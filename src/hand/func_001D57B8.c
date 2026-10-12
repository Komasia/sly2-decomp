struct S { unsigned int c; int a[0x100]; };
void func_001D57B8(struct S *p, int n) {
    if (p->c < 0x100) {
        p->a[p->c++] = n;
    }
}
