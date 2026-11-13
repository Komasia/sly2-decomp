/* SetJobCur: make a job the current one (TASKMGR +0x3B0C, in the world) and keep its id (JOB +0x18, or -1) in
 * D_002DEB40. */
struct JOB {
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ int id;
};
struct TASKMGR {
    /* 0x0000 */ char pad0[0x3b0c];
    /* 0x3b0c */ struct JOB *pjobCur;   /* field: SafeHouse port (task.h) */
};
extern int D_002DEB40;   /* the current job's id */

// name: SafeHouse port (SetJobCur)
void SetJobCur__FP7TASKMGRP3JOB(struct TASKMGR *ptaskmgr, struct JOB *pjob)
{
    ptaskmgr->pjobCur = pjob;
    if (pjob) {
        D_002DEB40 = pjob->id;
        return;
    }
    D_002DEB40 = -1;
}
