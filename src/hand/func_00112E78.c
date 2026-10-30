/* func_00112E78 (0x112E78): factory (CLS::pfnNew) of class 141 (SHUFFLE): allocate a zeroed 0x60-byte object and run the
 * inline constructor (vtable D_002D9300, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D9300[];

BASIC *func_00112E78(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x60);

    pbasic->pvt = D_002D9300;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
