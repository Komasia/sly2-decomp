/* func_00110BB8 (0x110BB8): factory (CLS::pfnNew) of class 6: allocate a zeroed 0x100-byte object and run the
 * inline constructor (vtable D_002D6E08, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D6E08[];

BASIC *func_00110BB8(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x100);

    pbasic->pvt = D_002D6E08;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
