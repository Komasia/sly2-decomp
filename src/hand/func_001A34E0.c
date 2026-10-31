/* func_001A34E0 (0x1A34E0): LIGHT virtual slot 21: LO slot 21, then func_001A3E88(world, plight). */
#include "light.h"

void func_001A6150(LO *plo);
void func_001A3E88(void *psw, LIGHT *plight);
extern char D_003DD490[];   /* the world (SW) */

void func_001A34E0(LIGHT *plight)
{
    func_001A6150(&plight->xfm.lo);
    func_001A3E88(D_003DD490, plight);
}
