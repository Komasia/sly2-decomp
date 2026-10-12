extern int D_002C35B4;
extern int D_003DA570;
struct S { char p0[0x48]; int n48; char p1[0x250-0x4C]; int n250; };
int func_001DBBA0(struct S *p) {
    int n = p->n250 + D_002C35B4;
    if (D_003DA570) {
        n -= (p->n250 > 0);
        n -= (n < p->n48);
    }
    return n;
}
