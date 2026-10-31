/* func_00110E50 (0x110E50): factory (CLS::pfnNew) of class 17: allocate a zeroed 0x130-byte object and run the
 * inline constructor (vtable D_002D52B0, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D52B0[];

BASIC *func_00110E50(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x130);

    pbasic->pvt = D_002D52B0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
