/* func_001130E8 (0x1130E8): factory (CLS::pfnNew) of class 158: allocate a zeroed 0x50-byte object and run the
 * inline constructor (vtable D_002D0A30, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D0A30[];

BASIC *func_001130E8(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x50);

    pbasic->pvt = D_002D0A30;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
