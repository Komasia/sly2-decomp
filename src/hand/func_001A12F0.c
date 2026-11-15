/* UpdateDamageTransitions (0x1A12F0): Sly's state 4 transitions: while the reaction's clip (the actor's ASEGA,
 * ACTOR +0x1030) is retracted the reaction ends, repeated while each end starts a new reaction. SafeHouse damage.cpp. */
struct ACTOR { char pad[0x1030]; int pasega; };
struct DAMAGE { struct ACTOR *pactor; int nState; };
int FAsegaRetracted(int pasega) asm("FAsegaRetracted__FP5ASEGA");
void EndDamageReaction__FP5ACTOR(struct DAMAGE *pdmg);
// name: SafeHouse port (UpdateDamageTransitions)
void UpdateDamageTransitions__FP5ACTOR(struct DAMAGE *pdmg)
{
    int nState;
    do {
        nState = pdmg->nState;
        if (FAsegaRetracted(pdmg->pactor->pasega))
            EndDamageReaction__FP5ACTOR(pdmg);
    } while (pdmg->nState != -1 && pdmg->nState != nState);
}
