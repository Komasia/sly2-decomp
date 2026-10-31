/* func_001138C0 (0x1138C0): factory (CLS::pfnNew) of class 193: allocate a zeroed 0x50-byte object and run the
 * inline constructor (vtable D_002CC440, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CC440[];

BASIC *func_001138C0(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x50);

    pbasic->pvt = D_002CC440;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
