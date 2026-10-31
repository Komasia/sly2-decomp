/* func_001138F8 (0x1138F8): factory (CLS::pfnNew) of class 194: allocate a zeroed 0xA0-byte object and run the
 * inline constructor (vtable D_002CC3C0, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CC3C0[];

BASIC *func_001138F8(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0xA0);

    pbasic->pvt = D_002CC3C0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
