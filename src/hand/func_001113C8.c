/* func_001113C8 (0x1113C8): factory (CLS::pfnNew) of class 40: allocate a zeroed 0xF0-byte object and run the
 * inline constructor (vtable D_002D3200, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D3200[];

BASIC *func_001113C8(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0xF0);

    pbasic->pvt = D_002D3200;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
