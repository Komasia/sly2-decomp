struct E { int n; int a; int b; };
struct O { char pad[0x574]; struct E ae[1]; };
struct S { char p0[0x10]; struct O *po; char p1[0x6C-0x14]; int i; int n; };
void func_001D4E30(struct S *p) {
    struct E *pe = &p->po->ae[p->i];
    int n = pe->n - p->n;
    if (n < 0) n = 0;
    pe->n = n;
}
