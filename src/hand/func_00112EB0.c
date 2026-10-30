/* func_00112EB0 (0x112EB0): factory (CLS::pfnNew) of class 142 (EYES): allocate a zeroed 0x80-byte object and run the
 * inline constructor (vtable D_002D92A0, null pframe / psidebag reference pointers). */
#include "so.h"

void *func_001AE4F8(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
extern VTE D_002D92A0[];

BASIC *func_00112EB0(void)
{
    BASIC *pbasic = (BASIC *)func_001AE4F8(0x80);

    pbasic->pvt = D_002D92A0;
    pbasic->pframe = NULL;
    pbasic->psidebag = NULL;
    return pbasic;
}
