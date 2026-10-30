/* func_00110C28 (0x110C28): factory (CLS::pfnNew) of class 8: allocate a zeroed 0x100-byte object and run the
 * inline constructor (vtable D_002D2CB8, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D2CB8[];

BASIC *func_00110C28(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x100);

    pbasic->pvt = D_002D2CB8;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
