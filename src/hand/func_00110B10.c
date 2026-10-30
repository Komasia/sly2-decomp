/* func_00110B10 (0x110B10): factory (CLS::pfnNew) of class 3 (ALO): allocate a zeroed 0xE0-byte object and run the
 * inline constructor (vtable D_002DD090, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002DD090[];

BASIC *func_00110B10(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0xE0);

    pbasic->pvt = D_002DD090;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
