/* func_001137D0 (0x1137D0): factory (CLS::pfnNew) of class 189: allocate a zeroed 0x50-byte object and run the
 * inline constructor (vtable D_002CFD20, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CFD20[];

BASIC *func_001137D0(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x50);

    pbasic->pvt = D_002CFD20;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
