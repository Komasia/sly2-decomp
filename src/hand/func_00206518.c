#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct LOV { char pad[0xC]; VTENT *pvt; };
/* the home go-to command */
struct CMD { char pad[8]; qword *pposGoal; float radGoal; };
/* the guard's detector: its owner and the owner's attachment */
struct DETECTOR { char pad[0xE0]; void *pguardOwner; void *poxaOwner; };
struct GUARD {
    char pad0[0xEC]; void *poxa; char pad1[0x26C - 0xF0]; char bhvstk[0x2F0 - 0x26C]; struct CMD *pcmdHome;
    char pad2[0x300 - 0x2F4]; qword posHome; float radHome; char pad3[0x338 - 0x314]; int nHealthMax; int nHealth; int n340; int n344;
    char pad4[0x494 - 0x348]; int n494; void *pwatchA; void *pwatchB; char pad5[0xE78 - 0x4A0]; int nE78; char pad6[0xE84 - 0xE7C];
    int nE84; int nE88; char pad7[0xF64 - 0xE8C]; struct DETECTOR *pdet; char pad8[0xFD0 - 0xF68]; char move[0xFE8 - 0xFD0];
    int grfFE8; struct LOV *ploFEC;
};
extern int D_002E1E40, D_002F7900, D_002DD5BC, D_002DD648;   /* the player and the other objects the detector watches */
void func_001CB518(struct GUARD *pguard);
void ClearJobs__FP5ACTOR(void *pv);
void func_00209778(void *pv);
void SetGuardStateMask__FP5GUARDUl(struct GUARD *pguard, int n);
void func_0020CE40(void *pv);
void func_0020D1C8(void *pv);
void func_0020D1A0(void *pv);
qword PosOfLo__FP2LO(void *pv);
float RadStepHeading__FP4STEP(struct GUARD *pguard);
void SetStepPhysHeading__FP3ALOf(struct GUARD *pguard, float f);
unsigned long func_00207A20(int n);   /* the state mask bit of state n */
void *PkindeBest__FP5GUARDUl(struct GUARD *pguard, unsigned long m);
void func_00153EF8(struct DETECTOR *pdetector, struct GUARD *pguard, int n);
void FillPocket__FP2LO(struct GUARD *pguard);
void NextPocketPrize__FP2LO(struct GUARD *pguard);
struct LOV *func_00205438(struct GUARD *pguard, int cid);   /* PjobPush */
void ReparentBooty__FP3ALOii(struct DETECTOR *pdetector, struct GUARD *pguard, int n);

/* ResetGuard (0x206518): GUARD reset: the base reset, health and the counters back to their authored values, the job
 * stack and the current move cleared, no state, the ground watchers reset, home = where it stands now, the moves it
 * has (grfFE8: bits its kind table), the detector watching the players, the pocket refilled, the
 * option object +0xFEC reset (vt slot 9), the stand job (0x9C) started, the booty reparented to the detector. */
// name: SafeHouse port (ResetGuard)
void ResetGuard__FP2LO(struct GUARD *pguard)
{
    struct LOV *pjob;
    qword *pposHome;
    func_001CB518(pguard);
    pposHome = &pguard->posHome;
    pguard->nHealth = pguard->nHealthMax;
    pguard->nE88 = pguard->nE84;
    pguard->n344 = pguard->n340;
    ClearJobs__FP5ACTOR(pguard->bhvstk);
    func_00209778(pguard->move);
    SetGuardStateMask__FP5GUARDUl(pguard, 0);
    func_0020CE40(pguard->pwatchA);
    func_0020D1C8(pguard->pwatchB);
    func_0020D1A0(pguard->pwatchA);
    pguard->posHome = PosOfLo__FP2LO(pguard);
    pguard->radHome = RadStepHeading__FP4STEP(pguard);
    pguard->pcmdHome->pposGoal = pposHome;
    pguard->pcmdHome->radGoal = pguard->radHome;
    SetStepPhysHeading__FP3ALOf(pguard, pguard->radHome);
    pguard->grfFE8 = 0;   /* bits: 1 kind 0xF, 2 kind 9 (a walk), 4 kind 8, 8 kind 0x11 */
    if (PkindeBest__FP5GUARDUl(pguard, func_00207A20(9)))
        pguard->grfFE8 |= 2;
    else
        pguard->nE78 = 2;
    if (PkindeBest__FP5GUARDUl(pguard, func_00207A20(8)))
        pguard->grfFE8 |= 4;
    if (PkindeBest__FP5GUARDUl(pguard, func_00207A20(0xF)))
        pguard->grfFE8 |= 1;
    if (PkindeBest__FP5GUARDUl(pguard, func_00207A20(0x11)))
        pguard->grfFE8 |= 8;
    func_00153EF8(pguard->pdet, pguard, D_002E1E40);
    func_00153EF8(pguard->pdet, pguard, D_002F7900);
    func_00153EF8(pguard->pdet, pguard, D_002DD5BC);
    func_00153EF8(pguard->pdet, pguard, D_002DD648);
    if (pguard->n494) {
        FillPocket__FP2LO(pguard);
        NextPocketPrize__FP2LO(pguard);
    }
    if (pguard->ploFEC)
        ((void (*)(void *))pguard->ploFEC->pvt[9].pfn)(VT_THIS(pguard->ploFEC, &pguard->ploFEC->pvt[9]));
    pjob = func_00205438(pguard, 0x9C);
    ((void (*)(void *))pjob->pvt[8].pfn)(VT_THIS(pjob, &pjob->pvt[8]));
    ReparentBooty__FP3ALOii(pguard->pdet, pguard, 0xF);
    pguard->pdet->pguardOwner = pguard;
    pguard->pdet->poxaOwner = pguard->poxa;
}
