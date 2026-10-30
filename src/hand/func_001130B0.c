/* func_001130B0 (0x1130B0): factory (CLS::pfnNew) of class 157: allocate a zeroed 0x50-byte object and run the
 * inline constructor (vtable D_002D0AB0, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D0AB0[];

BASIC *func_001130B0(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x50);

    pbasic->pvt = D_002D0AB0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
