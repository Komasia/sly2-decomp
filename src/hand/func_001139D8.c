/* func_001139D8 (0x1139D8): factory (CLS::pfnNew) of class 198: allocate a zeroed 0x40-byte object and run the
 * inline constructor (vtable D_002CC1C0, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CC1C0[];

BASIC *func_001139D8(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x40);

    pbasic->pvt = D_002CC1C0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
