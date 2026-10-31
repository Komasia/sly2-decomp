/* func_001135B8 (0x1135B8): factory (CLS::pfnNew) of class 180: allocate a zeroed 0x40-byte object and run the
 * inline constructor (vtable D_002CDDC0, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CDDC0[];

BASIC *func_001135B8(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x40);

    pbasic->pvt = D_002CDDC0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
