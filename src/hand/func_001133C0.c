/* func_001133C0 (0x1133C0): factory (CLS::pfnNew) of class 171: allocate a zeroed 0xE0-byte object and run the
 * inline constructor (vtable D_002CFA10, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CFA10[];

BASIC *func_001133C0(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0xE0);

    pbasic->pvt = D_002CFA10;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
