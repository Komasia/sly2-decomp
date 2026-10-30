/* func_00112938 (0x112938): factory (CLS::pfnNew) of class 115 (WR): allocate a zeroed 0x900-byte object and run the
 * inline constructor (vtable D_002DCF00, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002DCF00[];

BASIC *func_00112938(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x900);

    pbasic->pvt = D_002DCF00;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
