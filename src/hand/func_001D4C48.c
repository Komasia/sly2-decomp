struct K { int a, b; };
struct E { int n; int a, b; struct K k; };
struct S { char pad[0x4A4]; unsigned int c; struct E ae[4]; };
void func_001D4C48(struct S *p, int n, struct K *pk) {
    if (p->c < 4) {
        struct E *pe = &p->ae[p->c++];
        pe->n = n;
        pe->k = *pk;
    }
}
