/* func_001A36D8 (0x1A36D8): set LIGHT::fUnk160 (clearing fUnk15c when set); see func_001A3680. */
#include "light.h"

void func_001A36D8(LIGHT *plight, int f)
{
    if (f != plight->fUnk160) {
        func_001A3B38(plight);
        plight->fUnk160 = f;
        if (f != 0)
            plight->fUnk15c = 0;
        func_001A3B38(plight);
    }
}
