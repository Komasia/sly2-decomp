/* func_00113350 (0x113350): factory (CLS::pfnNew) of class 169: allocate a zeroed 0x60-byte object and run the
 * inline constructor (vtable D_002CF7F8, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CF7F8[];

BASIC *func_00113350(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x60);

    pbasic->pvt = D_002CF7F8;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
