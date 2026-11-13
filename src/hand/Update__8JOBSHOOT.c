/* JOBSHOOT::Update (AIJOB vt slot 10): the base update; then until the job is done (0x1EF0A8) or its state stops
 * changing: in state 0 a finished move child (0x174FB8) ends the shot (state -1). Layout: SafeHouse port
 * (aipursuit.h JOBSHOOT). */
#include "aijob.h"

struct JOBSHOOT {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ int st;     /* field: SafeHouse port */
};
void Update__5AIJOB(AIJOB *pjob);
int func_001EF0A8(struct JOBSHOOT *pjob);   /* SafeHouse: FJobDone */
int func_00174FB8(AIJOB *pjob);             /* the move job's state is 1 */
void SetShootState__8JOBSHOOTi(struct JOBSHOOT *pjob, int st);

// name: SafeHouse port (JOBSHOOT::Update)
void Update__8JOBSHOOT(struct JOBSHOOT *pjob)
{
    int st;
    Update__5AIJOB(&pjob->aijob);
    while (!func_001EF0A8(pjob)) {
        st = pjob->st;
        if (st == 0 && func_00174FB8(pjob->aijob.pchild))
            SetShootState__8JOBSHOOTi(pjob, -1);
        if (st == pjob->st)
            break;
    }
}
