/* func_001A3610 (0x1A3610): set LIGHT::gUnk150 and rebuild the light. */
#include "light.h"

void func_001A3610(LIGHT *plight, float g)
{
    plight->gUnk150 = g;
    func_001A3968(plight);
}
