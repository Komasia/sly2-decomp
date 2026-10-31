/* func_00113318 (0x113318): factory (CLS::pfnNew) of class 168: allocate a zeroed 0xE0-byte object and run the
 * inline constructor (vtable D_002CC4C0, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CC4C0[];

BASIC *func_00113318(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0xE0);

    pbasic->pvt = D_002CC4C0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
