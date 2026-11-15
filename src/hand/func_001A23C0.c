/* NDamageStatus (0x1A23C0): 0 free, 1 reacting (or flashing after a hit), 2 reacting with the health counter out.
 * SafeHouse damage.cpp. */
#include "h5_damage.h"
// name: SafeHouse port (NDamageStatus)
int NDamageStatus__FP5ACTOR(struct DAMAGE *pdmg)
{
    if (pdmg->nState != -1) return *pdmg->pcount <= 0 ? 2 : 1;
    return pdmg->nFlash == 1;
}
