#include "vtbl.h"
struct LOV { char pad[0xC]; VTENT *pvt; };
/* an attachment (OXA): its object and flags */
struct OXA { char pad[0x60]; struct LOV *pso; char pad2[0xC]; long grf; };
struct ALOX { char pad[0xEC]; struct OXA *poxa; };
struct SOE { int pad; struct ALOX *palo; int pad2[2]; long grf; };
int func_00134310(int okA, int okB);   /* combines the two overlap kinds */
#define VC61(o, a) /* vt slot 61: the overlap kind with a */ ((int (*)(void *, struct LOV *))(o)->pvt[61].pfn)(VT_THIS((o), &(o)->pvt[61]), a)
/* NOverlapKind (0x20F948): a collision-entry filter: whether an entry of another attachment (not a sensor entry, nor
 * of one marked 4) overlaps this one in a kind other than 1 / 3 (both objects' vt slot 61, combined). */
// name: SafeHouse port (NOverlapKind)
int NOverlapKind__FP3ALOT0(struct OXA *poxa, struct SOE *psoe)
{
    struct OXA *poxaOther = psoe->palo->poxa;
    int okA, okB, ok;
    if (!(psoe->grf & (1L << 48)) && (poxaOther->grf & 4))
        return 0;
    if ((psoe->grf & (1L << 48)) || poxaOther == poxa)
        return 0;
    okA = VC61(poxa->pso, poxaOther->pso);
    okB = VC61(poxaOther->pso, poxa->pso);
    ok = func_00134310(okA, okB);
    return ok != 1 && ok != 3;
}
