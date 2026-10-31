/* func_001134A0 (0x1134A0): factory (CLS::pfnNew) of class 175: allocate a zeroed 0x60-byte object and run the
 * inline constructor (vtable D_002D02A0, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D02A0[];

BASIC *func_001134A0(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x60);

    pbasic->pvt = D_002D02A0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
