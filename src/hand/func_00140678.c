/* SetActorTargets: the actor's object faced (+0x10DC; a change stops the launch tracking first), +0x10E4, its target
 * (+0x10E8) and the target's kind (+0x10EC). Layout: SafeHouse port (actor.h). */
#include "actor.h"
void StopNearestLaunchTracking__FP5ACTOR(struct ACTOR *pactor, int n10E4, int ploFace, int n10EC, int plo10E8);
// name: SafeHouse port (SetActorTargets)
void SetActorTargets__FP5ACTORiiii(struct ACTOR *pactor, int n10E4, int ploFace, int n10EC, int plo10E8)
{
    if (ploFace != pactor->ploFace) StopNearestLaunchTracking__FP5ACTOR(pactor, n10E4, ploFace, n10EC, plo10E8);
    pactor->ploFace = ploFace;
    pactor->n10E4 = n10E4;
    pactor->ploTarget = plo10E8;
    pactor->nTargetKind = n10EC;
}
