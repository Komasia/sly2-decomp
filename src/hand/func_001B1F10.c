/* func_001B1F10 (0x1B1F10): MISSILE virtual slot 76: BOMB version (func_0013B250), then func_0012E460 on the
 * sub-object at MISSILE+0x268. */
#include "bomb.h"

void func_0013B250(MISSILE *pmissile);
void func_0012E460(void *pv);

void func_001B1F10(MISSILE *pmissile)
{
    func_0013B250(pmissile);
    func_0012E460(pmissile->unk_0x268);
}
