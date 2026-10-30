/* func_00231440 (0x231440): ALO virtual slot 30: the ALO's world matrix, brought up to date first
 * (func_00231368). */
#include "so.h"

void func_00231368(ALO *palo);

struct MATRIX4 *func_00231440(ALO *palo)
{
    func_00231368(palo);
    return &palo->matWorld;
}
