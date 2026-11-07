/* func_001F56F8 (0x1F56F8): SO virtual slot 52: hand the SO to the world (PoxaAddSw__FP2SWP3ALO on g_sw). */
#include "so.h"

void PoxaAddSw__FP2SWP3ALO(void *psw, SO *pso);
extern char g_sw[];   /* the world (SW) */

void func_001F56F8(SO *pso)
{
    PoxaAddSw__FP2SWP3ALO(g_sw, pso);
}
