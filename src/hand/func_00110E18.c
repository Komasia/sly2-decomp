/* func_00110E18 (0x110E18): factory (CLS::pfnNew) of class 16: allocate a zeroed 0x180-byte object and run the
 * inline constructor (vtable D_002CDBA0, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CDBA0[];

BASIC *func_00110E18(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x180);

    pbasic->pvt = D_002CDBA0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
