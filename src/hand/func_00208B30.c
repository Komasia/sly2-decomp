/* func_00208B30 (0x208B30, EOPID 272): clears the guard's immediate target classes (+0x3C0). */

#include "stepguard.h"
void func_00208B30(struct GUARD *pguard)
{
    pguard->ccidImmediate = 0;
}
