/* TellBarrierContacts (queued by OnBarrierXpNew): each object in contact with the barrier (the other end of each
 * contact of each overlap in its attachment +0xEC, 16 distinct at most) is put in +0x17C and the barrier gets its
 * splice event 5 (vt slot 3). Layout: SafeHouse port (barrier.cpp); XP / OXA names after Sly 1. */
#include "vtbl.h"
struct BARRIER;
struct XPEND { int x0; int x4; struct BARRIER *pso; char pad[0x34]; };
struct XP { struct XPEND axpe[2]; char pad[0xAC - 0x80]; struct XP *pnext; };
struct XPL { struct XP *pxpFirst; struct XPL *pnext; };
struct OXA { char pad[0x64]; struct XPL *pxplFirst; };
struct BARRIER { char pad[0xC]; VTENT *pvt; char pad1[0xEC - 0x10]; struct OXA *poxa; char pad2[0x17C - 0xF0]; struct BARRIER *psoToucher; };
static __inline__ int IxpeSelf(struct XP *pxp, struct BARRIER *pbarrier) { return pxp->axpe[0].pso == pbarrier ? 0 : 1; }
// name: SafeHouse port (TellBarrierContacts)
void TellBarrierContacts__FPv(struct BARRIER *pbarrier)
{
    struct BARRIER *apso[16];
    int cpso = 0;
    struct XPL *pxpl;
    int i;
    for (pxpl = pbarrier->poxa->pxplFirst; pxpl; pxpl = pxpl->pnext) {
        struct XP *pxp;
        for (pxp = pxpl->pxpFirst; pxp; pxp = pxp->pnext) {
            struct BARRIER *psoOther = pxp->axpe[1 - IxpeSelf(pxp, pbarrier)].pso;
            for (i = 0; i < cpso; i++)
                if (psoOther == apso[i])
                    break;
            if (i >= cpso) {
                apso[cpso++] = psoOther;
                if (cpso >= sizeof(apso) / sizeof(apso[0]))
                    goto done;
            }
        }
    }
done:
    for (i = 0; i < cpso; i++) {
        pbarrier->psoToucher = apso[i];
        ((void (*)(void *, int, int, int, int, int))pbarrier->pvt[3].pfn)(VT_THIS(pbarrier, &pbarrier->pvt[3]), 5, 0, 0, 0, 0);
    }
}
