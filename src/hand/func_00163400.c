/* class: JOB (SafeHouse task.cpp: the job's option 1251 - its last task done). */
struct TASK;
struct JOB {
    /* 0x00 */ char pad0[0x68];
    /* 0x68 */ struct TASK *ptaskLast;   /* field: SafeHouse port */
};
int FTaskDone__FP4TASK(struct TASK *ptask);

int func_00163400(struct JOB *pjob)
{
    struct TASK *ptask = pjob->ptaskLast;
    int fDone = 0;
    if (ptask != 0) {
        fDone = FTaskDone__FP4TASK(ptask) != 0;
    }
    return fDone;
}
