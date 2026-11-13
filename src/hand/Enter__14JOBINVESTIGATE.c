/* JOBINVESTIGATE::Enter (AIJOB vt slot 8): the base enter, then the investigation's state 0. Layout: SafeHouse port (ainoise.cpp). */
#include "aijob.h"

struct JOBINVESTIGATE {
    /* 0x00 */ AIJOB aijob;
};
void Enter__5AIJOB(AIJOB *pjob);
void SetInvestigateState__14JOBINVESTIGATEi(struct JOBINVESTIGATE *pjob, int st);

// name: SafeHouse port (JOBINVESTIGATE::Enter)
void Enter__14JOBINVESTIGATE(struct JOBINVESTIGATE *pjob)
{
    Enter__5AIJOB(&pjob->aijob);
    SetInvestigateState__14JOBINVESTIGATEi(pjob, 0);
}
