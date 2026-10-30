/* func_00110F78 (0x110F78): factory (CLS::pfnNew) of class 22: allocate a zeroed 0x130-byte object and run the
 * inline constructor (vtable D_002DC3B0, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002DC3B0[];

BASIC *func_00110F78(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x130);

    pbasic->pvt = D_002DC3B0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
