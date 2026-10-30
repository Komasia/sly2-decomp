/* func_001114A8 (0x1114A8): factory (CLS::pfnNew) of class 44: allocate a zeroed 0x140-byte object and run the
 * inline constructor (vtable D_002CA9F0, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CA9F0[];

BASIC *func_001114A8(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x140);

    pbasic->pvt = D_002CA9F0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
