/* JobTaskReached: a task of a live job (0x162670) reached a done state: the job's first task begins the job, its
 * last completes it (0x162F10), and a task with a checkpoint (+0xB8) sets it (0x165E10). Source: SafeHouse port
 * (task.cpp). */
struct TASK {
    /* 0x00 */ char pad0[0xb8];
    /* 0xb8 */ int idChk;               /* field: SafeHouse port (-1 none) */
};
struct JOB {
    /* 0x00 */ char pad0[0x64];
    /* 0x64 */ struct TASK *ptaskFirst;  /* field: SafeHouse port */
    /* 0x68 */ struct TASK *ptaskLast;   /* field: SafeHouse port */
};
extern char g_sw[];
int func_00162670(struct JOB *pjob);   /* SafeHouse: FJobLive */
void JobBegin__FP3JOB(struct JOB *pjob);
void func_00162F10(struct JOB *pjob);   /* SafeHouse: JobComplete */
void SetTaskChk__FP7TASKMGRP4TASK(void *psw, struct TASK *ptask);

// name: SafeHouse port (JobTaskReached)
void JobTaskReached__FP3JOBP4TASK(struct JOB *pjob, struct TASK *ptask)
{
    if (func_00162670(pjob)) {
        if (ptask == pjob->ptaskFirst)
            JobBegin__FP3JOB(pjob);
        if (ptask == pjob->ptaskLast)
            func_00162F10(pjob);
        if (ptask->idChk != -1)
            SetTaskChk__FP7TASKMGRP4TASK(g_sw, ptask);
    }
}
