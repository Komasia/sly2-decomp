struct S { char pad[0x3C0]; unsigned int c; int a[2]; };
void func_00208A68(struct S *p, int n) { if (p->c < 2) p->a[p->c++] = n; }
