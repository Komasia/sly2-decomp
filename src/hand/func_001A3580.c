/* func_001A3580 (0x1A3580): LIGHT virtual slot 29 (rotate to matrix): ALO version, then rebuild the light. */
#include "light.h"

void func_00231300(ALO *palo, struct MATRIX4 *pmat);

void func_001A3580(LIGHT *plight, struct MATRIX4 *pmat)
{
    func_00231300(&plight->alo, pmat);
    func_001A3968(plight);
}
