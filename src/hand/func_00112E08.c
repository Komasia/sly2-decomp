/* func_00112E08 (0x112E08): factory (CLS::pfnNew) of class 139 (LOOP): allocate a zeroed 0x70-byte object and run the
 * inline constructor (vtable D_002D93C0, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D93C0[];

BASIC *func_00112E08(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x70);

    pbasic->pvt = D_002D93C0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
