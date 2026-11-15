/* EndDamageReaction (0x1A15D0): the end of a damage reaction: runs the deferred action (DAMAGE +0x1C) if one is set
 * (and clears it); else in the deadly reactions 8..12 the actor's vtable slot 93; else the actor recovers if the hit's
 * sender has grf148 bit 33, or jumps back (the jump's kind 11). SafeHouse damage.cpp. */
#include "vtbl.h"
#include "h5_damage.h"
struct O { int x0, x4, x8; VTENT *vt; };
struct ALO { char pad[0x148]; unsigned long grf148; };
#define GRF148_RECOVER 0x200000000UL  /* bit 33 */
#define IB_JUMP 0x2C0                 /* ACTOR +0x2C0: the JUMP */
#define JUMPK_BACK 11
#define VT_DAMAGE_DEATH (0x2E8 / 8)   /* slot 93 */
void *s1_memset(void *p, int c, unsigned int n) asm("memset");
void NextRecover(struct DAMAGE *pdmg) asm("NextRecover__FP5ACTOR");
void SetJumpKind__FP4JUMPiiP2LO(void *pjump, int kind, int n, int plo);
// name: SafeHouse port (EndDamageReaction)
void EndDamageReaction__FP5ACTOR(struct DAMAGE *pdmg)
{
    struct DAMAGEPMF pmf = pdmg->pmfNext;
    s1_memset(&pdmg->pmfNext, 0, sizeof(pdmg->pmfNext));
    if (pmf.idx) {
        pmf.pfn((char *)pdmg + pmf.delta);
    } else if ((unsigned int)(pdmg->nState - 8) < 5) {
        struct O *pactor = (struct O *)pdmg->pactor;
        VTENT *e = &pactor->vt[VT_DAMAGE_DEATH];
        ((void (*)(void *))e->pfn)(VT_THIS(pactor, e));
    } else if (pdmg->msg.ploSender && (((struct ALO *)pdmg->msg.ploSender)->grf148 & GRF148_RECOVER)) {
        NextRecover(pdmg);
    } else {
        SetJumpKind__FP4JUMPiiP2LO((char *)pdmg->pactor + IB_JUMP, JUMPK_BACK, 0, 0);
    }
}
