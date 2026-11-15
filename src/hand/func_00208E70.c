#include "stepguard.h"
#include "cid.h"
struct LOF { char pad[0x28]; unsigned long grfLo; };
/* the hit (0xA1 / 0xA2: its source) and carry (0xB1: its owner) jobs */
struct JOBHIT { char pad[0x50]; void *psource; char pad2[0x5C - 0x54]; void *ploOwner; };
/* the actor's current target (+0x10DC) and its kind, and whether it can be targeted */
struct ACTOR { char pad[0x10DC]; void *ploTarget; int pad2; int nTargetKind; char pad3[0x10F0 - 0x10E8]; int fTargetable; };
extern float D_002C3D90;   /* -500 */
extern float D_002C3D94;   /* 0.7 */
void LookScore__FP5ACTORP2LOPP2LOPfT3(struct ACTOR *pactor, struct GUARD *pguard, void *pploTarget, float *pdxy, float *pdz);
unsigned long func_00207A20(int n);
int FGuardState(struct GUARD *pguard, int n) asm("FGuardState__FP5GUARDi");
struct JOBHIT *func_00205458(struct GUARD *pguard, int cid);   /* PjobFind */
int FIsBasicDerivedFrom__FP5BASIC3CID(void *po, int n);
qword PosOfLo__FP2LO(void *pv);
int FPointInShape__FP2LOG9VU_VECTOR(struct LOF *pl, qword q);
int FCheckLm(void *plm, float g) asm("FCheckLm__FP2LMf");

/* NRankGuard (0x208E70): the guard's rank for the actor: 4 the actor is the object of its pursuit / hit / carry
 * (or any actor is), 3 the actor is inside its volume +0x3F4 (+0x3F8 when it is the actor's current target of
 * kind 3), 2 near (within sNear * 0.7 and the near height range), 1 far (within sFar and the far height range),
 * else 0; *pgDist the horizontal distance (500 nearer for the actor it carries). Field names: SafeHouse port
 * (target.cpp NRankGuard). */
// name: SafeHouse port (NRankGuard)
int NRankGuard__FP5GUARDP5ACTORPf(struct GUARD *pguard, struct ACTOR *pactor, float *pgDist)
{
    float dxy, dz;
    void *ploGrab;
    struct LOF *ploVolume;
    void *plmNear;
    LookScore__FP5ACTORP2LOPP2LOPfT3(pactor, pguard, &pactor->ploTarget, &dxy, &dz);
    if (pgDist)
        *pgDist = dxy;
    if (!(pguard->grfState & func_00207A20(1))) {
        if (pguard->fNear && pactor->fTargetable) {
            if (FGuardState(pguard, 0x1D))
                ploGrab = pguard->ploPursued;
            else if (FGuardState(pguard, 5))
                ploGrab = func_00205458(pguard, 0xA1)->psource;
            else if (FGuardState(pguard, 6))
                ploGrab = func_00205458(pguard, 0xA2)->psource;
            else if (FGuardState(pguard, 0x17)) {
                ploGrab = func_00205458(pguard, 0xB1)->ploOwner;
                if (ploGrab == pactor)
                    *pgDist += D_002C3D90;
            } else
                ploGrab = 0;
            if (ploGrab) {
                if (ploGrab == pactor)
                    return 4;
                if (FIsBasicDerivedFrom__FP5BASIC3CID(ploGrab, CID_ACTOR))
                    return 4;
            }
        }
        if (pguard == pactor->ploTarget && pactor->nTargetKind == 3)
            ploVolume = pguard->plo3F8;
        else
            ploVolume = pguard->plo3F4;
        if (ploVolume && !!((ploVolume->grfLo >> 60) & 1) && FPointInShape__FP2LOG9VU_VECTOR(ploVolume, PosOfLo__FP2LO(pactor)))
            return 3;
    }
    plmNear = FGuardState(pguard, 0x17) ? pguard->lmNearCarry : pguard->lmNear;
    if (dxy <= pguard->sNear * D_002C3D94 && FCheckLm(plmNear, dz) && pguard->fNear)
        return 2;
    if (dxy <= pguard->sFar && FCheckLm(pguard->lmFar, dz) && pguard->fFar)
        return 1;
    return 0;
}
