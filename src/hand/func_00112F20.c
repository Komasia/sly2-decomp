/* func_00112F20 (0x112F20): factory (CLS::pfnNew) of class 144 (CIRCLER): allocate a zeroed 0x60-byte object and run the
 * inline constructor (vtable g_vtcircler, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE g_vtcircler[];

BASIC *func_00112F20(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x60);

    pbasic->pvt = g_vtcircler;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
