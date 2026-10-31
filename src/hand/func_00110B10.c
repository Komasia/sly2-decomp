/* func_00110B10 (0x110B10): factory (CLS::pfnNew) of class 3 (XFM): allocate a zeroed 0xE0-byte object and run the
 * inline constructor (vtable g_vtxfm, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE g_vtxfm[];

BASIC *func_00110B10(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0xE0);

    pbasic->pvt = g_vtxfm;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
