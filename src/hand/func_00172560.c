#include "clock.h"
extern float D_002BE5A0;
struct GUARD { char pad[0xE6C]; float dtGiveUpMin; float dtGiveUpMax; int pad2; int nSearchKind; };
struct JOBINVESTIGATE { char pad[0x10]; struct GUARD *pguard; char pad2[0x24]; float tEnd; float tSearch; };
float GRandInRange__Fff(float a, float b);
/* JOBINVESTIGATE::SetDeadlines: give up after a random time in the guard's range (+0xE6C..+0xE70); guards of kind 1
 * (+0xE78) start searching after D_002BE5A0, others never. */
// name: SafeHouse port (JOBINVESTIGATE::SetDeadlines)
void SetDeadlines__14JOBINVESTIGATE(struct JOBINVESTIGATE *pjob) {
    float t = g_clock.t;
    pjob->tEnd = t + GRandInRange__Fff(pjob->pguard->dtGiveUpMin, pjob->pguard->dtGiveUpMax);
    if (pjob->pguard->nSearchKind == 1) pjob->tSearch = g_clock.t + D_002BE5A0;
    else pjob->tSearch = 3.40282346638528859812e+38f;
}
