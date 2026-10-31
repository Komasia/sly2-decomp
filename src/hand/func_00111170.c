/* func_00111170 (0x111170): factory (CLS::pfnNew) of class 31 (EXPLG): allocate a zeroed 0xF0-byte object and run the
 * inline constructor (vtable g_vtexplg, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE g_vtexplg[];

BASIC *func_00111170(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0xF0);

    pbasic->pvt = g_vtexplg;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
