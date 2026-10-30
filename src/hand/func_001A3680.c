/* func_001A3680 (0x1A3680): set LIGHT::fUnk15c (clearing fUnk160 when set), with func_001A3B38 run before and
 * after the change. func_001A36D8 is the mirror image for fUnk160. */
#include "light.h"

void func_001A3680(LIGHT *plight, int f)
{
    if (f != plight->fUnk15c) {
        func_001A3B38(plight);
        plight->fUnk15c = f;
        if (f != 0)
            plight->fUnk160 = 0;
        func_001A3B38(plight);
    }
}
