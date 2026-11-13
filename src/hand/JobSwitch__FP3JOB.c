/* JobSwitch: a job becomes the current one: the current job (D_003E0F9C) ends (0x162908) and this one is activated
 * (0x1629A0). Source: SafeHouse port (task.cpp). */
struct JOB;
extern struct JOB *D_003E0F9C;   /* SafeHouse: the world's current job */
int FJobCur__FP3JOB(struct JOB *pjob);
void func_00162908(struct JOB *pjob);   /* SafeHouse: JobEndIfCur */
void func_001629A0(struct JOB *pjob);   /* SafeHouse: ActivateJob */

// name: SafeHouse port (JobSwitch)
void JobSwitch__FP3JOB(struct JOB *pjob)
{
    if (!FJobCur__FP3JOB(pjob)) {
        if (D_003E0F9C != 0)
            func_00162908(D_003E0F9C);
        func_001629A0(pjob);
    }
}
