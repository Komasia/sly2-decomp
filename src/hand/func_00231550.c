/* func_00231550 (0x231550): ALO virtual slot 31: the ALO's transform link - copy its local matrix out when asked
 * and return the XF it hangs off (the default XF D_002C44F0 when it has none). */
#include "so.h"

extern XF D_002C44F0;

XF *func_00231550(ALO *palo, struct MATRIX4 *pmatLocal)
{
    XF *pxf;

    if (pmatLocal != NULL)
        *pmatLocal = palo->matLocal;
    pxf = palo->pxf;
    if (pxf == NULL)
        pxf = &D_002C44F0;
    return pxf;
}
