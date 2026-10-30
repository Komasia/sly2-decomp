/* SetSoMass__FP2SOf (0x1F35C8): set the SO's mass and rescale its moment of inertia by the same ratio
 * (Sly 1 SetSoMass; AdjustSoMomint__FP2SOf = AdjustSoMomint). */
#include "so.h"

void AdjustSoMomint__FP2SOf(SO *pso, float rMass);

void SetSoMass__FP2SOf(SO *pso, float m)
{
    SOPHYS *psophys = pso->psophys;
    float mOld = psophys->m;
    float rMass = m / mOld;

    psophys->m = mOld * rMass;
    AdjustSoMomint__FP2SOf(pso, rMass);
}
