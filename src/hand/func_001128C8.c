/* func_001128C8 (0x1128C8): factory (CLS::pfnNew) of class 113: allocate a zeroed 0x60-byte object and run the
 * inline constructor (vtable D_002CF880, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CF880[];

BASIC *func_001128C8(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x60);

    pbasic->pvt = D_002CF880;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
