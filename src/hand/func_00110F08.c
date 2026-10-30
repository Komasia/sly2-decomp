/* func_00110F08 (0x110F08): factory (CLS::pfnNew) of class 20: allocate a zeroed 0xF0-byte object and run the
 * inline constructor (vtable D_002C9A80, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002C9A80[];

BASIC *func_00110F08(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0xF0);

    pbasic->pvt = D_002C9A80;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
