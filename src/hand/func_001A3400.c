/* func_001A3400 (0x1A3400): LIGHT virtual slot 14 (Post*Load): LO post-load, then rebuild the light. */
#include "light.h"

void PostLoLoad__FP2LO(LO *plo);

void func_001A3400(LIGHT *plight)
{
    PostLoLoad__FP2LO(&plight->alo.lo);
    func_001A3968(plight);
}
