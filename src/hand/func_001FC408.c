struct R { float lo, hi; };
struct E { int n; struct R r; float g; };
struct P { char pad[0xA0]; int c[6]; struct E ae[6][8]; };
void func_001FB658(struct P *, int, int);
void func_001FC408(struct P *p, unsigned int k, int n, struct R *pr, float g)
{
    if (k < 6 && p->c[k] < 8) {
        struct E *pe;
        func_001FB658(p, 0x200, 0x200);
        pe = &p->ae[k][p->c[k]++];
        pe->n = n;
        pe->g = g;
        pe->r = *pr;
        if (pe->r.lo == pe->r.hi) pe->r.hi += 1.0f;
    }
}
