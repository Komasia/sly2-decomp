#include "clock.h"
struct A { char pad[0x74]; float g74; };
struct B { char pad[0x1C]; float g1C; };
struct KINDE { int kind; struct A *pa; struct B *pb; int nC; };
struct GUARD { char pad[0x1A4]; int n1A4; char pad2[0xFD0 - 0x1A8]; char moveref[0x20]; float uGaitPhase; float tGaitPhase; };
struct JOBMOVE { char pad[0x10]; struct GUARD *pguard; char pad2[0x1C]; int st; float tSt; char pad3[8]; struct KINDE *pkinde; };
void func_00209788(void *pjob, struct JOBMOVE *ps);
void func_00209790(void *pjob, struct JOBMOVE *ps);
int FGuardState(struct GUARD *pguard, int stNew) asm("FGuardState__FP5GUARDi");
void PlayKinde__FP5KINDEP5GUARDif(struct KINDE *pkinde, struct GUARD *pguard, int stNew, float g);
void StopKinde__FP5KINDE(struct KINDE *pkinde);
void UnlockJob__FP5AIJOB(struct JOBMOVE *pjob);
/* JOBMOVE::SetMoveState: 0 plays the move's kind entry (a walk resumes the guard's gait phase when it was just
 * walking: +0xFF0 at +0xFF4), 1 ends it: unlocked, the gait phase kept, the entry stopped and the move released. */
// name: SafeHouse port (JOBMOVE::SetMoveState)
void SetMoveState__7JOBMOVEi(struct JOBMOVE *pjob, int stNew) {
    if (pjob->st == stNew) return;
    pjob->st = stNew;
    pjob->tSt = g_clock.t;
    switch (stNew) {
    case 0: {
        float f;
        func_00209788(pjob->pguard->moveref, pjob);
        if (pjob->pkinde->kind == 0 && FGuardState(pjob->pguard, 9) && g_clock.t == pjob->pguard->tGaitPhase)
            f = pjob->pkinde->pa->g74 * pjob->pguard->uGaitPhase;
        else
            f = 0.0f;
        PlayKinde__FP5KINDEP5GUARDif(pjob->pkinde, pjob->pguard, pjob->pkinde->nC | 1, f);
        break;
    }
    case 1:
        UnlockJob__FP5AIJOB(pjob);
        if (pjob->pkinde) {
            if (pjob->pkinde->kind == 0 && FGuardState(pjob->pguard, 9)) {
                pjob->pguard->uGaitPhase = pjob->pkinde->pb->g1C / pjob->pkinde->pa->g74;
                pjob->pguard->tGaitPhase = g_clock.t;
            }
            StopKinde__FP5KINDE(pjob->pkinde);
            pjob->pkinde = 0;
            func_00209790(pjob->pguard->moveref, pjob);
        }
        pjob->pguard->n1A4 = 0;
        break;
    }
}
