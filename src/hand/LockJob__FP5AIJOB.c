/* LockJob: the job holds its actor: the jobs above it count one more hold (+0x20), and a guard (cid 0x38) is kept
 * active (LockGuardActivation). Layout: SafeHouse port (ai.h AIJOB). */
#include "aijob.h"

int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
void LockGuardActivation__FP5GUARDi(struct GUARD *pguard);

// name: SafeHouse port (LockJob)
void LockJob__FP5AIJOB(AIJOB *pjob)
{
    AIJOB *pjobParent;
    if (pjob->fLocked == 0) {
        pjob->fLocked = 1;
        if (FIsBasicDerivedFrom__FP5BASIC3CID(pjob->pguard, 0x38))
            LockGuardActivation__FP5GUARDi(pjob->pguard);
        for (pjobParent = pjob->pparent; pjobParent != 0; pjobParent = pjobParent->pparent)
            pjobParent->cLock++;
    }
}
