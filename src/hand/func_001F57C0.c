/* SetAloCnstrAng__FP3ALOi (0x1F57C0): SetAloCnstrLin__FP3ALOi for the torque constraint (SOPHYS::vecNormalTorque) and the second
 * attachment transform (SO::pxfUnk5c). */
#include "so.h"

void SetXfMode__FP3ALOP2XFi(SO *pso, XF *pxf, int n);
void SetCnstrAxis__FP2XFP6CNSTRSiP3OUT(SO *pso, XF *pxf, int n, qword *pqwNormal);
void ReRootAlo__FP3ALO(SO *pso);
void SetAloIced__FP3ALOl(SO *pso, int n);

// name: SafeHouse port (SetAloCnstrAng)
void SetAloCnstrAng__FP3ALOi(SO *pso, int n)
{
    XF *pxf;

    if (pso->psophys != NULL) {
        pxf = pso->pxfUnk5c;
        if (pxf->nUnk90 == 0 && pxf->nKindUnk98 != 2)
            SetXfMode__FP3ALOP2XFi(pso, pxf, 1);
        SetCnstrAxis__FP2XFP6CNSTRSiP3OUT(pso, pxf, n, &pso->psophys->vecNormalTorque);
        ReRootAlo__FP3ALO(pso);
        if (pso->psophys->nKindTorque != 3)
            SetAloIced__FP3ALOl(pso, 0);
    }
}
