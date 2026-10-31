/* func_001A3580 (0x1A3580): LIGHT virtual slot 29 (rotate to matrix): XFM version, then rebuild the light. */
#include "light.h"

void func_00231300(XFM *pxfm, struct MATRIX4 *pmat);

void func_001A3580(LIGHT *plight, struct MATRIX4 *pmat)
{
    func_00231300(&plight->xfm, pmat);
    func_001A3968(plight);
}
