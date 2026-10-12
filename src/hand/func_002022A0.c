struct O { char pad[0x108]; int n; };
struct S { char pad[0x30]; int c; struct O *a[1]; };
void func_002022A0(struct S *p) { int i; for (i = 0; i < p->c; i++) p->a[i]->n = 0; }
