/* func_00110B80 (0x110B80): factory (CLS::pfnNew) of class 5: allocate a zeroed 0x120-byte object and run the
 * inline constructor (vtable D_002DC070, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002DC070[];

BASIC *func_00110B80(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x120);

    pbasic->pvt = D_002DC070;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
