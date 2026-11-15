/* NextGetUp (a damage state's next step): with health left (*DAMAGE +0x10) the actor gets up (damage state 0), else
 * state 8. Source: SafeHouse port (damage.cpp). */
#include "h5_damage.h"
void SetDamageState__FP5ACTORi(struct DAMAGE *pdmg, int nState);

// name: SafeHouse port (NextGetUp, damage.cpp)
void NextGetUp__FP5ACTOR(struct DAMAGE *pdmg)
{
    if (*pdmg->pcount > 0) {
        SetDamageState__FP5ACTORi(pdmg, 0);
        return;
    }
    SetDamageState__FP5ACTORi(pdmg, 8);
}
