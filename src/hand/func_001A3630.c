/* func_001A3630 (0x1A3630): set LIGHT::gUnk154 and rebuild the light. */
#include "light.h"

void func_001A3630(LIGHT *plight, float g)
{
    plight->gUnk154 = g;
    func_001A3968(plight);
}
