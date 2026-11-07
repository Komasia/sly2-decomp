/* func_001B1F10 (0x1B1F10): MISSILE virtual slot 76: BOMB version (func_0013B250), then DeleteCtrl__FPP4CTRL on the
 * sub-object at MISSILE+0x268. */
#include "bomb.h"

void func_0013B250(MISSILE *pmissile);
void DeleteCtrl__FPP4CTRL(void *pv);

void func_001B1F10(MISSILE *pmissile)
{
    func_0013B250(pmissile);
    DeleteCtrl__FPP4CTRL(pmissile->unk_0x268);
}
