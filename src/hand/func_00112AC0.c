/* func_00112AC0 (0x112AC0): factory (CLS::pfnNew) of class 122: allocate a zeroed 0x60-byte object and run the
 * inline constructor (vtable D_002CDA10, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CDA10[];

BASIC *func_00112AC0(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x60);

    pbasic->pvt = D_002CDA10;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
