/* func_001127E8 (0x1127E8): factory (CLS::pfnNew) of class 109: allocate a zeroed 0xC0-byte object and run the
 * inline constructor (vtable D_002CAD78, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CAD78[];

BASIC *func_001127E8(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0xC0);

    pbasic->pvt = D_002CAD78;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
