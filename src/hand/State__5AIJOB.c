/* AIJOB::State (AIJOB vt slot 12, the base's): 7 unless the guard's +0x204 is set, then 0. */
#include "stepguard.h"
#include "aijob.h"


// name: SafeHouse port (AIJOB::State)
int State__5AIJOB(AIJOB *pjob)
{
    return pjob->pguard->step.fNoContacts ? 0 : 7;
}
