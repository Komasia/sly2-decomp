/* func_00113798 (0x113798): factory (CLS::pfnNew) of class 188: allocate a zeroed 0x30-byte object and run the
 * inline constructor (vtable D_002CFEA0, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CFEA0[];

BASIC *func_00113798(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x30);

    pbasic->pvt = D_002CFEA0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
