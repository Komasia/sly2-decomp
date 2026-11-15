/* NextStunned (0x1A1FA8): the end of a stun (reactions 1 / 2): with health left the actor recovers if the hit's sender
 * has grf148 bit 33, else jumps back (the jump's kind 11); out of health: reaction 8. SafeHouse damage.cpp. */
#include "h5_damage.h"
struct ALO { char pad[0x148]; unsigned long grf148; };
#define GRF148_RECOVER 0x200000000UL  /* bit 33 */
#define IB_JUMP 0x2C0                 /* ACTOR +0x2C0: the JUMP */
#define JUMPK_BACK 11
void NextRecover(struct DAMAGE *pdmg) asm("NextRecover__FP5ACTOR");
void SetJumpKind__FP4JUMPiiP2LO(void *pjump, int kind, int n, int plo);
void SetDamageState__FP5ACTORi(struct DAMAGE *pdmg, int nState);
// name: SafeHouse port (NextStunned)
void NextStunned__FP5ACTOR(struct DAMAGE *pdmg)
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
