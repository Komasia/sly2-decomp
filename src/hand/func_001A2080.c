/* func_001A2080 (0x1A2080): the deferred action after the burn's end (the PMF D_002A6790): the same as NextStunned.
 * SafeHouse damage.cpp NextAfterSpecial. */
#include "h5_damage.h"
struct ALO { char pad[0x148]; unsigned long grf148; };
#define GRF148_RECOVER 0x200000000UL  /* bit 33 */
#define IB_JUMP 0x2C0                 /* ACTOR +0x2C0: the JUMP */
#define JUMPK_BACK 11
void NextRecover(struct DAMAGE *pdmg) asm("NextRecover__FP5ACTOR");
void SetJumpKind__FP4JUMPiiP2LO(void *pjump, int kind, int n, int plo);
void SetDamageState__FP5ACTORi(struct DAMAGE *pdmg, int nState);
void func_001A2080(struct DAMAGE *pdmg)
{
    if (*pdmg->pcount > 0) {
        struct ALO *paloSender = (struct ALO *)pdmg->msg.ploSender;
        if (paloSender && (paloSender->grf148 & GRF148_RECOVER))
            NextRecover(pdmg);
        else
            SetJumpKind__FP4JUMPiiP2LO((char *)pdmg->pactor + IB_JUMP, JUMPK_BACK, 0, 0);
    } else {
        SetDamageState__FP5ACTORi(pdmg, 8);
    }
}
