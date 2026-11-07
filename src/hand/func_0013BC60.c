/* SetProjectileLauncher__FP3ALOP2LO (0x13BC60): change BOMB::psoOwner; on a change the bomb is re-registered with the world
 * (RecalcSwOxfFilterForObject__FP2SWP2SO). */
#include "bomb.h"

void RecalcSwOxfFilterForObject__FP2SWP2SO(void *psw, BOMB *pbomb);
extern char g_sw[];   /* the world (SW) */

// name: SafeHouse port (SetProjectileLauncher)
void SetProjectileLauncher__FP3ALOP2LO(BOMB *pbomb, SO *psoOwner)
{
    if (psoOwner != pbomb->psoOwner) {
        pbomb->psoOwner = psoOwner;
        RecalcSwOxfFilterForObject__FP2SWP2SO(g_sw, pbomb);
    }
}
