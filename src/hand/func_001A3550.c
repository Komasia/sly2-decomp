/* func_001A3550 (0x1A3550): LIGHT virtual slot 28 (translate to position): XFM version, then rebuild the light. */
#include "light.h"

void func_002312A0(XFM *pxfm, qword pos);

void func_001A3550(LIGHT *plight, qword pos)
{
    func_002312A0(&plight->xfm, pos);
    func_001A3968(plight);
}
