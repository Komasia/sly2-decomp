/* func_00111170 (0x111170): factory (CLS::pfnNew) of class 31 (EXPLG): allocate a zeroed 0xF0-byte object and run the
 * inline constructor (vtable D_002CE828, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CE828[];

BASIC *func_00111170(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0xF0);

    pbasic->pvt = D_002CE828;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
