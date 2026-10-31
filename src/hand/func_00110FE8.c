/* func_00110FE8 (0x110FE8): factory (CLS::pfnNew) of class 24: allocate a zeroed 0x2D0-byte object and run the
 * inline constructor (vtable g_vtvolbtn, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE g_vtvolbtn[];

BASIC *func_00110FE8(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x2D0);

    pbasic->pvt = g_vtvolbtn;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
