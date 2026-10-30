/* func_001136D0 (0x1136D0): factory (CLS::pfnNew) of class 185: allocate a zeroed 0x40-byte object and run the
 * inline constructor (vtable D_002CFFA0, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CFFA0[];

BASIC *func_001136D0(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x40);

    pbasic->pvt = D_002CFFA0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
