/* func_001F57C0 (0x1F57C0): func_001F5720 for the torque constraint (SOPHYS::vecNormalTorque) and the second
 * attachment transform (SO::pxfUnk5c). */
#include "so.h"

void func_002303A0(SO *pso, XF *pxf, int n);
void func_001F5510(SO *pso, XF *pxf, int n, qword *pqwNormal);
void func_001F55C8(SO *pso);
void func_001F8668(SO *pso, int n);

void func_001F57C0(SO *pso, int n)
{
    XF *pxf;

    if (pso->psophys != NULL) {
        pxf = pso->pxfUnk5c;
        if (pxf->nUnk90 == 0 && pxf->nKindUnk98 != 2)
            func_002303A0(pso, pxf, 1);
        func_001F5510(pso, pxf, n, &pso->psophys->vecNormalTorque);
        func_001F55C8(pso);
        if (pso->psophys->nKindTorque != 3)
            func_001F8668(pso, 0);
    }
}
