/* func_001135F0 (0x1135F0): factory (CLS::pfnNew) of class 181: allocate a zeroed 0x60-byte object and run the
 * inline constructor (vtable D_002CDD40, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CDD40[];

BASIC *func_001135F0(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x60);

    pbasic->pvt = D_002CDD40;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
