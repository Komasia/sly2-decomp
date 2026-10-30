/* func_00112A18 (0x112A18): factory (CLS::pfnNew) of class 119: allocate a zeroed 0xB0-byte object and run the
 * inline constructor (vtable D_002CFA90, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CFA90[];

BASIC *func_00112A18(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0xB0);

    pbasic->pvt = D_002CFA90;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
