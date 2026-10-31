/* func_00110C98 (0x110C98): factory (CLS::pfnNew) of class 10: allocate a zeroed 0x190-byte object and run the
 * inline constructor (vtable D_002D9040, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D9040[];

BASIC *func_00110C98(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x190);

    pbasic->pvt = D_002D9040;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
