/* JOBLINK::NextRecord: on to the link's next record (its record state again), else done (no state, the job
 * unlocked). Layout: SafeHouse port (aijobs.h JOBLINK). */
#include "h2_aijobs.h"

void SetState__7JOBLINKi(JOBLINK *pjob, int st);
void UnlockJob__FP5AIJOB(AIJOB *pjob);

// name: SafeHouse port (JOBLINK::NextRecord)
void NextRecord__7JOBLINK(JOBLINK *pjob)
{
    if (++pjob->irec < pjob->plink->crec) {
        SetState__7JOBLINKi(pjob, LINKS_None);
        SetState__7JOBLINKi(pjob, LINKS_Record);
        return;
    }
    SetState__7JOBLINKi(pjob, LINKS_None);
    UnlockJob__FP5AIJOB(&pjob->aijob);
}
