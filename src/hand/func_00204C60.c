/* func_00204C60 (0x204C60): STEP virtual slot 53: after the SO hook, forget the floor contact if it is with the
 * given SO. */
#include "step.h"

void func_001F5988(SO *pso);   /* SO slot 53 (empty) */

void func_00204C60(STEP *pstep, SO *pso)
{
    XP *pxp;

    func_001F5988(&pstep->po.so);
    pxp = pstep->pxpFloor;
    if (pxp != NULL && pxp->psoOther == pso)
        pstep->pxpFloor = NULL;
}
