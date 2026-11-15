/* func_001A15B0 (0x1A15B0): sets the damage controller's deferred action (DAMAGE +0x1C, a pointer to member function
 * run by EndDamageReaction at the reaction's end). */
#include "h5_damage.h"
void func_001A15B0(struct DAMAGE *pdmg, struct DAMAGEPMF pmf) { pdmg->pmfNext = pmf; }
