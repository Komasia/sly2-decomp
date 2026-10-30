/* func_001A3430 (0x1A3430): LIGHT virtual slot 10 (On*Add): LO add, then rebuild the light (Sly 1 OnLightAdd
 * adds the light to the world's light list at this point). */
#include "light.h"

void OnLoAdd__FP2LO(LO *plo);

void func_001A3430(LIGHT *plight)
{
    OnLoAdd__FP2LO(&plight->alo.lo);
    func_001A3968(plight);
}
