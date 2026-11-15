/* NextSpecial (0x1A2028): the burn's end: starts the plain sound 0x6A without a source, reaction 6, then defers
 * func_001A2080 (the PMF D_002A6790). SafeHouse damage.cpp. */
#include "h5_damage.h"
#define SFX_BURN_END 0x6A
extern struct DAMAGEPMF g_pmfNextAfterSpecial __asm__("D_002A6790");  /* -> func_001A2080 */
void *PsndNewPlain__Fi(int sfx);
void SetSource__4CSndPv(void *psnd, int pv);
void SetDamageState__FP5ACTORi(void *pdmg, int nState);
void func_001A15B0(void *pdmg, struct DAMAGEPMF pmf);
// name: SafeHouse port (NextSpecial)
void NextSpecial__FP5ACTOR(void *pdmg)
{
    SetSource__4CSndPv(PsndNewPlain__Fi(SFX_BURN_END), 0);
    SetDamageState__FP5ACTORi(pdmg, 6);
    func_001A15B0(pdmg, g_pmfNextAfterSpecial);
}
