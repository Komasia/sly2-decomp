struct S { char pad[0x3A8]; unsigned int c; int a[5]; };
void func_00208920(struct S *p, int n) { if (p->c < 5) p->a[p->c++] = n; }
