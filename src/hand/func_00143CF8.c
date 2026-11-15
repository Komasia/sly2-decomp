/* class: ACTOR (JT / MURRAY / BENTLEY vt slot 29, SetPos; SafeHouse actor.cpp SetActorPosVt): the step's position,
 * then the safe ground's count cleared. */
#include "actor.h"
void SetStepPos__FP4STEPG9VU_VECTOR(struct ACTOR *pstep, qword pos);

void func_00143CF8(struct ACTOR *pactor, qword pos)
{
    SetStepPos__FP4STEPG9VU_VECTOR(pactor, pos);
    pactor->cSafeGround = 0;
}
