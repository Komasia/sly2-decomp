/* func_001A3680 (0x1A3680): sets LIGHT::fNoContext (not a light-context candidate, EOPID 157) (clearing fNoBake when set), with func_001A3B38 run before and
 * after the change. func_001A36D8 is the mirror image for fNoBake. */
#include "light.h"

void func_001A3680(LIGHT *plight, int f)
{
    if (f != plight->fNoContext) {
        func_001A3B38(plight);
        plight->fNoContext = f;
        if (f != 0)
            plight->fNoBake = 0;
        func_001A3B38(plight);
    }
}
