/* func_001129E0 (0x1129E0): factory (CLS::pfnNew) of class 118: allocate a zeroed 0x60-byte object and run the
 * inline constructor (vtable D_002C94E0, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002C94E0[];

BASIC *func_001129E0(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x60);

    pbasic->pvt = D_002C94E0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
