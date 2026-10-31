/* func_00112C10 (0x112C10): factory (CLS::pfnNew) of class 127, derived from class 126: allocate a zeroed
 * 0x120-byte object, run the class 126 constructor (func_00212158) and install its own vtable (D_002DABF0). */
#include "so.h"

void *__builtin_new(int cb);   /* zeroed, 16-byte aligned allocation (operator new) */
BASIC *func_00212158(BASIC *pbasic);   /* class 126 constructor */
extern VTE D_002DABF0[];   /* class 127 vtable */

BASIC *func_00112C10(void)
{
    BASIC *pbasic = (BASIC *)__builtin_new(0x120);

    func_00212158(pbasic);
    pbasic->pvt = D_002DABF0;
    return pbasic;
}
