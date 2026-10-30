/* func_00112900 (0x112900): factory (CLS::pfnNew) of class 114: allocate a zeroed 0xB0-byte object and run the
 * inline constructor (vtable D_002D8C48, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D8C48[];

BASIC *func_00112900(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0xB0);

    pbasic->pvt = D_002D8C48;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
