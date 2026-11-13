/* RestartJobAtCheckpoint: restart the current checkpoint's task (D_003E0FA4), or the job's first task (+0x64). */
struct TASK;
struct JOB {
    /* 0x00 */ char pad0[0x64];
    /* 0x64 */ struct TASK *ptaskFirst;
};
extern struct TASK *D_003E0FA4;   /* the checkpoint's task */
void RestartTask(struct TASK *ptask) asm("RestartTask__FP4TASK");

// name: SafeHouse port (RestartJobAtCheckpoint)
void RestartJobAtCheckpoint__FP2SW(struct JOB *pjob)
{
    if (D_003E0FA4) {
        RestartTask(D_003E0FA4);
        return;
    }
    RestartTask(pjob->ptaskFirst);
}
