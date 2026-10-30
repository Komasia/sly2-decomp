/* func_00113238 (0x113238): factory (CLS::pfnNew) of class 164: allocate a zeroed 0x50-byte object and run the
 * inline constructor (vtable D_002D0620, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D0620[];

BASIC *func_00113238(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x50);

    pbasic->pvt = D_002D0620;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
