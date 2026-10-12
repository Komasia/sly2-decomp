struct S { char pad[0x90]; int c; int *a; };
void func_00173398(struct S *p, int x) { if (p->c < 8) { p->a[p->c++] = x; } }
