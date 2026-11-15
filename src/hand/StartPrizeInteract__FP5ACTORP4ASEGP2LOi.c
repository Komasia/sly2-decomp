/* StartPrizeInteract: an actor holds up a prize (interaction kind 12) with the given clip, else the interaction's
 * default one. Layout: SafeHouse port (interact.h INTERACT at ACTOR +0x4C0). */
#include "actor.h"
struct ASEG;
struct LO;
void StartInteract(struct INTERACT *pinter, int n, struct LO *plo, int jtl) asm("StartInteract__FP5ACTORii3JTL");

// name: SafeHouse port (StartPrizeInteract)
void StartPrizeInteract__FP5ACTORP4ASEGP2LOi(struct ACTOR *pactor, struct ASEG *paseg, struct LO *ploPrize, int n)
{
    if (paseg == 0)
        paseg = pactor->inter.paseg508;
    pactor->inter.paseg50C = paseg;
    StartInteract(&pactor->inter, 12, ploPrize, 0);
    pactor->n1318 = n;
}
