/* FJobCur: whether a job is the current one (the task manager's current job, D_003E0F9C). */
struct JOB;
extern struct JOB *D_003E0F9C;   /* the current job */

// name: SafeHouse port (FJobCur)
int FJobCur__FP3JOB(struct JOB *pjob)
{
    return D_003E0F9C == pjob;
}
