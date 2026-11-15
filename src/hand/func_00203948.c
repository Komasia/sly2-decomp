/* InitStep (0x203948): STEP vt slot 7: the PO init, then the defaults: no mesh oid, size and brake scale 1, speed
 * scale 1 (SetStepPhysScale), heading 0, support radius 30, the second floor probe 50 below the first; then the behaviour
 * stack (0x1EEC60). */
#include "step.h"

void InitPo__FP2PO(STEP *pstep);
void SetStepPhysScale__FP3ALOf(STEP *pstep, float g);
void SetStepPhysHeading__FP3ALOf(STEP *pstep, float rad);
void func_001EEC60(void *pbhvstk, STEP *pstep);   /* inits the behaviour stack */

void InitStep__FP4STEP(STEP *pstep)
{
    InitPo__FP2PO(pstep);
    pstep->oidMesh = -1;
    pstep->sSize = 1.0f;
    pstep->uBrake = 1.0f;
    SetStepPhysScale__FP3ALOf(pstep, 1.0f);
    SetStepPhysHeading__FP3ALOf(pstep, 0.0f);
    pstep->sSupport = 30.0f;
    pstep->sProbeDrop = -50.0f;
    func_001EEC60(pstep->bhvstk, pstep);
}
