/* RenderStepSelf (0x203AD0): STEP virtual slot 18: just the SO rendering. */
#include "step.h"

void RenderSoSelf__FP2SOP2CMP2RO(SO *pso);

void RenderStepSelf__FP4STEPP2CMP2RO(STEP *pstep)
{
    RenderSoSelf__FP2SOP2CMP2RO(&pstep->po.so);
}
