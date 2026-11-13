/* JOBSTRIKE::Enter (AIJOB vt slot 8): the guard is striking (+0xF3C); the move's enter; a kind-2 entry (a leap at the
 * target) makes its player ballistic (+0x60) and steep (+0x64), and the target is followed (+0x50).
 * Layout: SafeHouse port (aipursuit.h JOBSTRIKE, guard.h KINDE). */
#include "aijob.h"

struct GUARD {
    /* 0x000 */ char pad0[0xf3c];
    /* 0xf3c */ int fF3C;        /* field: SafeHouse port - striking */
};
struct K2PLAY {
    /* 0x00 */ char pad0[0x60];
    /* 0x60 */ int fBallistic;   /* field: SafeHouse port */
    /* 0x64 */ int fSteep;       /* field: SafeHouse port */
};
struct KINDE {
    /* 0x00 */ int k;            /* field: SafeHouse port */
    /* 0x04 */ void *pv;
    /* 0x08 */ struct K2PLAY *pvState;   /* field: SafeHouse port (kind 2's player) */
};
struct JOBSTRIKE {
    /* 0x00 */ JOBMOVE jobmove;
    /* 0x50 */ int f50;          /* field: SafeHouse port - the target followed */
};
void Enter__7JOBMOVE(struct JOBSTRIKE *pjob);

// name: SafeHouse port (JOBSTRIKE::Enter)
void Enter__9JOBSTRIKE(struct JOBSTRIKE *pjob)
{
    pjob->jobmove.aijob.pguard->fF3C = 1;
    Enter__7JOBMOVE(pjob);
    if (pjob->jobmove.pkinde->k == 2) {
        pjob->jobmove.pkinde->pvState->fBallistic = 1;
        pjob->jobmove.pkinde->pvState->fSteep = 1;
        pjob->f50 = 1;
    }
}
