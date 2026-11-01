/* func_001A6178 (0x1A6178): LO virtual slot 22: func_00210140(world, plo); the partner of slot 21. */
#include "so.h"

void func_00210140(void *psw, LO *plo);
extern char g_sw[];   /* the world (SW) */

void func_001A6178(LO *plo)
{
    func_00210140(g_sw, plo);
}
