struct K { int a, b; };
struct E { int n; int a[7]; float g; struct K k; int pad[13]; };
struct S { char pad[0x190]; unsigned int c; int pad2[3]; struct E ae[8]; };
void func_001D4B48(struct S *p, int n, struct K *pk, float g) {
    if (p->c < 8) {
        struct E *pe = &p->ae[p->c++];
        pe->n = n;
        pe->g = g;
        pe->k = *pk;
    }
}
