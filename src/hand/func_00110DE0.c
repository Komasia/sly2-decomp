/* func_00110DE0 (0x110DE0): factory (CLS::pfnNew) of class 15: allocate a zeroed 0x1C0-byte object and run the
 * inline constructor (vtable D_002DB6B8, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002DB6B8[];

BASIC *func_00110DE0(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x1C0);

    pbasic->pvt = D_002DB6B8;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
