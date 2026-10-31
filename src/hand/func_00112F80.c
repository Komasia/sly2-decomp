/* func_00112F80 (0x112F80): factory (CLS::pfnNew) of class 146: allocate a zeroed 0x40-byte object and run the
 * inline constructor (vtable D_002DA9D0, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002DA9D0[];

BASIC *func_00112F80(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x40);

    pbasic->pvt = D_002DA9D0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
