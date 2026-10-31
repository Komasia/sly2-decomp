/* func_00111518 (0x111518): factory (CLS::pfnNew) of class 46: allocate a zeroed 0x120-byte object and run the
 * inline constructor (vtable D_002D9F70, null pframe / psidebag reference pointers). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D9F70[];

BASIC *func_00111518(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x120);

    pbasic->pvt = D_002D9F70;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
