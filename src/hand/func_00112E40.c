/* func_00112E40 (0x112E40): factory (CLS::pfnNew) of class 140 (PINGPONG): allocate a zeroed 0x70-byte object and run the
 * inline constructor (vtable g_vtpingpong, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE g_vtpingpong[];

BASIC *func_00112E40(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x70);

    pbasic->pvt = g_vtpingpong;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
