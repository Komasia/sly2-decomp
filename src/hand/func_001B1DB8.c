/* InitMissile (0x1B1DB8): MISSILE virtual slot 6: BOMB init, then the missile defaults. */
#include "bomb.h"

void InitBomb__FP4BOMB(BOMB *pbomb);

void InitMissile__FP7MISSILE(MISSILE *pmissile)
{
    InitBomb__FP4BOMB(&pmissile->bomb);
    pmissile->fUnk264 = 1;
    pmissile->sUnk260 = 800.0f;
    pmissile->gUnk26c = 1.0f;
}
