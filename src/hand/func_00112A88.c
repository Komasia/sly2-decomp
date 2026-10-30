/* func_00112A88 (0x112A88): factory (CLS::pfnNew) of class 121: allocate a zeroed 0x10B0-byte object and run the
 * inline constructor (vtable D_002CD5B8, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CD5B8[];

BASIC *func_00112A88(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x10B0);

    pbasic->pvt = D_002CD5B8;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
