/* func_001111A8 (0x1111A8): factory (CLS::pfnNew) of class 32 (EXPLO): allocate a zeroed 0xF0-byte object and run the
 * inline constructor (vtable D_002CA098, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CA098[];

BASIC *func_001111A8(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0xF0);

    pbasic->pvt = D_002CA098;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
