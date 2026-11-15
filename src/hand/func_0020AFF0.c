/* func_0020AFF0 (0x20AFF0, splice method {oid}): the guard action's kind entry becomes a new KIND2 with the ASEG oid. */
#include "h6_guard.h"
typedef struct GUARD GUARD;
/* a guard action (cid 0x78): its guard and kind entry */
typedef struct GUARDACTION {
    /* 0x00 */ char pad0[0xac];
    /* 0xac */ GUARD *pguard;
    /* 0xb0 */ KINDE kinde;
} GUARDACTION;

void func_002090D0(KINDE *pkinde, GUARD *pguard);   /* clears a kind entry */
KIND2 *func_0020C010(int cb);   /* new KIND2 */
void func_0020BD78(KIND2 *pk2);  /* KIND2 init */
void func_0020AFF0(GUARDACTION *paction, int oid)
{
    KINDE *pkinde = &paction->kinde;
    func_002090D0(pkinde, paction->pguard);
    paction->kinde.k = KINDK_Kind2;
    pkinde->u.pk2 = func_0020C010(sizeof(KIND2));
    func_0020BD78(pkinde->u.pk2);
    pkinde->u.pk2->oid = oid;
    pkinde->grf = 0;
}
