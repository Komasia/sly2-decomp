struct S { char pad[0xEB8]; int a[8]; unsigned int c; };
void func_0020AA40(struct S *p, int n) { if (n != -1) { if (p->c < 8) p->a[p->c++] = n; } }
