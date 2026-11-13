/* JOBLINK::NextRecord: on to the link's next record (state 0 again), else done (state -1, the job unlocked).
 * Layout: SafeHouse port (aijobs.h JOBLINK). */
#include "aijob.h"

struct NAVLINK {
    /* 0x00 */ char pad0[0x50];
    /* 0x50 */ int crec;               /* the records */
};
struct JOBLINK {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ struct NAVLINK *plink;  /* field: SafeHouse port */
    /* 0x34 */ int irec;               /* field: SafeHouse port - the record walked to */
};
void SetState__7JOBLINKi(struct JOBLINK *pjob, int st);
void UnlockJob__FP5AIJOB(AIJOB *pjob);

// name: SafeHouse port (JOBLINK::NextRecord)
void NextRecord__7JOBLINK(struct JOBLINK *pjob)
{
    if (++pjob->irec < pjob->plink->crec) {
        SetState__7JOBLINKi(pjob, -1);
        SetState__7JOBLINKi(pjob, 0);
        return;
    }
    SetState__7JOBLINKi(pjob, -1);
    UnlockJob__FP5AIJOB(&pjob->aijob);
}
