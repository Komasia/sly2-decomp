/* func_00112E08 (0x112E08): factory (CLS::pfnNew) of class 139 (LOOP): allocate a zeroed 0x70-byte object and run the
 * inline constructor (vtable g_vtloop, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE g_vtloop[];

BASIC *func_00112E08(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x70);

    pbasic->pvt = g_vtloop;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
