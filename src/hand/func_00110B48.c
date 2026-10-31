/* func_00110B48 (0x110B48): factory (CLS::pfnNew) of class 4: allocate a zeroed 0x170-byte object and run the
 * inline constructor (vtable g_vtlight, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE g_vtlight[];

BASIC *func_00110B48(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x170);

    pbasic->pvt = g_vtlight;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
