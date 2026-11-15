/* JOBGOTO::Update: while the guard walks (+0xFE8 bit 1) and the job is not done, steps the state machine until it
 * settles: on a path: arrived at the goal's region -> the link; the way searched again when it is old or the
 * navigation changed; stuck -> straight on to a point a bit further along the path; crossing a link / at the point:
 * searched again once done. */
#include "clock.h"
#include "h2_aijobs.h"

extern float D_002BE758;   /* how long a found way is kept */
extern float D_002BE75C;   /* how far on along the path when stuck */
struct NAVSERIAL { char pad0[0x28]; int nSerial; };
struct SW { char pad0[0x45CC]; struct NAVSERIAL *pnavserial; };
extern struct SW g_sw;
/* the follow child: its path and the distance on it (field: SafeHouse port, aijobs.h JOBFOLLOW) */
struct JOBFOLLOW { char pad0[0x30]; struct CRV *pcrv; float s; };
/* the guard's fields used here */
struct VECTOR3 { float x, y, z; };
struct GUARD {
    /* 0x000 */ char pad0[0x218];
    /* 0x218 */ struct VECTOR3 *pposProbe; /* field: SafeHouse port (STEP +0x218) - the floor probe's point */
    /* 0x21c */ char pad21C[0xFE8 - 0x21C];
    /* 0xfe8 */ int grfFE8;             /* field: SafeHouse port - 2: it walks */
};
void Update__5AIJOB(JOBGOTO *pjob);
int FJobDone(JOBGOTO *pjob) asm("FJobDone__FP5AIJOB");
int FArrived__9JOBFOLLOW(struct JOBFOLLOW *pjobFollow);
void SetState__7JOBGOTOi(JOBGOTO *pjob, int st);
int FStuck__9JOBFOLLOW(struct JOBFOLLOW *pjobFollow);
float SMaxCrv__FP3CRV(struct CRV *pcrv);
void EvalCrvS(struct CRV *pcrv, float s, qword *ppos, int n) asm("EvalCrvS__FP3CRVfP6VECTORT2");
int func_0017E570(struct JOBFOLLOW *pjobLink);        /* JOBLINK: crossed */
int FDone__11JOBNAVPOINT(struct JOBFOLLOW *pjobPoint);
void Search__7JOBGOTO(JOBGOTO *pjob);

// name: SafeHouse port (JOBGOTO::Update)
void Update__7JOBGOTO(JOBGOTO *pjob)
{
    int st;
    Update__5AIJOB(pjob);
    if (!(pjob->aijob.pguard->grfFE8 & 2)) return;
    while (!FJobDone(pjob)) {
        st = pjob->st;
        switch (st) {
        case GOTOS_Path:
        case GOTOS_PathOpen:
            {
                struct JOBFOLLOW *pjobFollow = (struct JOBFOLLOW *)pjob->aijob.pchild;
                if (st == GOTOS_PathOpen && FArrived__9JOBFOLLOW(pjobFollow)) {
                    SetState__7JOBGOTOi(pjob, GOTOS_Link);
                } else if (g_clock.t - pjob->tSearch > D_002BE758 || pjob->nSerial != g_sw.pnavserial->nSerial) {
                    Search__7JOBGOTO(pjob);
                } else if (FStuck__9JOBFOLLOW(pjobFollow)) {
                    float s = pjobFollow->s + D_002BE75C;
                    float sMax = SMaxCrv__FP3CRV(pjobFollow->pcrv);
                    pjob->goalFallback.pcrv = 0;
                    pjob->goalFallback.plo = 0;
                    EvalCrvS(pjobFollow->pcrv, s < sMax ? s : sMax, &pjob->goalFallback.pos, 0);
                    ((float *)&pjob->goalFallback.pos)[2] = pjob->aijob.pguard->pposProbe->z;
                    SetState__7JOBGOTOi(pjob, GOTOS_Point);
                }
            }
            break;
        case GOTOS_Link:
            if (func_0017E570((struct JOBFOLLOW *)pjob->aijob.pchild)) Search__7JOBGOTO(pjob);
            break;
        case GOTOS_Point:
            if (FDone__11JOBNAVPOINT((struct JOBFOLLOW *)pjob->aijob.pchild)) Search__7JOBGOTO(pjob);
            break;
        }
        if (st != pjob->st) continue;
        break;
    }
}
