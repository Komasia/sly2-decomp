struct S { char pad[0x1D0]; int c; int a[1]; };
int func_001FE990(struct S *p, int n) { int i; for (i = 0; i < p->c; i++) if (p->a[i] == n) return i; return -1; }
