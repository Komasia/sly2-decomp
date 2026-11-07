/* func_001F4848 (0x1F4848): pass the first attachment transform (SO::pxfUnk58) to VecConvertXfs__FP2XFT0G9VU_VECTOR together with the
 * root transform. func_001F4870 is the same for SO::pxfUnk5c. */
#include "so.h"

void VecConvertXfs__FP2XFT0G9VU_VECTOR(int n, XF *pxfRoot, qword qwPos);

void func_001F4848(SO *pso)
{
    XF *pxf = pso->pxfUnk58;

    VecConvertXfs__FP2XFT0G9VU_VECTOR(pxf->nUnkA0, pso->pxfRoot, pxf->qwPosUnkB0);
}
