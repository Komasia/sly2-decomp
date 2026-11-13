/* JOBB1::Exit (AIJOB subclass method, AIJOB vt slot 9). */
#include "aijob.h"

struct JOBB1 {
    /* 0x00 */ AIJOB aijob;
};
void SetState(struct JOBB1 *pjob, int n) asm("SetState__5JOBB1i");
struct JOBMOVE;
void Exit__7JOBMOVE(struct JOBMOVE *pjob);

// name: SafeHouse port (JOBB1::Exit)
void Exit__5JOBB1(struct JOBB1 *pjob)
{
    SetState(pjob, -1);
    Exit__7JOBMOVE((struct JOBMOVE *)pjob);
}
