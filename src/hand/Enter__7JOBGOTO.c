/* JOBGOTO::Enter (AIJOB vt slot 8): the guard state of the go-to (+0x38) added, the base enter, state 4 and the
 * search for the goal. Layout: SafeHouse port (aijobs.h JOBGOTO). */
#include "aijob.h"

struct JOBGOTO {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ int st;      /* field: SafeHouse port */
    /* 0x34 */ float tSt;   /* field: SafeHouse port */
    /* 0x38 */ int nAnim;   /* field: SafeHouse port - the guard state (-1 none) */
};
void AddGuardState__FP5GUARDi(struct GUARD *pguard, int gs);
void Enter__5AIJOB(AIJOB *pjob);
void SetState__7JOBGOTOi(struct JOBGOTO *pjob, int st);
void Search__7JOBGOTO(struct JOBGOTO *pjob);

// name: SafeHouse port (JOBGOTO::Enter)
void Enter__7JOBGOTO(struct JOBGOTO *pjob)
{
    int gs = pjob->nAnim;
    if (gs != -1)
        AddGuardState__FP5GUARDi(pjob->aijob.pguard, gs);
    Enter__5AIJOB(&pjob->aijob);
    SetState__7JOBGOTOi(pjob, 4);
    Search__7JOBGOTO(pjob);
}
