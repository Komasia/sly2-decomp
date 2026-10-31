/* func_00111058 (0x111058): factory (CLS::pfnNew) of class 26: allocate a zeroed 0x190-byte object and run the
 * inline constructor (vtable D_002DC6F0, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002DC6F0[];

BASIC *func_00111058(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x190);

    pbasic->pvt = D_002DC6F0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
