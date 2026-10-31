/* func_00113698 (0x113698): factory (CLS::pfnNew) of class 184: allocate a zeroed 0x40-byte object and run the
 * inline constructor (vtable D_002D0020, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D0020[];

BASIC *func_00113698(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x40);

    pbasic->pvt = D_002D0020;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
