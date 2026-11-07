/* func_001F4870 (0x1F4870): func_001F4848 for the second attachment transform (SO::pxfUnk5c). */
#include "so.h"

void VecConvertXfs__FP2XFT0G9VU_VECTOR(int n, XF *pxfRoot, qword qwPos);

void func_001F4870(SO *pso)
{
    XF *pxf = pso->pxfUnk5c;

    VecConvertXfs__FP2XFT0G9VU_VECTOR(pxf->nUnkA0, pso->pxfRoot, pxf->qwPosUnkB0);
}
