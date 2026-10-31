/* func_00110C60 (0x110C60): factory (CLS::pfnNew) of class 9: allocate a zeroed 0x120-byte object and run the
 * inline constructor (vtable D_002D2B18, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D2B18[];

BASIC *func_00110C60(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x120);

    pbasic->pvt = D_002D2B18;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
