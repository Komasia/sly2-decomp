/* func_001A6178 (0x1A6178): LO virtual slot 22: unregister the LO from the world (func_00210140); see slot 21. */
#include "so.h"

void func_00210140(void *psw, LO *plo);
extern char D_003DD490[];   /* the world (SW) */

void func_001A6178(LO *plo)
{
    func_00210140(D_003DD490, plo);
}
