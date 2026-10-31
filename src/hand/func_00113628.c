/* func_00113628 (0x113628): factory (CLS::pfnNew) of class 182: allocate a zeroed 0x50-byte object and run the
 * inline constructor (vtable D_002CCE90, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CCE90[];

BASIC *func_00113628(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x50);

    pbasic->pvt = D_002CCE90;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
