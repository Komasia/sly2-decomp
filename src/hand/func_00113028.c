/* func_00113028 (0x113028): factory (CLS::pfnNew) of class 155: allocate a zeroed 0x30-byte object and run the
 * inline constructor (vtable D_002D9480, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D9480[];

BASIC *func_00113028(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x30);

    pbasic->pvt = D_002D9480;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
