/* JOBLINK (SafeHouse aijobs.cpp 0x17E5F0): whether the guard is near (25) the current record. */
#include "h2_aijobs.h"

int FNearRecord__FP4GOALP5GUARDf(GOAL *pgoal, struct GUARD *pguard, float dist);

int func_0017E5F0(JOBLINK *pjob)
{
    return FNearRecord__FP4GOALP5GUARDf(&pjob->plink->agoal[pjob->irec], pjob->aijob.pguard, 25.0f);
}
