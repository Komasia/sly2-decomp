/* func_00111138 (0x111138): factory (CLS::pfnNew) of class 29 (EMITTER): allocate a zeroed 0x160-byte object and run the
 * inline constructor (vtable g_vtemitter, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE g_vtemitter[];

BASIC *func_00111138(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x160);

    pbasic->pvt = g_vtemitter;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
