struct S { int c; int a[0x100]; };
int func_001D57E0(struct S *p) {
    if (p->c == 0) return 0;
    return p->a[--p->c];
}
