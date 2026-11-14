/* SetTaskChk: the task whose checkpoint the job restarts at (SafeHouse task.cpp SetJobCur / SetTaskCur / SetTaskChk,
 * orig 0x00165DC0 / 0x00165DE8 / 0x00165E10; task.h: TASKMGR +0x3B14 ptaskChk): set, and its oid kept in D_002DEB48
 * (-1: none). */
struct TASK {
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ int oid;
};
struct SW {
    /* 0x0000 */ char pad0[0x3b14];
    /* 0x3b14 */ struct TASK *ptaskChk;   /* field: SafeHouse port */
};
extern int D_002DEB48;   /* the checkpoint task's oid (SafeHouse g_taskmgr.oidQueued) */

// name: SafeHouse port (SetTaskChk; the signature as SetJobCur__FP7TASKMGRP3JOB 0x165DC0)
void SetTaskChk__FP7TASKMGRP4TASK(struct SW *psw, struct TASK *p)
{
    psw->ptaskChk = p;
    if (p != 0) {
        D_002DEB48 = p->oid;
        return;
    }
    D_002DEB48 = -1;
}
