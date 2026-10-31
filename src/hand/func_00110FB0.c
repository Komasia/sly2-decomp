/* func_00110FB0 (0x110FB0): factory (CLS::pfnNew) of class 23: allocate a zeroed 0x140-byte object and run the
 * inline constructor (vtable D_002DC210, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002DC210[];

BASIC *func_00110FB0(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x140);

    pbasic->pvt = D_002DC210;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
