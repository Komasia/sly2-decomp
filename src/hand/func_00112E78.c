/* func_00112E78 (0x112E78): factory (CLS::pfnNew) of class 141 (SHUFFLE): allocate a zeroed 0x60-byte object and run the
 * inline constructor (vtable g_vtshuffle, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE g_vtshuffle[];

BASIC *func_00112E78(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x60);

    pbasic->pvt = g_vtshuffle;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
