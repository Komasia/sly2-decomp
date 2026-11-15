/* UpdatePath17: a path's update (vt slot 17): its rope simulation's step by the rope's mode (the spring for
 * ROPEK_Spring / ROPEK_SpringResample, the trail for the two trail modes), else the base update (0x1A5E80).
 * Layout: crv.h CRV, h3_rope.h ROPE. */
#include "h3_rope.h"

void StepRopeSpring__FP4ROPE(ROPE *prope);
void StepRopeTrail__FP4ROPE(ROPE *prope);
void func_001A5E80(CRV *pcrv);

// name: SafeHouse port (UpdatePath17)
void UpdatePath17__FP2LO(CRV *pcrv)
{
    if (pcrv->prope) {
        switch (pcrv->prope->mode) {
        case ROPEK_Spring:
        case ROPEK_SpringResample:
            StepRopeSpring__FP4ROPE(pcrv->prope);
            break;
        case ROPEK_Trail:
        case ROPEK_TrailPinned:
            StepRopeTrail__FP4ROPE(pcrv->prope);
            break;
        }
    } else {
        func_001A5E80(pcrv);
    }
}
