/* FOverlapOxa: whether two attachments overlap: their boxes do, and the larger of the objects' overlap kinds
 * (vt slot 61, combined by 0x134310) is neither 1 nor 3 (both pass). Layout: SafeHouse port (so.h OXA). */
#include "vtbl.h"
struct LO { char pad[0xC]; VTENT *pvt; };
struct OXA { float posMin[4]; float posMax[4]; char pad[0x60 - 0x20]; struct LO *pso; };   /* field: SafeHouse port */
int func_00134310(int n1, int n2);   /* the larger */
static __inline__ int OverlapKind(struct LO *pso, struct LO *psoOther)
{
    return ((int (*)(void *, struct LO *))pso->pvt[61].pfn)(VT_THIS(pso, &pso->pvt[61]), psoOther);
}
// name: SafeHouse port (FOverlapOxa)
int FOverlapOxa__FP3OXAT0Pv(void *psw, struct OXA *poxa, struct OXA *poxaOther)
{
    int n1, n2, n;
    if (poxa->posMin[0] >= poxaOther->posMax[0] || poxa->posMin[1] >= poxaOther->posMax[1] || poxa->posMin[2] >= poxaOther->posMax[2] ||
        poxaOther->posMin[0] >= poxa->posMax[0] || poxaOther->posMin[1] >= poxa->posMax[1] || poxaOther->posMin[2] >= poxa->posMax[2])
        return 0;
    n1 = OverlapKind(poxa->pso, poxaOther->pso);
    n2 = OverlapKind(poxaOther->pso, poxa->pso);
    n = func_00134310(n1, n2);
    return n != 1 && n != 3;
}
