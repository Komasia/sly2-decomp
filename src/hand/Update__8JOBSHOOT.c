/* JOBSHOOT::Update (AIJOB vt slot 10): the base update; then until the job is done (0x1EF0A8) or its state stops
 * changing: while shooting, a finished move child (0x174FB8) ends the shot. Layout: SafeHouse port
 * (aipursuit.h JOBSHOOT). */
#include "h2_aijobs.h"

void Update__5AIJOB(AIJOB *pjob);
int FJobDone(JOBSHOOT *pjob) asm("FJobDone__FP5AIJOB");   /* SafeHouse: FJobDone */
int func_00174FB8(AIJOB *pjob);             /* the move job's state is 1 */
void SetShootState__8JOBSHOOTi(JOBSHOOT *pjob, int st);

// name: SafeHouse port (JOBSHOOT::Update)
void Update__8JOBSHOOT(JOBSHOOT *pjob)
{
    int st;
    Update__5AIJOB(&pjob->aijob);
    while (!FJobDone(pjob)) {
        st = pjob->st;
        if (st == SHOOTS_Shoot && func_00174FB8(pjob->aijob.pchild))
            SetShootState__8JOBSHOOTi(pjob, SHOOTS_None);
        if (st == pjob->st)
            break;
    }
}
