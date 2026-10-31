/* func_001131C8 (0x1131C8): factory (CLS::pfnNew) of class 162: allocate a zeroed 0xC0-byte object and run the
 * inline constructor (vtable D_002D0830, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D0830[];

BASIC *func_001131C8(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0xC0);

    pbasic->pvt = D_002D0830;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
