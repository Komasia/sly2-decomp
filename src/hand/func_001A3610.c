/* func_001A3610 (0x1A3610): sets the light's strength (LIGHT::strength, EOPID 153) and rebuilds the light. */
#include "light.h"

void func_001A3610(LIGHT *plight, float g)
{
    plight->strength = g;
    ComputeLight__FP11LIGHTPARAMS(plight);
}
