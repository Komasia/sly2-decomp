/* func_001B2070 (0x1B2070): class 81 (a MISSILE) virtual slot 6: missile init with its own ranges. */
#include "bomb.h"

void InitMissile__FP7MISSILE(MISSILE *pmissile);

void func_001B2070(MISSILE *pmissile)
{
    InitMissile__FP7MISSILE(pmissile);
    pmissile->sUnk270 = 2000.0f;
    pmissile->sUnk274 = 5000.0f;
    pmissile->fUnk264 = 0;
}
