/* class: ACTOR (vtable 0x2CBE68 entry 100, the actor's ability start; StartBentleyAbility / StartMurrayAbility fall
 * back to it - SafeHouse gang.cpp "else 0x141D38"): abilities 14 / 21 / 23 start the interaction kind 11 (the
 * ability id kept at +0x9BC); 12 spends its power (0x141CD0) and starts the jump kind 17; others nothing. */
#include "actor.h"

void StartInteract__FP5ACTORii3JTL(INTERACT *pinter, int kind, void *plo, int jtl);
void SetJumpKind__FP4JUMPiiP2LO(JUMP *pjump, int kind, int n, void *plo);
void SpendActorPower__FP5ACTORi(ACTOR *pactor, int kAbility);   /* spend the ability's power (SafeHouse SpendActorPower) */

void func_00141D38(ACTOR *pactor, int kAbility)
{
    switch (kAbility) {
    case 14:
    case 21:
    case 23:
        pactor->inter.kAbility = kAbility;
        StartInteract__FP5ACTORii3JTL(&pactor->inter, 11, 0, 0);
        break;
    case 12:
        SpendActorPower__FP5ACTORi(pactor, 12);
        SetJumpKind__FP4JUMPiiP2LO(&pactor->jump, 17, 0, 0);
        break;
    }
}
