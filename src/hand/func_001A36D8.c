/* func_001A36D8 (0x1A36D8): sets LIGHT::fNoBake (not baked, EOPID 158) (clearing fNoContext when set); see func_001A3680. */
#include "light.h"

void func_001A36D8(LIGHT *plight, int f)
{
    if (f != plight->fNoBake) {
        func_001A3B38(plight);
        plight->fNoBake = f;
        if (f != 0)
            plight->fNoContext = 0;
        func_001A3B38(plight);
    }
}
