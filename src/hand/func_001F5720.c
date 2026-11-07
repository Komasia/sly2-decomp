/* SetAloCnstrLin__FP3ALOi (0x1F5720): re-apply the force constraint (SOPHYS::vecNormalForce) from the first attachment
 * transform (SO::pxfUnk58); SetAloCnstrAng__FP3ALOi is the torque twin using SO::pxfUnk5c. Unless the force constraint is
 * locked, SetAloIced__FP3ALOl(pso, 0) runs afterwards. */
#include "so.h"

void SetXfMode__FP3ALOP2XFi(SO *pso, XF *pxf, int n);
void SetCnstrAxis__FP2XFP6CNSTRSiP3OUT(SO *pso, XF *pxf, int n, qword *pqwNormal);
void ReRootAlo__FP3ALO(SO *pso);
void SetAloIced__FP3ALOl(SO *pso, int n);

// name: SafeHouse port (SetAloCnstrLin)
void SetAloCnstrLin__FP3ALOi(SO *pso, int n)
{
    XF *pxf;

    if (pso->psophys != NULL) {
        pxf = pso->pxfUnk58;
        if (pxf->nUnk90 == 0 && pxf->nKindUnk98 != 2)
            SetXfMode__FP3ALOP2XFi(pso, pxf, 1);
        SetCnstrAxis__FP2XFP6CNSTRSiP3OUT(pso, pxf, n, &pso->psophys->vecNormalForce);
        ReRootAlo__FP3ALO(pso);
        if (pso->psophys->nKindForce != 3)
            SetAloIced__FP3ALOl(pso, 0);
    }
}
