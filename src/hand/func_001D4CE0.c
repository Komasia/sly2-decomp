struct E { int a; int n; float g; };
struct S { char pad[0x574]; struct E ae[1]; };
void func_001D4CE0(struct S *p, int i, float g, int n) {
    struct E *pe = &p->ae[i];
    pe->n = n;
    pe->g = g;
}
