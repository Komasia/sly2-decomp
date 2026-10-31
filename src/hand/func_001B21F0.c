/* func_001B21F0 (0x1B21F0): class 82 (a MISSILE) virtual slot 6: missile init with MISSILE::sUnk274 = 1500. */
#include "bomb.h"

void InitMissile__FP7MISSILE(MISSILE *pmissile);

void func_001B21F0(MISSILE *pmissile)
{
    InitMissile__FP7MISSILE(pmissile);
    pmissile->sUnk274 = 1500.0f;
}
