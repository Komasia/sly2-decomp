/* func_001B1F10 (0x1B1F10): MISSILE virtual slot 76: BOMB version (AttachStickyProjectile__FPvT0), then DeleteCtrl__FPP4CTRL on the
 * sub-object at MISSILE+0x268. */
#include "bomb.h"

void AttachStickyProjectile__FPvT0(MISSILE *pmissile);
void DeleteCtrl__FPP4CTRL(void *pv);

void func_001B1F10(MISSILE *pmissile)
{
    AttachStickyProjectile__FPvT0(pmissile);
    DeleteCtrl__FPP4CTRL(pmissile->unk_0x268);
}
