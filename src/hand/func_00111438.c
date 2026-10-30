/* func_00111438 (0x111438): factory (CLS::pfnNew) of class 42: allocate a zeroed 0x180-byte object and run the
 * inline constructor (vtable D_002DC550, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002DC550[];

BASIC *func_00111438(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x180);

    pbasic->pvt = D_002DC550;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
