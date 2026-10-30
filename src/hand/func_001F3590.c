/* func_001F3590 (0x1F3590): reset an SO's physics defaults: gravity (0, 0, -1750) and constraint kind 3 for
 * both the force and the torque constraint. */
#include "so.h"

SOPHYS *func_001F3590(SO *pso)
{
    SOPHYS *psophys;
    float *pdvGravity = pso->psophys->dvGravity;

    pdvGravity[0] = 0;
    pdvGravity[2] = -1750.0f;
    pdvGravity[1] = 0;
    pso->psophys->nKindForce = 3;
    psophys = pso->psophys;
    psophys->nKindTorque = 3;
    return psophys;
}
