struct S { char pad[0x1D0]; int c; int a[1]; };
// name: SafeHouse port (IvoiceFromTarget)
int IvoiceFromTarget__FP8SOUNDMGRi(struct S *p, int n) { int i; for (i = 0; i < p->c; i++) if (p->a[i] == n) return i; return -1; }
