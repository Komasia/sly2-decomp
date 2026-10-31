/* func_00113510 (0x113510): factory (CLS::pfnNew) of class 177: allocate a zeroed 0x70-byte object and run the
 * inline constructor (vtable D_002D03A0, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D03A0[];

BASIC *func_00113510(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x70);

    pbasic->pvt = D_002D03A0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
