/* SetProjectileLauncher__FP3ALOP2LO (0x13BC60): change BOMB::psoOwner; on a change the bomb is re-registered with the world
 * (func_00134320). */
#include "bomb.h"

void func_00134320(void *psw, BOMB *pbomb);
extern char g_sw[];   /* the world (SW) */

// name: SafeHouse port (SetProjectileLauncher)
void SetProjectileLauncher__FP3ALOP2LO(BOMB *pbomb, SO *psoOwner)
{
    if (psoOwner != pbomb->psoOwner) {
        pbomb->psoOwner = psoOwner;
        func_00134320(g_sw, pbomb);
    }
}
