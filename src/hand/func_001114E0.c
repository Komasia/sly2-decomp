/* func_001114E0 (0x1114E0): factory (CLS::pfnNew) of class 45: allocate a zeroed 0x130-byte object and run the
 * inline constructor (vtable D_002D4F80, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D4F80[];

BASIC *func_001114E0(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x130);

    pbasic->pvt = D_002D4F80;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
