/* func_001A6178 (0x1A6178): LO virtual slot 22: AddLoToUpdateTable__FP2SWP2LO(world, plo); the partner of slot 21. */
#include "so.h"

void AddLoToUpdateTable__FP2SWP2LO(void *psw, LO *plo);
extern char g_sw[];   /* the world (SW) */

void func_001A6178(LO *plo)
{
    AddLoToUpdateTable__FP2SWP2LO(g_sw, plo);
}
