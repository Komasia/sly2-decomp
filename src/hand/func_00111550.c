/* func_00111550 (0x111550): factory (CLS::pfnNew) of class 47: allocate a zeroed 0x110-byte object and run the
 * inline constructor (vtable D_002CE118, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CE118[];

BASIC *func_00111550(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x110);

    pbasic->pvt = D_002CE118;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
