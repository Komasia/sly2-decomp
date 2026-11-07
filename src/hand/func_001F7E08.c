struct E { char pad[0xB0]; };
struct P { char pad[0xE0]; int c; struct E *ae; };
// name: SafeHouse port (CsoeCollect)
int CsoeCollect__FP3ALOPvN21(struct P *p, int (*pfn)(void *, struct E *), void *pv, struct E **ape)
{
    int n = 0;
    int i;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        if (!pfn || pfn(pv, pe)) {
            ape[n++] = pe;
        }
    }
    return n;
}
