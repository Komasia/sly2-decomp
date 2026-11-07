struct E { int n0; int k4; int k8; int fl; int pad[2]; };
struct P { char pad[0x58]; int c; struct E *ae; };
int PsmtChoose__FPviT0(struct P *, int, struct E **);
// name: SafeHouse port (PsmtLeaving)
int PsmtLeaving__FP2SMUii(struct P *p, int mask, int k)
{
    struct E *ape[64];
    int n = 0;
    int i;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        if ((pe->fl & mask) && (pe->k4 == k || ((pe->fl & 1) && pe->k8 == k)))
            ape[n++] = pe;
    }
    if (n == 0) return 0;
    return PsmtChoose__FPviT0(p, n, ape);
}
