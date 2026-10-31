/* func_001A6150 (0x1A6150): LO virtual slot 21: func_00210268(world, plo). Slot 21 and slot 22 (func_001A6178,
 * func_00210140) are a pair; derived classes take themselves off their per-class list in slot 21 and put themselves
 * on it in slot 22. */
#include "so.h"

void func_00210268(void *psw, LO *plo);
extern char D_003DD490[];   /* the world (SW) */

void func_001A6150(LO *plo)
{
    func_00210268(D_003DD490, plo);
}
