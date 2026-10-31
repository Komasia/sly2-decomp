/* func_00112EB0 (0x112EB0): factory (CLS::pfnNew) of class 142 (EYES): allocate a zeroed 0x80-byte object and run the
 * inline constructor (vtable g_vteyes, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE g_vteyes[];

BASIC *func_00112EB0(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x80);

    pbasic->pvt = g_vteyes;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
