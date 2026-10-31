/* func_00113580 (0x113580): factory (CLS::pfnNew) of class 179: allocate a zeroed 0x40-byte object and run the
 * inline constructor (vtable D_002D0120, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D0120[];

BASIC *func_00113580(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x40);

    pbasic->pvt = D_002D0120;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
