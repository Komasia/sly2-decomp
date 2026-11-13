/* class: JOB (SafeHouse task.cpp, orig 0x00162F60 / 0x00162FD0 / 0x00162F10: the job complete - its sequence 1 when
 * +0xB8 is set, else closed and the next one). */
struct JOB {
    /* 0x00 */ char pad0[0xb8];
    /* 0xb8 */ int fSeq;
};
void SetJobSeq__FP3JOBi(struct JOB *pjob, int n);
void JobCompleteClose__FP3JOB(struct JOB *pjob, int n);
void JobCompleteNext__FP3JOB(struct JOB *pjob);

void func_00162F10(struct JOB *pjob, int n)
{
    if (pjob->fSeq != 0) {
        SetJobSeq__FP3JOBi(pjob, 1);
        return;
    }
    JobCompleteClose__FP3JOB(pjob, n);
    JobCompleteNext__FP3JOB(pjob);
}
