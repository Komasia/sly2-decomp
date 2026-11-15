/* SetActorLookTarget: the actor's look target (its kind and object); a new object while the look timer runs
 * (+0x114C not FLT_MAX) turns the look on (+0x1148) and clears +0x1100 (0x142860). Layout: SafeHouse port (actor.h). */
#include "actor.h"
struct LO;
extern float D_002A4D60;   /* FLT_MAX */
void func_00142860(struct ACTOR *pactor);

// name: SafeHouse port (SetActorLookTarget)
void SetActorLookTarget__FP5ACTORiP2LO(struct ACTOR *pactor, int nKind, struct LO *plo)
{
    if (plo != pactor->ploLook || nKind != pactor->nLookKind) {
        pactor->nLookKind = nKind;
        pactor->ploLook = plo;
        if (plo != 0) {
            if (pactor->tLookNext != D_002A4D60) {
                pactor->fLook = 1;
                func_00142860(pactor);
            }
        }
    }
}
