/* func_00110AD8 (0x110AD8): factory (CLS::pfnNew) of class 2 (LO): allocate a zeroed 0x50-byte object and run the
 * inline constructor (vtable g_vtlo, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE g_vtlo[];

BASIC *func_00110AD8(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x50);

    pbasic->pvt = g_vtlo;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
