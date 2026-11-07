/* func_001A3550 (0x1A3550): LIGHT virtual slot 28 (translate to position): XFM version, then rebuild the light. */
#include "light.h"

void SetLoxPos(XFM *pxfm, qword pos);

void func_001A3550(LIGHT *plight, qword pos)
{
    SetLoxPos(&plight->xfm, pos);
    ComputeLight__FP11LIGHTPARAMS(plight);
}
