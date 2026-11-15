/* func_002089E8 (0x2089E8, option 395): clears the guard's excluded target classes (+0x3A8). */

#include "stepguard.h"
void func_002089E8(struct GUARD *pguard)
{
    pguard->ccidExcluded = 0;
}
