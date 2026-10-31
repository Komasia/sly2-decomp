/* func_00112FB8 (0x112FB8): factory (CLS::pfnNew) of class 153: allocate a zeroed 0xB0-byte object and run the
 * inline constructor (vtable D_002C94A0, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002C94A0[];

BASIC *func_00112FB8(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0xB0);

    pbasic->pvt = D_002C94A0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
