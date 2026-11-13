/* JOBNAVPOINT::Enter (AIJOB subclass method, AIJOB vt slot 8). */
#include "aijob.h"

struct JOBNAVPOINT {
    /* 0x00 */ AIJOB aijob;
};
void Enter__5AIJOB(AIJOB *pjob);
void Start(struct JOBNAVPOINT *pjob) asm("Start__11JOBNAVPOINT");

// name: SafeHouse port (JOBNAVPOINT::Enter)
void Enter__11JOBNAVPOINT(struct JOBNAVPOINT *pjob)
{
    Enter__5AIJOB(&pjob->aijob);
    Start(pjob);
}
