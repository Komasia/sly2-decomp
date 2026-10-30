/* func_001111E0 (0x1111E0): factory (CLS::pfnNew) of class 33 (EXPLS): allocate a zeroed 0x110-byte object and run the
 * inline constructor (vtable D_002CE4D0, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CE4D0[];

BASIC *func_001111E0(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x110);

    pbasic->pvt = D_002CE4D0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
