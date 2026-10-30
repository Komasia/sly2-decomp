/* func_00113888 (0x113888): factory (CLS::pfnNew) of class 192: allocate a zeroed 0x60-byte object and run the
 * inline constructor (vtable D_002CFDA0, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CFDA0[];

BASIC *func_00113888(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x60);

    pbasic->pvt = D_002CFDA0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
