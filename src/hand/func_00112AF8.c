/* func_00112AF8 (0x112AF8): factory (CLS::pfnNew) of class 123: allocate a zeroed 0x60-byte object and run the
 * inline constructor (vtable D_002CCF10, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CCF10[];

BASIC *func_00112AF8(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x60);

    pbasic->pvt = D_002CCF10;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
