/* func_00112FF0 (0x112FF0): factory (CLS::pfnNew) of class 154: allocate a zeroed 0x30-byte object and run the
 * inline constructor (vtable D_002CA490, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CA490[];

BASIC *func_00112FF0(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x30);

    pbasic->pvt = D_002CA490;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
