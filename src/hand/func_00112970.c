/* func_00112970 (0x112970): factory (CLS::pfnNew) of class 116: allocate a zeroed 0x70-byte object and run the
 * inline constructor (vtable D_002CF058, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CF058[];

BASIC *func_00112970(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x70);

    pbasic->pvt = D_002CF058;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
