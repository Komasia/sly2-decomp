/* func_001F5040 (0x1F5040): is the SO fixed in place? True when it has no physics state, or when both its
 * force and its torque constraint are locked (kind 3). */
#include "so.h"

int func_001F5040(SO *pso)
{
    SOPHYS *psophys = pso->psophys;
    int fLocked = 0;

    if (psophys == NULL || (psophys->nKindForce == 3 && psophys->nKindTorque == psophys->nKindForce))
        fLocked = 1;
    return fLocked;
}
