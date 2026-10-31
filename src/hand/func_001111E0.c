/* func_001111E0 (0x1111E0): factory (CLS::pfnNew) of class 33 (EXPLS): allocate a zeroed 0x110-byte object and run the
 * inline constructor (vtable g_vtexpls, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE g_vtexpls[];

BASIC *func_001111E0(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x110);

    pbasic->pvt = g_vtexpls;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
