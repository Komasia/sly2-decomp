/* func_001111A8 (0x1111A8): factory (CLS::pfnNew) of class 32 (EXPLO): allocate a zeroed 0xF0-byte object and run the
 * inline constructor (vtable g_vtexplo, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE g_vtexplo[];

BASIC *func_001111A8(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0xF0);

    pbasic->pvt = g_vtexplo;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
