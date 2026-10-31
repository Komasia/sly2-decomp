/* func_00112CF8 (0x112CF8): factory (CLS::pfnNew) of class 131, derived from class 126: allocate a zeroed
 * 0x140-byte object, run the class 126 constructor (func_00212158) and install its own vtable (D_002CEEB8). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
BASIC *func_00212158(BASIC *pbasic);   /* class 126 constructor */
extern VTE D_002CEEB8[];   /* class 131 vtable */

BASIC *func_00112CF8(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x140);

    func_00212158(pbasic);
    pbasic->pvt = D_002CEEB8;
    return pbasic;
}
