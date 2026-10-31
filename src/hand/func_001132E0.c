/* func_001132E0 (0x1132E0): factory (CLS::pfnNew) of class 167: allocate a zeroed 0xF0-byte object and run the
 * inline constructor (vtable D_002D06A0, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D06A0[];

BASIC *func_001132E0(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0xF0);

    pbasic->pvt = D_002D06A0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
