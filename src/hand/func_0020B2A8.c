#include "cid.h"
typedef int qword __attribute__((mode(TI)));
/* the object moved on (a HOOK: its kind) */
struct LOK { char pad[0x124]; int nKind; };
struct GUARD { char pad[0xF80]; int kMove; struct LOK *ploMove; int sMove; int nMoveKind; void *ploHands; };
int FIsBasicDerivedFrom__FP5BASIC3CID(struct LOK *pbasic, int cid);
qword PosOfLo__FP2LO(void *plo);
void NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(struct LOK *pcrv, qword pos, int ppos, int pdir, int pu, int pdist, int *ps);
void PairActorWith__FP5ACTORP2LOi(struct GUARD *pguard, struct LOK *plo, int fPair);

/* AttachGuardMove (0x20B2A8): the guard moves on plo, paired with it: a PIPE (kMove 1, its place on the curve
 * the nearest to its hands' point), a rail (CID_PATH_0D: kMove 0, the nearest to the guard), a HOOK of kind 3 (2)
 * or a SPIRE (3); anything else is dropped. */
// name: SafeHouse port (AttachGuardMove)
void AttachGuardMove__FP5GUARDP2LOi(struct GUARD *pguard, struct LOK *plo, int nMoveKind)
{
    pguard->ploMove = plo;
    pguard->nMoveKind = nMoveKind;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(plo, CID_PIPE)) {
        pguard->kMove = 1;
        NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(pguard->ploMove, PosOfLo__FP2LO(pguard->ploHands), 0, 0, 0, 0, &pguard->sMove);
        PairActorWith__FP5ACTORP2LOi(pguard, pguard->ploMove, 1);
    } else if (FIsBasicDerivedFrom__FP5BASIC3CID(pguard->ploMove, CID_PATH_0D)) {
        pguard->kMove = 0;
        NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(pguard->ploMove, PosOfLo__FP2LO(pguard), 0, 0, 0, 0, &pguard->sMove);
        PairActorWith__FP5ACTORP2LOi(pguard, pguard->ploMove, 1);
    } else if (FIsBasicDerivedFrom__FP5BASIC3CID(pguard->ploMove, CID_HOOK) && pguard->ploMove->nKind == 3) {
        pguard->kMove = 2;
        PairActorWith__FP5ACTORP2LOi(pguard, pguard->ploMove, 1);
    } else if (FIsBasicDerivedFrom__FP5BASIC3CID(pguard->ploMove, CID_SPIRE)) {
        pguard->kMove = 3;
        PairActorWith__FP5ACTORP2LOi(pguard, pguard->ploMove, 1);
    } else {
        pguard->ploMove = 0;
    }
}
