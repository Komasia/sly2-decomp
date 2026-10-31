/* func_00111020 (0x111020): factory (CLS::pfnNew) of class 25: allocate a zeroed 0x2D0-byte object and run the
 * inline constructor (vtable D_002C9C20, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002C9C20[];

BASIC *func_00111020(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x2D0);

    pbasic->pvt = D_002C9C20;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
