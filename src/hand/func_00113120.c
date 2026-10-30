/* func_00113120 (0x113120): factory (CLS::pfnNew) of class 159: allocate a zeroed 0x60-byte object and run the
 * inline constructor (vtable D_002D07B0, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D07B0[];

BASIC *func_00113120(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x60);

    pbasic->pvt = D_002D07B0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
