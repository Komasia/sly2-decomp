/* func_00112DD0 (0x112DD0): factory (CLS::pfnNew) of class 136: allocate a zeroed 0x50-byte object and run the
 * inline constructor (vtable D_002D9768, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D9768[];

BASIC *func_00112DD0(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x50);

    pbasic->pvt = D_002D9768;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
