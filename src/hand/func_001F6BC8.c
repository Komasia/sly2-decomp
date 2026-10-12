struct E { int a[3]; int n; int b[2]; int x18; char pad[0x94]; };
struct S { char pad[0xE0]; int c; struct E *ae; };
void func_001F6BC8(struct S *p, int n, int x) { int i; for (i = 0; i < p->c; i++) { struct E *pe = &p->ae[i]; if (pe->n == n) pe->x18 = x; } }
