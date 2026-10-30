/* func_00111138 (0x111138): factory (CLS::pfnNew) of class 29 (EMITTER): allocate a zeroed 0x160-byte object and run the
 * inline constructor (vtable D_002CEB78, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002CEB78[];

BASIC *func_00111138(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x160);

    pbasic->pvt = D_002CEB78;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
