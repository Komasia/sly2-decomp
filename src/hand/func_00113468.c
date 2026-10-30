/* func_00113468 (0x113468): factory (CLS::pfnNew) of class 174: allocate a zeroed 0x40-byte object and run the
 * inline constructor (vtable D_002D4AF8, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D4AF8[];

BASIC *func_00113468(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x40);

    pbasic->pvt = D_002D4AF8;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
