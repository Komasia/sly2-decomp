/* class: ACTOR (SafeHouse scpt.cpp, orig 0x1421A0: the reach interaction ended (kind 0), then the object held by the
 * interaction's reach +0x900, or the held one let go). */
#include "actor.h"
struct LO;
struct REACH;
void SetActorInteractObject__FP5ACTORi(struct ACTOR *pactor, int kind);
void AttachReachObject__FP5REACHP2LO(void *preach, struct LO *plo);
void ReleaseReachObject__FP5REACH(void *preach);

void func_001421A0(struct ACTOR *pactor, struct LO *plo)
{
    SetActorInteractObject__FP5ACTORi(pactor, 0);
    if (plo != 0) {
        AttachReachObject__FP5REACHP2LO(pactor->inter.reach, plo);
        return;
    }
    ReleaseReachObject__FP5REACH(pactor->inter.reach);
}
