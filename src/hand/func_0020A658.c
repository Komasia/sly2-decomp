struct S { char pad[0x28]; int c; int a[1]; };
int func_0020A658(struct S *p, int n) { int i; for (i = 0; i < p->c; i++) if (n == p->a[i]) return i; return -1; }
