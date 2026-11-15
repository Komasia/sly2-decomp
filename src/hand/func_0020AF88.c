/* func_0020AF88 (0x20AF88, the live splice method 0x1044B0): as 0x20AF38, then the entry resolved (ResolveKinde). */
#include "h6_guard.h"
typedef struct GUARD GUARD;
/* a guard action (cid 0x78): its guard and kind entry */
typedef struct GUARDACTION {
    /* 0x00 */ char pad0[0xac];
    /* 0xac */ GUARD *pguard;
    /* 0xb0 */ KINDE kinde;
} GUARDACTION;

void func_002090D0(KINDE *pkinde, GUARD *pguard);   /* clears a kind entry */
void ResolveKinde__FP5KINDEP5GUARD(KINDE *pkinde, GUARD *pguard);

void func_0020AF88(GUARDACTION *paction, int oid, int grf)
{
    KINDE *pkinde = &paction->kinde;

    func_002090D0(pkinde, paction->pguard);
    paction->kinde.u.oid = oid;
    paction->kinde.grf = grf;
    ResolveKinde__FP5KINDEP5GUARD(pkinde, paction->pguard);
}
