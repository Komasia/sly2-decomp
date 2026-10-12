struct E { int n; int a; int b; };
struct O { char pad[0x574]; struct E ae[1]; };
struct S { char p0[0x10]; struct O *po; char p1[0x6C-0x14]; int i; int n; };
int func_001D4E08(struct S *p) {
    return p->po->ae[p->i].n >= p->n;
}
