/* OnLightRemove__FP5LIGHT (0x1A34B0): LIGHT virtual slot 11 (On*Remove): LO remove, then func_001A3B38. */
#include "light.h"

void OnLoRemove__FP2LO(LO *plo);

void OnLightRemove__FP5LIGHT(LIGHT *plight)
{
    OnLoRemove__FP2LO(&plight->xfm.lo);
    func_001A3B38(plight);
}
