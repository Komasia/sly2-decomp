/* func_00113968 (0x113968): factory (CLS::pfnNew) of class 196: allocate a zeroed 0x40-byte object and run the
 * inline constructor (vtable D_002CC2C0, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CC2C0[];

BASIC *func_00113968(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x40);

    pbasic->pvt = D_002CC2C0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
