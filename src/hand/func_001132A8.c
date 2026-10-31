/* func_001132A8 (0x1132A8): factory (CLS::pfnNew) of class 166: allocate a zeroed 0xC0-byte object and run the
 * inline constructor (vtable D_002D0728, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D0728[];

BASIC *func_001132A8(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0xC0);

    pbasic->pvt = D_002D0728;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
