/* PoxRemoveSw: the overlap record of poxaOther's object unlinked from poxa's list (OXA +0x64) and returned (null:
 * none). Layout: SafeHouse port (so.h OX / OXA, bbmark.cpp). */
struct OX { int pxp; struct OX *poxNext; int poxOther; int psoOther; };   /* field: SafeHouse port */
struct OXA { char pad[0x64]; struct OX *pox; };
struct OXAK { char pad[0x60]; int pso; };
// name: SafeHouse port (PoxRemoveSw)
struct OX *PoxRemoveSw__FP2SWP3OXAT1(void *psw, struct OXA *poxa, struct OXAK *poxaOther)
{
    int pso = poxaOther->pso;
    struct OX *pox = poxa->pox;
    if (pox) {
        struct OX **ppox = &pox->poxNext;
        if (pox->psoOther == pso) {
            poxa->pox = pox->poxNext;
        } else {
            for (;;) {
                pox = pox->poxNext;
                if (!pox) break;
                if (pox->psoOther == pso) { *ppox = pox->poxNext; break; }
                ppox = &pox->poxNext;
            }
        }
    }
    return pox;
}
