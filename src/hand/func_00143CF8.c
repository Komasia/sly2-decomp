/* class: ACTOR (JT / MURRAY / BENTLEY vt slot 29, SetPos; SafeHouse actor.cpp SetActorPosVt): the step's position,
 * then the safe ground's count cleared. */
typedef int qword __attribute__((mode(TI)));
struct ACTOR {
    /* 0x000 */ char pad0[0x9e4];
    /* 0x9e4 */ int cSafeGround;   /* field: SafeHouse port */
};
void SetStepPos__FP4STEPG9VU_VECTOR(struct ACTOR *pstep, qword pos);

void func_00143CF8(struct ACTOR *pactor, qword pos)
{
    SetStepPos__FP4STEPG9VU_VECTOR(pactor, pos);
    pactor->cSafeGround = 0;
}
