/* func_001133F8 (0x1133F8): factory (CLS::pfnNew) of class 172: allocate a zeroed 0xA0-byte object and run the
 * inline constructor (vtable D_002D0320, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D0320[];

BASIC *func_001133F8(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0xA0);

    pbasic->pvt = D_002D0320;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
