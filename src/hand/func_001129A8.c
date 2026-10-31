/* func_001129A8 (0x1129A8): factory (CLS::pfnNew) of class 117: allocate a zeroed 0x70-byte object and run the
 * inline constructor (vtable D_002CE2F8, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CE2F8[];

BASIC *func_001129A8(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x70);

    pbasic->pvt = D_002CE2F8;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
