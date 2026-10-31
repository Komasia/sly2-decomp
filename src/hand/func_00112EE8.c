/* func_00112EE8 (0x112EE8): factory (CLS::pfnNew) of class 143 (SCROLLER): allocate a zeroed 0x70-byte object and run the
 * inline constructor (vtable g_vtscroller, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE g_vtscroller[];

BASIC *func_00112EE8(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x70);

    pbasic->pvt = g_vtscroller;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
