/* func_00113660 (0x113660): factory (CLS::pfnNew) of class 183: allocate a zeroed 0x70-byte object and run the
 * inline constructor (vtable D_002D00A0, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D00A0[];

BASIC *func_00113660(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x70);

    pbasic->pvt = D_002D00A0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
