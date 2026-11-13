/* class: JOB (SafeHouse task.cpp, orig 0x00162A60 / 0x00162908: the current job ends). */
struct JOB;
int FJobCur__FP3JOB(struct JOB *pjob);
void DeactivateJob__FP3JOB(struct JOB *pjob);

void func_00162908(struct JOB *pjob)
{
    if (FJobCur__FP3JOB(pjob) != 0) {
        DeactivateJob__FP3JOB(pjob);
    }
}
