struct P { int a; int b; };
struct E { char pad[0x94]; int f94; int f98; int f9c; char pad2[0x100 - 0xa0]; };
struct S { char pad[0x50]; int c; struct E *ae; };
void DemoteAsegaOnXf__FiiP2XF(void *, struct S *, struct E *);
// name: SafeHouse port (DemoteAsegaOnAlo)
void DemoteAsegaOnAlo__FP5ASEGAP3ALOiPv(void *pv, struct S *p, int cp, struct P *ap) {
    int i, j;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        for (j = 0; j < cp; j++) {
            struct P *pp = &ap[j];
            if ((pe->f9c == pp->a || pp->a == -1) && (pe->f94 == pp->b || pp->b == -1)) {
                DemoteAsegaOnXf__FiiP2XF(pv, p, pe);
                break;
            }
        }
    }
}
