/* func_00112938 (0x112938): factory (CLS::pfnNew) of class 115 (WR): allocate a zeroed 0x900-byte object and run the
 * inline constructor (vtable g_vtwr, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE g_vtwr[];

BASIC *func_00112938(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x900);

    pbasic->pvt = g_vtwr;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
