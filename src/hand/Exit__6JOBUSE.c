/* JOBUSE::Exit (AIJOB subclass method, AIJOB vt slot 9). */
#include "aijob.h"

struct JOBUSE {
    /* 0x00 */ AIJOB aijob;
};
struct JOBMOVE;
void Exit__7JOBMOVE(struct JOBMOVE *pjob);
void UnlockJob(AIJOB *pjob) asm("UnlockJob__FP5AIJOB");

// name: SafeHouse port (JOBUSE::Exit)
void Exit__6JOBUSE(struct JOBUSE *pjob)
{
    Exit__7JOBMOVE((struct JOBMOVE *)pjob);
    UnlockJob(&pjob->aijob);
}
