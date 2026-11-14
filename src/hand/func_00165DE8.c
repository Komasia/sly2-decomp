/* SetTaskCur: the world's current task (SafeHouse task.cpp SetJobCur / SetTaskCur / SetTaskChk, orig 0x00165DC0 /
 * 0x00165DE8 / 0x00165E10; task.h: TASKMGR +0x3B10 ptaskCur): set, and its oid kept in D_002DEB44 (-1: none). */
struct TASK {
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ int oid;
};
struct SW {
    /* 0x0000 */ char pad0[0x3b10];
    /* 0x3b10 */ struct TASK *ptaskCur;   /* field: SafeHouse port */
};
extern int D_002DEB44;   /* the current task's oid (SafeHouse g_taskmgr.oidTask) */

// name: SafeHouse port (SetTaskCur; the signature as SetJobCur__FP7TASKMGRP3JOB 0x165DC0)
void SetTaskCur__FP7TASKMGRP4TASK(struct SW *psw, struct TASK *p)
{
    psw->ptaskCur = p;
    if (p != 0) {
        D_002DEB44 = p->oid;
        return;
    }
    D_002DEB44 = -1;
}
