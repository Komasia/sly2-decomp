/* func_00111470 (0x111470): factory (CLS::pfnNew) of class 43: allocate a zeroed 0x100-byte object and run the
 * inline constructor (vtable D_002CABD8, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CABD8[];

BASIC *func_00111470(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x100);

    pbasic->pvt = D_002CABD8;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
