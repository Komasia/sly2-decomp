/* JOBINVESTIGATE::Exit (AIJOB subclass method, AIJOB vt slot 9). */
#include "aijob.h"

struct GUARD;
struct JOBINVESTIGATE {
    /* 0x00 */ AIJOB aijob;
};
void Exit__5AIJOB(AIJOB *pjob);
void SetInvestigateState(struct JOBINVESTIGATE *pjob, int n) asm("SetInvestigateState__14JOBINVESTIGATEi");
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");
struct NOISE;
void SetNoise(struct JOBINVESTIGATE *pjob, struct NOISE *pnoise) asm("SetNoise__14JOBINVESTIGATEP5NOISE");

// name: SafeHouse port (JOBINVESTIGATE::Exit)
void Exit__14JOBINVESTIGATE(struct JOBINVESTIGATE *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    SetInvestigateState(pjob, -1);
    RemoveGuardState(pjob->aijob.pguard, 0x1F);
    SetNoise(pjob, 0);
}
