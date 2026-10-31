/* func_00112A50 (0x112A50): factory (CLS::pfnNew) of class 120: allocate a zeroed 0xD0-byte object and run the
 * inline constructor (vtable D_002DA840, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002DA840[];

BASIC *func_00112A50(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0xD0);

    pbasic->pvt = D_002DA840;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
