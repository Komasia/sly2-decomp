/* func_00112D70 (0x112D70): factory (CLS::pfnNew) of class 133: allocate a zeroed 0x110-byte object and run the
 * inline constructor (vtable D_002CF1E8, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CF1E8[];

BASIC *func_00112D70(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x110);

    pbasic->pvt = D_002CF1E8;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
