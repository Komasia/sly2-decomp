/* func_00110DA8 (0x110DA8): factory (CLS::pfnNew) of class 14: allocate a zeroed 0x1F0-byte object and run the
 * inline constructor (vtable D_002D4DE0, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D4DE0[];

BASIC *func_00110DA8(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x1F0);

    pbasic->pvt = D_002D4DE0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
