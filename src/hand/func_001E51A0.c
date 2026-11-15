/* HoldRunEffects: the script holds a STEP actor's effect (kind, value) while it runs: added once per actor (at most
 * 4, JSG apstepHold / anHold5 / anHold6) and applied through the actor's vt slot 0x53; ReleaseRunEffects undoes it. */
#include "relay.h"
#include "cid.h"
struct STEP { int pad[3]; VTENT *vt; };
int FIsBasicDerivedFrom__FP5BASIC3CID(void *p, int cid);
// name: SafeHouse port (HoldRunEffects)
void HoldRunEffects__FP3RUNP2LOii(JSG *pjsg, struct STEP *pstep, int nHold5, int nHold6)
{
    int i;
    if (!FIsBasicDerivedFrom__FP5BASIC3CID(pstep, CID_STEP)) return;
    for (i = 0; i < pjsg->cstepHold; i++)
        if (pjsg->apstepHold[i] == pstep) return;
    if ((unsigned)pjsg->cstepHold >= 4) return;
    pjsg->anHold5[pjsg->cstepHold] = nHold5;
    pjsg->anHold6[pjsg->cstepHold] = nHold6;
    pjsg->apstepHold[pjsg->cstepHold] = pstep;
    pjsg->cstepHold++;
    ((void (*)(void *, int, int))pstep->vt[0x53].pfn)(VT_THIS(pstep, &pstep->vt[0x53]), nHold5, nHold6);
}
