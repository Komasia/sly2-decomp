/* func_0020B060 (0x20B060, the live splice method 0x104638): 0x20AFF0, then the entry resolved (ResolveKinde). */
#include "h6_guard.h"
typedef struct GUARD GUARD;
/* a guard action (cid 0x78): its guard and kind entry */
typedef struct GUARDACTION {
    /* 0x00 */ char pad0[0xac];
    /* 0xac */ GUARD *pguard;
    /* 0xb0 */ KINDE kinde;
} GUARDACTION;

void func_0020AFF0(GUARDACTION *paction, int oid);
void ResolveKinde__FP5KINDEP5GUARD(KINDE *pkinde, GUARD *pguard);

void func_0020B060(GUARDACTION *paction, int oid)
{
    func_0020AFF0(paction, oid);
    ResolveKinde__FP5KINDEP5GUARD(&paction->kinde, paction->pguard);
}
