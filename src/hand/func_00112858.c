/* func_00112858 (0x112858): factory (CLS::pfnNew) of class 111 (SM): allocate a zeroed 0x80-byte object and run the
 * inline constructor (vtable D_002D97A8, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D97A8[];

BASIC *func_00112858(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x80);

    pbasic->pvt = D_002D97A8;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
