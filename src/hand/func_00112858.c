/* func_00112858 (0x112858): factory (CLS::pfnNew) of class 111 (SM): allocate a zeroed 0x80-byte object and run the
 * inline constructor (vtable g_vtsm, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE g_vtsm[];

BASIC *func_00112858(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x80);

    pbasic->pvt = g_vtsm;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
