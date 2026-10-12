struct S { char pad[0xE94]; unsigned int c; int a[8]; };
void func_0020A518(struct S *p, int n) { if (p->c < 8) p->a[p->c++] = n; }
