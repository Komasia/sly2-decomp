/* CopyRopeDistances: a rope's rest distances copied from its path's distances. Layout: h3_rope.h ROPE, crv.h CRV. */
#include "h3_rope.h"

void CopyAb(void *pvDst, void *pvSrc, unsigned int cb) asm("CopyAb__FPvT0Ui");

// name: SafeHouse port (CopyRopeDistances)
void CopyRopeDistances__FP4ROPE(ROPE *prope)
{
    CopyAb(prope->as5C, prope->ppath->as, prope->ppath->cpoint * sizeof(float));
}
