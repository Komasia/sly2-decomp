/* func_001A2358 (0x1A2358): whether a hit is fatal for the damage controller's actor: its vtable slot 86 with the
 * contact message (SafeHouse damage.cpp FDamageFatal). */
#include "actor.h"
struct DAMAGE { struct ACTOR *pactor; };
#define VT_DAMAGE_FATAL 86
int func_001A2358(struct DAMAGE *pdmg, int pctm) { struct ACTOR *pactor = pdmg->pactor; VTENT *e = &pactor->so.lo.pvt[VT_DAMAGE_FATAL]; return ((int (*)(void *, int))e->pfn)(VT_THIS(pactor, e), pctm); }
