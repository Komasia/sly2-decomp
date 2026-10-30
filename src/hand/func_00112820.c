/* func_00112820 (0x112820): factory (CLS::pfnNew) of class 110: allocate a zeroed 0xE0-byte object and run the
 * inline constructor (vtable D_002CA300, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CA300[];

BASIC *func_00112820(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0xE0);

    pbasic->pvt = D_002CA300;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
