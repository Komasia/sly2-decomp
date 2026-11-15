/* JOBLADDER::Update: climbing: at the goal: state 1; otherwise the direction set from the goal, the speed eased
 * (GSmooth, an SMP of the move's speed (+0x198) as its limit) toward the move's speed in that direction, and the
 * guard's place along the pipe moved by it (wrapped). Every frame the guard's heading frame (+0x1B0) is the pipe's
 * frame there (MatPipeFrame). */
#include "clock.h"
#include "h2_aijobs.h"

extern float D_002DFB7C;                /* the target speed (a static) */
struct GUARD {
    /* 0x000 */ char pad0[0x198];
    /* 0x198 */ float svMove;           /* field: SafeHouse port (STEP +0x198: the move's speed) */
    /* 0x19c */ char pad19C[0x14];
    /* 0x1b0 */ char matHeading[0xF84 - 0x1B0];   /* field: SafeHouse port (STEP +0x1B0: the heading's frame) */
    /* 0xf84 */ int pcrvMove;           /* field: SafeHouse port (ploMove) - the pipe */
    /* 0xf88 */ float sMove;            /* field: SafeHouse port */
    /* 0xf8c */ int fForward;           /* field: SafeHouse port (nMoveKind) */
};
/* a smoothing's parameters: the limit, then two more */
struct SMP { float gLimit, g4, g8; };
void Update__5AIJOB(JOBLADDER *pjob);
int func_0017D188(JOBLADDER *pjob);
void SetLadderState__9JOBLADDERi(JOBLADDER *pjob, int st);
float GSmooth__FfffP3SMPPf(float gCur, float gGoal, float dt, struct SMP *psmp, int pgVel);
float SWrapCrv__FP3CRVf(int pcrv, float s);
void MatPipeFrame__FP2LOfiPv(int plo, float s, int fForward, void *pmat);

// name: SafeHouse port (JOBLADDER::Update)
void Update__9JOBLADDER(JOBLADDER *pjob)
{
    int st;
    Update__5AIJOB(pjob);
    do {
        st = pjob->st;
        if (st == 0) {
            if (func_0017D188(pjob)) {
                SetLadderState__9JOBLADDERi(pjob, 1);
            } else {
                struct SMP smp;
                float gSpeed;
                pjob->aijob.pguard->fForward = pjob->aijob.pguard->sMove < pjob->sGoal;
                if (pjob->aijob.pguard->fForward) D_002DFB7C = -pjob->aijob.pguard->svMove;
                else D_002DFB7C = pjob->aijob.pguard->svMove;
                {
                    float gGoal = D_002DFB7C;
                    smp.g4 = 0.0f;
                    smp.g8 = 0.1f;
                    smp.gLimit = __builtin_fabsf(gGoal);
                    gSpeed = GSmooth__FfffP3SMPPf(pjob->gSpeed, gGoal, g_clock.dt, &smp, 0);
                }
                pjob->gSpeed = gSpeed;
                pjob->aijob.pguard->sMove = SWrapCrv__FP3CRVf(pjob->aijob.pguard->pcrvMove, pjob->aijob.pguard->sMove + gSpeed * g_clock.dt);
            }
        }
    } while (pjob->st != st);
    {
        struct GUARD *pguard = pjob->aijob.pguard;
        MatPipeFrame__FP2LOfiPv(pguard->pcrvMove, pguard->sMove, pguard->fForward, pguard->matHeading);
    }
}
