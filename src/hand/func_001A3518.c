/* func_001A3518 (0x1A3518): LIGHT virtual slot 22: unregister from the world (LO slot 22), then take the light out
 * of the world's lights (func_001A3D00). */
#include "light.h"

void func_001A6178(LO *plo);
void func_001A3D00(void *psw, LIGHT *plight);
extern char D_003DD490[];   /* the world (SW) */

void func_001A3518(LIGHT *plight)
{
    func_001A6178(&plight->alo.lo);
    func_001A3D00(D_003DD490, plight);
}
