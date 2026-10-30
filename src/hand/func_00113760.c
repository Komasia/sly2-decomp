/* func_00113760 (0x113760): factory (CLS::pfnNew) of class 187: allocate a zeroed 0x30-byte object and run the
 * inline constructor (vtable D_002CFF20, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CFF20[];

BASIC *func_00113760(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x30);

    pbasic->pvt = D_002CFF20;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
