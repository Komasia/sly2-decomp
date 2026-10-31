/* func_00113190 (0x113190): factory (CLS::pfnNew) of class 161: allocate a zeroed 0xC0-byte object and run the
 * inline constructor (vtable D_002D0930, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D0930[];

BASIC *func_00113190(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0xC0);

    pbasic->pvt = D_002D0930;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
