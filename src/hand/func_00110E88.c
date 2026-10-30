/* func_00110E88 (0x110E88): factory (CLS::pfnNew) of class 18: allocate a zeroed 0x100-byte object and run the
 * inline constructor (vtable D_002DB518, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002DB518[];

BASIC *func_00110E88(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x100);

    pbasic->pvt = D_002DB518;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
