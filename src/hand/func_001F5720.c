/* func_001F5720 (0x1F5720): re-apply the force constraint (SOPHYS::vecNormalForce) from the first attachment
 * transform (SO::pxfUnk58); func_001F57C0 is the torque twin using SO::pxfUnk5c. Unless the force constraint is
 * locked, func_001F8668(pso, 0) runs afterwards. */
#include "so.h"

void func_002303A0(SO *pso, XF *pxf, int n);
void func_001F5510(SO *pso, XF *pxf, int n, qword *pqwNormal);
void func_001F55C8(SO *pso);
void func_001F8668(SO *pso, int n);

void func_001F5720(SO *pso, int n)
{
    XF *pxf;

    if (pso->psophys != NULL) {
        pxf = pso->pxfUnk58;
        if (pxf->nUnk90 == 0 && pxf->nKindUnk98 != 2)
            func_002303A0(pso, pxf, 1);
        func_001F5510(pso, pxf, n, &pso->psophys->vecNormalForce);
        func_001F55C8(pso);
        if (pso->psophys->nKindForce != 3)
            func_001F8668(pso, 0);
    }
}
