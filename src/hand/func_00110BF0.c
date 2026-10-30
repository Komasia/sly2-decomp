/* func_00110BF0 (0x110BF0): factory (CLS::pfnNew) of class 7: allocate a zeroed 0x110-byte object and run the
 * inline constructor (vtable D_002D5DC8, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D5DC8[];

BASIC *func_00110BF0(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x110);

    pbasic->pvt = D_002D5DC8;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
