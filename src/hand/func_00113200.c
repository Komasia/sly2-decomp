/* func_00113200 (0x113200): factory (CLS::pfnNew) of class 163: allocate a zeroed 0xC0-byte object and run the
 * inline constructor (vtable D_002D08B0, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D08B0[];

BASIC *func_00113200(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0xC0);

    pbasic->pvt = D_002D08B0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
