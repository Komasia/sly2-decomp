/* func_002041F8 (0x2041F8): STEP virtual slot 29 (rotate to matrix): SO version, then re-derive the target
 * heading (func_00204740 -> func_00204660) and hand it to the controller (POCTL::radLeft). */
#include "step.h"

void SetAloRotation__FP3ALOP7MATRIX3(SO *pso, struct MATRIX4 *pmat);   /* SO slot 29 */
float func_00204740(STEP *pstep);
void func_00204660(STEP *pstep, float rad);

void func_002041F8(STEP *pstep, struct MATRIX4 *pmat)
{
    POCTL *pctl;

    SetAloRotation__FP3ALOP7MATRIX3(&pstep->po.so, pmat);
    func_00204660(pstep, func_00204740(pstep));
    pctl = pstep->po.pctl;
    if (pctl != NULL)
        pctl->radLeft = pstep->radTarget;
}
