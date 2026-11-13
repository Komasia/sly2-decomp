/* JOBSTATION::Enter (AIJOB subclass method, AIJOB vt slot 8). */
#include "aijob.h"

struct JOBSTATION {
    /* 0x00 */ AIJOB aijob;
};
void Enter__5AIJOB(AIJOB *pjob);
void SetState(struct JOBSTATION *pjob, int n) asm("SetState__10JOBSTATIONi");

// name: SafeHouse port (JOBSTATION::Enter)
void Enter__10JOBSTATION(struct JOBSTATION *pjob)
{
    Enter__5AIJOB(&pjob->aijob);
    SetState(pjob, 0);
}
