/* SetStepOverlap__FP3ALOT0 (0x204C60): STEP virtual slot 53: after the SO hook, forget the floor contact if it is with the
 * given SO. */
#include "step.h"

void SetAloOverlapNothing__FP3ALOT0(SO *pso);   /* SO slot 53 (empty) */

// name: SafeHouse port (SetStepOverlap)
void SetStepOverlap__FP3ALOT0(STEP *pstep, SO *pso)
{
    XP *pxp;

    SetAloOverlapNothing__FP3ALOT0(&pstep->po.so);
    pxp = pstep->pxpFloor;
    if (pxp != NULL && pxp->psoOther == pso)
        pstep->pxpFloor = NULL;
}
