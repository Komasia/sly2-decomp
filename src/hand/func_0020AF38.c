/* func_0020AF38 (0x20AF38, splice method 0x104408 {oid, grf}): the guard action's kind entry cleared (0x2090D0), then
 * given an object oid and ApplyAseg flags - not resolved (see 0x20AF88). */
#include "h6_guard.h"
typedef struct GUARD GUARD;
/* a guard action (cid 0x78): its guard and kind entry */
typedef struct GUARDACTION {
    /* 0x00 */ char pad0[0xac];
    /* 0xac */ GUARD *pguard;
    /* 0xb0 */ KINDE kinde;
} GUARDACTION;

void func_002090D0(KINDE *pkinde, GUARD *pguard);   /* clears a kind entry */

void func_0020AF38(GUARDACTION *paction, int oid, int grf)
{
    func_002090D0(&paction->kinde, paction->pguard);
    paction->kinde.u.oid = oid;
    paction->kinde.grf = grf;
}
