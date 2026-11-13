/* JOBGOTO::Exit (AIJOB vt slot 9): the go-to ends: the base exit, state -1, and the guard state it added (+0x38)
 * removed. Layout: SafeHouse port (aijobs.h JOBGOTO). */
#include "aijob.h"

struct JOBGOTO {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ int st;      /* field: SafeHouse port */
    /* 0x34 */ float tSt;   /* field: SafeHouse port */
    /* 0x38 */ int nAnim;   /* field: SafeHouse port - the guard state (-1 none) */
};
void Exit__5AIJOB(AIJOB *pjob);
void SetState__7JOBGOTOi(struct JOBGOTO *pjob, int st);
void RemoveGuardState__FP5GUARDi(struct GUARD *pguard, int gs);

// name: SafeHouse port (JOBGOTO::Exit)
void Exit__7JOBGOTO(struct JOBGOTO *pjob)
{
    int gs;
    Exit__5AIJOB(&pjob->aijob);
    SetState__7JOBGOTOi(pjob, -1);
    gs = pjob->nAnim;
    if (gs != -1)
        RemoveGuardState__FP5GUARDi(pjob->aijob.pguard, gs);
}
