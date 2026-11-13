/* UnlockJob: the job's hold on its actor released: the jobs above it count one hold less (+0x20), and a guard
 * (cid 0x38) has its activation lock released (UnlockGuardActivation). Layout: SafeHouse port (ai.h AIJOB). */
#include "aijob.h"

int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
void UnlockGuardActivation__FP5GUARDi(struct GUARD *pguard);

// name: SafeHouse port (UnlockJob)
void UnlockJob__FP5AIJOB(AIJOB *pjob)
{
    AIJOB *pjobParent;
    if (pjob->fLocked != 0) {
        pjob->fLocked = 0;
        if (FIsBasicDerivedFrom__FP5BASIC3CID(pjob->pguard, 0x38))
            UnlockGuardActivation__FP5GUARDi(pjob->pguard);
        for (pjobParent = pjob->pparent; pjobParent != 0; pjobParent = pjobParent->pparent)
            pjobParent->cLock--;
    }
}
