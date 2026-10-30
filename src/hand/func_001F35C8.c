/* func_001F35C8 (0x1F35C8): set the SO's mass and rescale its moment of inertia by the same ratio
 * (Sly 1 SetSoMass; func_001F35F8 = AdjustSoMomint). */
#include "so.h"

void func_001F35F8(SO *pso, float rMass);

void func_001F35C8(SO *pso, float m)
{
    SOPHYS *psophys = pso->psophys;
    float mOld = psophys->m;
    float rMass = m / mOld;

    psophys->m = mOld * rMass;
    func_001F35F8(pso, rMass);
}
