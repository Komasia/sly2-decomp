/* func_001A6150 (0x1A6150): LO virtual slot 21: RemoveLoFromUpdateTable__FP2SWP2LO(world, plo). Slot 21 and slot 22 (func_001A6178,
 * AddLoToUpdateTable__FP2SWP2LO) are a pair; derived classes take themselves off their per-class list in slot 21 and put themselves
 * on it in slot 22. */
#include "so.h"

void RemoveLoFromUpdateTable__FP2SWP2LO(void *psw, LO *plo);
extern char g_sw[];   /* the world (SW) */

void func_001A6150(LO *plo)
{
    RemoveLoFromUpdateTable__FP2SWP2LO(g_sw, plo);
}
