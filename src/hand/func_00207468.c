#include "vtbl.h"
#include "cid.h"
/* the source's owner (+0x200): its team */
struct SOSRCOWNER { char pad[0x14]; int nTeam; };
struct SOSRC { char pad[0x200]; struct SOSRCOWNER *pownerSrc; };
/* the contact message: its source and zap kind */
struct CTMSG { struct SOSRC *psoSrc; int pad[2]; int zpk; };
struct GUARD { char pad[0xC]; VTENT *pvt; char pad2[4]; int nTeam; char pad3[0x26C - 0x18]; char bhvstk[4]; };
int FIsBasicDerivedFrom__FP5BASIC3CID(struct SOSRC *psoSrc, int cid);
int FAbsorbSoWkr__FP2SOP3WKR(struct GUARD *pguard, struct CTMSG *pctm);
void OfferJobMessage__FP5GUARDii(void *pbhvstk, int msg, struct CTMSG *pctm);
/* FAcceptContactGuard (0x207468): whether the guard accepts a contact message: unless vt slot 86 says so at once, a
 * hit that matters (vt slot 76 with the zap kind), one from an object of cid 0x4F on the guard's own team, or one
 * the SO absorbs (FAbsorbSoWkr); accepted ones go to the job stack as message 0xC. */
// name: SafeHouse port (FAcceptContactGuard)
int FAcceptContactGuard__FP3ALOP5CTMSG(struct GUARD *pguard, struct CTMSG *pctm)
{
    if (!((int (*)(void *))pguard->pvt[86].pfn)(VT_THIS(pguard, &pguard->pvt[86]))) {
        if (((int (*)(void *, int))pguard->pvt[76].pfn)(VT_THIS(pguard, &pguard->pvt[76]), pctm->zpk))
            return 1;
        if (pctm->psoSrc && FIsBasicDerivedFrom__FP5BASIC3CID(pctm->psoSrc, CID_BOMB) && pctm->psoSrc->pownerSrc->nTeam == pguard->nTeam)
            return 1;
        if (!FAbsorbSoWkr__FP2SOP3WKR(pguard, pctm))
            return 0;
    }
    OfferJobMessage__FP5GUARDii(pguard->bhvstk, 0xC, pctm);
    return 1;
}
