struct S { int a, b, k, c; };
static __inline__ int FX(struct S *p) { return p->c == 9 || p->c == 10; }
int func_00194640(struct S *p) {
    switch (p->k) {
    case 8: if (FX(p)) goto one; break; case 0xC: one: return 1;
    }
    return 0;
}
