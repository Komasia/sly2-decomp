/* func_001A3630 (0x1A3630): sets the light's angle in degrees (LIGHT::angle, EOPID 154) and rebuilds the light. */
#include "light.h"

void func_001A3630(LIGHT *plight, float g)
{
    plight->angle = g;
    ComputeLight__FP11LIGHTPARAMS(plight);
}
