/* func_001A35F0 (0x1A35F0): sets the light's colour (LIGHT::hsv, EOPID 152 setter) and rebuilds the light. */
#include "light.h"

void func_001A35F0(LIGHT *plight, qword qw)
{
    plight->hsv = qw;
    ComputeLight__FP11LIGHTPARAMS(plight);
}
